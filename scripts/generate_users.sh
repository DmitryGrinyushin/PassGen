#!/bin/bash

for i in {1..100}; do
  login="user$i"
  password=$(./bin/PassGenTerm -a -m 12 -x 16)  # Пароль из 12-16 символов
  
  echo "$login:$password" >> users_db.txt
done

echo "Готово! Результат записан в users_db.txt"