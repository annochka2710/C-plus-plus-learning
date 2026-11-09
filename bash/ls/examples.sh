#!/usr/bin/env bash

# Запускать из корня проекта:
# bash bash/ls/examples.sh

set -euo pipefail
export LC_ALL=C

work_dir=$(mktemp -d /tmp/bash-ls.XXXXXX)
trap 'rm -rf -- "$work_dir"' EXIT
printf 'Учебный каталог: %s\n' "$work_dir"

mkdir -p "$work_dir/docs/nested" "$work_dir/empty"
printf 'Small\n' > "$work_dir/small.txt"
printf '%2048s' '' > "$work_dir/large.txt"
printf 'Hidden\n' > "$work_dir/.hidden.txt"
printf 'Report\n' > "$work_dir/report final.txt"
printf 'Draft\n' > "$work_dir/-draft.txt"
printf 'Notes\n' > "$work_dir/docs/nested/notes.txt"
printf '#!/usr/bin/env bash\n' > "$work_dir/run.sh"
chmod u+x -- "$work_dir/run.sh"
for number in 1 2 10; do
    printf 'v%s\n' "$number" > "$work_dir/part-$number.txt"
done
ln -- "$work_dir/small.txt" "$work_dir/hard-small.txt"
ln -s -- small.txt "$work_dir/file-link"
ln -s -- docs "$work_dir/directory-link"
touch -t 202001010000 -- "$work_dir/small.txt"
touch -t 202101010000 -- "$work_dir/large.txt"

printf '\n1. Одно имя на строку, скрытые имена пропущены\n'
ls -1 -- "$work_dir"

printf '\n2. Все имена, включая . и ..\n'
ls -1a -- "$work_dir"

printf '\n3. Скрытые имена без . и ..\n'
ls -1A -- "$work_dir"

printf '\n4. Подробный вывод и удобные единицы размера\n'
ls -lAh -- "$work_dir"

printf '\n5. Сам каталог и его содержимое — разные запросы\n'
ls -ldh -- "$work_dir/docs"
ls -l -- "$work_dir/docs"

printf '\n6. Рекурсивный просмотр подкаталогов\n'
ls -R -- "$work_dir/docs"

printf '\n7. Метки типов: каталоги /, ссылки @, исполняемые файлы *\n'
ls -1F -- "$work_dir"
printf 'Только обозначения каталогов:\n'
ls -1p -- "$work_dir"

printf '\n8. Сортировка по размеру и обратный порядок\n'
ls -lhS -- "$work_dir/small.txt" "$work_dir/large.txt"
ls -lhSr -- "$work_dir/small.txt" "$work_dir/large.txt"

printf '\n9. Сортировка по mtime: новые, затем старые; обратный порядок\n'
ls -lt -- "$work_dir/small.txt" "$work_dir/large.txt"
ls -ltr -- "$work_dir/small.txt" "$work_dir/large.txt"

printf '\n10. Сортировка имён с числами\n'
printf 'По имени:\n'
ls -1 -- "$work_dir"/part-*.txt
printf 'С учётом чисел (-v):\n'
ls -1v -- "$work_dir"/part-*.txt

printf '\n11. Номера inode: жёсткие имена и символическая ссылка\n'
ls -li -- "$work_dir/small.txt" "$work_dir/hard-small.txt" "$work_dir/file-link"
printf 'Свойства цели символической ссылки (-L):\n'
ls -liL -- "$work_dir/file-link"
printf 'Сама ссылка на каталог (-d):\n'
ls -ld -- "$work_dir/directory-link"

printf '\n12. Числовые UID/GID и выделенное место в блоках по 1024 байта\n'
ls -n -- "$work_dir/small.txt"
ls -lsk -- "$work_dir/large.txt"

printf '\n13. Кавычки и экранирование в выводе имени с пробелом\n'
ls -lQ -- "$work_dir/report final.txt"
ls -lb -- "$work_dir/report final.txt"

printf '\n14. Каталоги первыми и явный формат даты\n'
ls -1 --group-directories-first --color=never -- "$work_dir"
ls -l --time-style=long-iso -- "$work_dir/small.txt" "$work_dir/large.txt"

printf '\n15. Время доступа и время изменения состояния inode\n'
ls -lu -- "$work_dir/small.txt"
ls -lc -- "$work_dir/small.txt"

printf '\n16. Дефис в начале имени: -- завершает список опций\n'
(
    cd -- "$work_dir"
    ls -l -- -draft.txt
)

printf '\nПримеры завершены. Временный каталог будет удалён при выходе.\n'
