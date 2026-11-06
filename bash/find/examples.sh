#!/usr/bin/env bash

# Запускать из корня проекта:
# bash bash/find/examples.sh

printf '\n1. Начальный каталог и всё его содержимое\n'
find bash/practice/find

printf '\n2. Файлы с расширением .txt с учётом регистра\n'
find bash/practice/find -type f -name '*.txt'

printf '\n3. Файлы с расширением .txt без учёта регистра\n'
find bash/practice/find -type f -iname '*.txt'

printf '\n4. Только каталоги\n'
find bash/practice/find -type d

printf '\n5. Обычные файлы с расширением .cpp\n'
find bash/practice/find -type f -name '*.cpp'

printf '\n6. Файлы непосредственно в учебном каталоге\n'
find bash/practice/find -maxdepth 1 -type f

printf '\n7. Файлы размером строго меньше 20 байт\n'
find bash/practice/find -type f -size -20c

printf '\n8. Файлы .txt или .log с учётом регистра\n'
find bash/practice/find -type f \( -name '*.txt' -o -name '*.log' \)

printf '\n9. Определить тип каждого найденного файла\n'
find bash/practice/find -type f -exec file {} +
