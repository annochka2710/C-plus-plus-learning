#!/usr/bin/env bash

# Запускать из корня проекта:
# bash linux/links/examples.sh

set -euo pipefail

work_dir=$(mktemp -d /tmp/linux-links.XXXXXX)
trap 'rm -rf -- "$work_dir"' EXIT
printf 'Учебный каталог: %s\n' "$work_dir"

printf '\n1. Файл, жёсткая и символическая ссылки\n'
printf 'First version\n' > "$work_dir/original.txt"
ln -- "$work_dir/original.txt" "$work_dir/hard.txt"
ln -s -- original.txt "$work_dir/soft.txt"
ls -li -- "$work_dir/original.txt" "$work_dir/hard.txt" "$work_dir/soft.txt"
stat -c '%n: device=%d inode=%i links=%h type=%F' -- \
    "$work_dir/original.txt" "$work_dir/hard.txt" "$work_dir/soft.txt"

printf '\n2. Сама символическая ссылка и её цель\n'
readlink -- "$work_dir/soft.txt"
readlink -e -- "$work_dir/soft.txt"
stat -L -c '%n: inode=%i links=%h type=%F' -- "$work_dir/soft.txt"

printf '\n3. Изменение через hard link видно через остальные имена\n'
printf 'Added through hard link\n' >> "$work_dir/hard.txt"
cat -- "$work_dir/original.txt"
cat -- "$work_dir/soft.txt"

printf '\n4. Копия — отдельный файл\n'
cp -- "$work_dir/original.txt" "$work_dir/copy.txt"
printf 'Only in copy\n' >> "$work_dir/copy.txt"
stat -c '%n: inode=%i links=%h' -- "$work_dir/original.txt" "$work_dir/copy.txt"
printf 'Исходный файл:\n'
cat -- "$work_dir/original.txt"
printf 'Копия:\n'
cat -- "$work_dir/copy.txt"

printf '\n5. Переименование сохраняет hard link и ломает путь soft link\n'
mv -- "$work_dir/original.txt" "$work_dir/renamed.txt"
cat -- "$work_dir/hard.txt"
if [[ -L "$work_dir/soft.txt" && ! -e "$work_dir/soft.txt" ]]; then
    printf 'soft.txt существует, но её цель отсутствует\n'
else
    printf 'Ошибка примера: ожидалась битая ссылка\n' >&2
    exit 1
fi
mv -- "$work_dir/renamed.txt" "$work_dir/original.txt"
printf 'После восстановления имени soft link снова работает:\n'
cat -- "$work_dir/soft.txt"

printf '\n6. Замена файла по прежнему пути меняет inode\n'
printf 'Replacement version\n' > "$work_dir/replacement.txt"
mv -f -- "$work_dir/replacement.txt" "$work_dir/original.txt"
printf 'Hard link показывает старые данные:\n'
cat -- "$work_dir/hard.txt"
printf 'Soft link показывает новый файл:\n'
cat -- "$work_dir/soft.txt"
stat -c '%n: inode=%i links=%h' -- "$work_dir/original.txt" "$work_dir/hard.txt"

printf '\n7. Удаление имени файла оставляет старую hard link доступной\n'
rm -- "$work_dir/original.txt"
cat -- "$work_dir/hard.txt"
printf 'Удаляем битую soft link, затем последнее имя старого файла\n'
rm -- "$work_dir/soft.txt"
rm -- "$work_dir/hard.txt"
printf 'Независимая копия осталась:\n'
cat -- "$work_dir/copy.txt"

printf '\n8. Относительная ссылка сохраняется при переносе всего дерева\n'
mkdir -p "$work_dir/package/data" "$work_dir/package/links"
printf 'Portable data\n' > "$work_dir/package/data/message.txt"
ln -s -- ../data/message.txt "$work_dir/package/links/message"
mv -- "$work_dir/package" "$work_dir/moved-package"
readlink -- "$work_dir/moved-package/links/message"
cat -- "$work_dir/moved-package/links/message"

printf '\n9. Удаление ссылки на каталог сохраняет настоящий каталог\n'
mkdir "$work_dir/real-directory"
printf 'Keep me\n' > "$work_dir/real-directory/keep.txt"
ln -s -- real-directory "$work_dir/directory-link"
cat -- "$work_dir/directory-link/keep.txt"
rm -- "$work_dir/directory-link"
test -f "$work_dir/real-directory/keep.txt"
printf 'Файл в настоящем каталоге остался\n'

printf '\n10. Символическую ссылку можно создать до появления цели\n'
ln -s -- future.txt "$work_dir/future-link"
readlink -- "$work_dir/future-link"
if [[ -L "$work_dir/future-link" && ! -e "$work_dir/future-link" ]]; then
    printf 'Пока цель отсутствует, ссылка битая\n'
else
    printf 'Ошибка примера: ожидалась битая ссылка\n' >&2
    exit 1
fi
printf 'Target now exists\n' > "$work_dir/future.txt"
readlink -e -- "$work_dir/future-link"
cat -- "$work_dir/future-link"

printf '\n11. Поиск символических ссылок\n'
find "$work_dir" -type l -print

printf '\nПримеры завершены. Временный каталог будет удалён при выходе.\n'
