#include <check.h>
#include "libbuf.h"

/* initialization, buf_free() */
#test initialization, buf_free()
    float *a = 0;

    //TEST("capacity init", buf_capacity(a) == 0);
    ck_assert_int_eq(buf_capacity(a), 0);

    //TEST("size init", buf_size(a) == 0);
    ck_assert_int_eq(buf_size(a), 0);

    buf_push(a, 1.3f);

    //TEST("size 1", buf_size(a) == 1);
    ck_assert_int_eq(buf_size(a), 1);
    
    //TEST("value", a[0] == (float)1.3f);
    ck_assert_float_eq(a[0], 1.3f);

    buf_clear(a);

    //TEST("clear", buf_size(a) == 0);
    ck_assert_int_eq(buf_size(a), 0);

    //TEST("clear not-free", a != 0);
    ck_assert_float_ne(a, 0);

    buf_free(a);
    //TEST("free", a == 0);
    ck_assert_float_eq(a, 0);
