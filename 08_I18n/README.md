Сборка и установка: 

    autoreconf -fisv && ./configure --prefix YOUR_PATH && make && make install

Запуск: 

    /YOUR_PATH/bin/guess

Обновление перевода: 

    make -C po update-po

Удаление генератов: 

    make gitclean
