#!/usr/bin/env bash

# Запускать из корня проекта:
# bash bash/grep/examples.sh

printf '\n1. Строки, содержащие ERROR с учётом регистра\n'
grep 'ERROR' bash/practice/grep/app.log

printf '\n2. Совпадения с номерами строк\n'
grep -n 'ERROR' bash/practice/grep/app.log

printf '\n3. Отдельное слово error без учёта регистра\n'
grep -inw 'error' bash/practice/grep/app.log

printf '\n4. Строки, которые не начинаются с INFO и пробела\n'
grep -v '^INFO ' bash/practice/grep/app.log

printf '\n5. Количество строк, содержащих ERROR\n'
grep -c 'ERROR' bash/practice/grep/app.log

printf '\n6. Только имена файлов с совпадениями\n'
grep -l 'ERROR' bash/practice/grep/app.log bash/practice/grep/notes.txt

printf '\n7. Поиск ERROR во всех вложенных файлах .log\n'
grep -rn --include='*.log' 'ERROR' bash/practice/grep

printf '\n8. Точка в регулярном выражении и в обычном тексте\n'
grep '1.2' bash/practice/grep/config.txt
grep -F '1.2' bash/practice/grep/config.txt

printf '\n9. Слово stopped в конце строки\n'
grep -n 'stopped$' bash/practice/grep/app.log

printf '\n10. Строки, начинающиеся с ERROR или WARNING и пробела\n'
grep -En '^(ERROR|WARNING) ' bash/practice/grep/app.log
