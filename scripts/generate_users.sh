#!/bin/bash

# Переход в корень проекта
cd "$(dirname "$0")/.." || exit 1

# Удаление старого файла (если существует)
if [ -f "users_db.txt" ]; then
    rm "users_db.txt"
    echo "Удалён старый users_db.txt"
fi

# Проверка существования программы
if [ ! -f "bin/PassGenTerm" ]; then
    echo "Ошибка: программа PassGenTerm не найдена в bin/"
    echo "Сначала скомпилируйте проект:"
    echo "g++ -std=c++17 -Iinclude src/*.cpp -o bin/PassGenTerm"
    exit 1
fi

# Генерация 100 записей
for i in {1..100}; do
    echo "user$i:$(bin/PassGenTerm -a -m 12 -x 16)"
done > users_db.txt

echo "Готово! Результат записан в users_db.txt"