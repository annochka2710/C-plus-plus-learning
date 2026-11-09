#!/usr/bin/env bash

# Запускать из корня проекта:
# bash bash/rm/examples.sh

set -euo pipefail

# Все удаления ограничены новым временным каталогом.
work_dir=$(mktemp -d /tmp/bash-rm.XXXXXX)
trap 'rm -rf -- "$work_dir"' EXIT
printf 'Учебный каталог: %s\n' "$work_dir"

printf '\n1. Удаление одного и нескольких файлов, включая имя с пробелом\n'
touch "$work_dir/first.txt" "$work_dir/second.txt" "$work_dir/report final.txt"
rm -v -- "$work_dir/first.txt"
rm -v -- "$work_dir/second.txt" "$work_dir/report final.txt"

printf '\n2. Имя, начинающееся с дефиса\n'
touch "$work_dir/-draft.txt"
(
    cd -- "$work_dir"
    rm -v -- -draft.txt
)

printf '\n3. Опция -f допускает отсутствие файла\n'
rm -f -- "$work_dir/missing.txt"

printf '\n4. Рекурсивное удаление, включая скрытый файл\n'
mkdir -p "$work_dir/cache/nested"
touch "$work_dir/cache/nested/data.txt" "$work_dir/cache/.hidden"
rm -rv -- "$work_dir/cache"

printf '\n5. Удаление пустого каталога\n'
mkdir "$work_dir/empty"
rmdir -v -- "$work_dir/empty"

printf '\n6. rmdir отказывается удалять непустой каталог (ожидаемая ошибка)\n'
mkdir "$work_dir/nonempty"
touch "$work_dir/nonempty/keep.txt"
if rmdir -- "$work_dir/nonempty"; then
    printf 'Ошибка примера: непустой каталог был удалён\n' >&2
    exit 1
fi
printf 'Файл остался: %s\n' "$work_dir/nonempty/keep.txt"

printf '\n7. Удаление цепочки пустых каталогов\n'
mkdir -p "$work_dir/parents/child/leaf"
(
    cd -- "$work_dir"
    rmdir -pv -- parents/child/leaf
)

printf '\n8. Удаление символической ссылки и файла через unlink\n'
touch "$work_dir/original.txt"
ln -s -- "$work_dir/original.txt" "$work_dir/shortcut"
rm -v -- "$work_dir/shortcut"
test -f "$work_dir/original.txt"
printf 'Исходный файл остался\n'
unlink -- "$work_dir/original.txt"

printf '\n9. Поиск и удаление только обычных файлов .log\n'
mkdir -p "$work_dir/logs/archive"
touch "$work_dir/logs/current.log" "$work_dir/logs/archive/old.log"
touch "$work_dir/logs/.hidden.log" "$work_dir/logs/keep.txt"
printf 'Будут удалены:\n'
find "$work_dir/logs" -type f -name '*.log' -print
find "$work_dir/logs" -type f -name '*.log' -delete
printf 'Остались:\n'
find "$work_dir/logs" -type f -print

printf '\nПримеры завершены. Временный каталог будет удалён при выходе.\n'
