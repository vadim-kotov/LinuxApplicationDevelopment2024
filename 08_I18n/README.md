Сборка и установка: autoreconf -fisv && ./configure --prefix <your location> && make && make install
Запуск: /<your location>/bin/guess

Обновление перевода: make -C po update-po
Удаление генератов: make gitclean
