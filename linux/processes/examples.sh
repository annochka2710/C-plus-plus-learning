#!/usr/bin/env bash

# Запускать из корня проекта:
# bash linux/processes/examples.sh

set -euo pipefail

child_pid=''

cleanup() {
    if [[ -n "$child_pid" ]]; then
        # Завершаем только созданный здесь процесс, даже если он остановлен.
        kill -KILL -- "$child_pid" 2>/dev/null || true
        wait "$child_pid" 2>/dev/null || true
    fi
}

trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

# Доставка сигналов асинхронна. До 100 проверок с паузами по 0.02 секунды.
wait_for_state() {
    local expected=$1
    local state
    local attempt

    for ((attempt = 0; attempt < 100; attempt++)); do
        state=$(ps -p "$child_pid" -o stat=) || return 1
        state=${state//[[:space:]]/}
        if [[ "$state" == "$expected"* ]]; then
            return 0
        fi
        sleep 0.02
    done

    printf 'Процесс %s не перешёл в состояние %s\n' "$child_pid" "$expected" >&2
    return 1
}

start_child() {
    sleep 300 &
    child_pid=$!
    printf 'Учебный PID: %s\n' "$child_pid"
    wait_for_state S
}

finish_child() {
    local expected=$1
    local status=0

    # Завершение сигналом даёт ненулевой статус; это ожидаемый результат.
    wait "$child_pid" 2>/dev/null || status=$?
    child_pid=''
    printf 'Статус wait: %s (ожидаем %s)\n' "$status" "$expected"
    if [[ "$status" != "$expected" ]]; then
        return 1
    fi
}

printf 'PID оболочки скрипта: %s\n' "$$"
printf '\n1. Запускаем свой процесс в фоне\n'
start_child
jobs -l

printf '\n2. Снимок ps: только скрипт и его учебный процесс\n'
ps -p "$$,$child_pid" -o pid,ppid,stat,pcpu,pmem,etime,args

printf '\n3. Поиск sleep среди прямых потомков скрипта\n'
pgrep -a -P "$$" -x sleep

printf '\n4. Один снимок top для учебного процесса\n'
top -b -n 1 -p "$child_pid"

printf '\n5. STOP приостанавливает процесс, ожидаем STAT=T\n'
kill -STOP -- "$child_pid"
wait_for_state T
ps -p "$child_pid" -o pid,ppid,stat,args

printf '\n6. CONT продолжает процесс, sleep снова ожидает: STAT=S\n'
kill -CONT -- "$child_pid"
wait_for_state S
ps -p "$child_pid" -o pid,ppid,stat,args

printf '\n7. kill -0 проверяет существование PID и право отправки сигнала\n'
kill -0 -- "$child_pid"
printf 'Проверка прошла\n'

printf '\n8. TERM запрашивает завершение, wait получает статус\n'
kill -TERM -- "$child_pid"
finish_child 143

printf '\n9. Отдельный процесс для демонстрации KILL\n'
start_child
ps -p "$child_pid" -o pid,ppid,stat,args
kill -KILL -- "$child_pid"
finish_child 137

printf '\nПримеры завершены. Все учебные процессы завершены и собраны через wait.\n'
