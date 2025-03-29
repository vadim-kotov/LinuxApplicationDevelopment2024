Для работы gcov и вывода процента покрытия указать ключ ```--enable-gcov```:

    autoreconf -fisv && ./configure --enable-gcov && make check

Вывод журнала тестирования:

    make checklog

&nbsp;&nbsp;&nbsp;&nbsp;если был указан ключ ```--enable-gcov```, то выведет ещё и процент покрытия

Удаление генератов:

    make gitclean
