#!/usr/bin/env bash

# Запускать из корня проекта:
# bash bash/file/examples.sh

# Тип содержимого: расширение .jpg не делает текст картинкой.
file bash/practice/file/message.txt bash/practice/file/picture.jpg

# Пустой файл и каталог.
file bash/practice/file/empty
file bash/practice/file

# Описание без имени файла.
file -b bash/practice/file/picture.jpg

# MIME-тип.
file --mime-type bash/practice/file/picture.jpg

# Предполагаемая кодировка.
file --mime-encoding bash/practice/file/picture.jpg

# MIME-тип и кодировка вместе.
file --mime bash/practice/file/picture.jpg
