Сборка и установка: 

    autoreconf -fisv && ./configure --prefix=YOUR_PATH --disable-doxygen-pdf --disable-doxygen-ps && make && make install

Запуск: 

    /YOUR_PATH/bin/guess

Обновление перевода: 

    make -C po update-po

Читать man:

    man .YOUR_PATH/share/doc/guess/man/man1/guess.1

Поднять сервер с документацией:

    make http

Удаление генератов: 

    make gitclean
