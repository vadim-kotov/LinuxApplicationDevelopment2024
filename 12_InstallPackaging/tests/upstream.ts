#include <check.h>
#include "libroman.h"

#tcase get_roman_numeral_test
#test get_roman_invalid_args
	char *res = get_roman_numeral(-1);
	ck_assert_ptr_null(res);

	res = get_roman_numeral(1000);
	ck_assert_ptr_null(res);

#test get_roman_valid_args
	char *res = get_roman_numeral(54);
	ck_assert_str_eq(res, "LIV");

	res = get_roman_numeral(1);
	ck_assert_str_eq(res, "I");

	res = get_roman_numeral(100);
	ck_assert_str_eq(res, "C");

#tcase get_arabic_numeral_test
#test get_arabic_invalid_args
	int res = get_arabic_numeral("foo");
	ck_assert_int_eq(res, -1);

	res = get_arabic_numeral("IIII");
	ck_assert_int_eq(res, -1);

	res = get_arabic_numeral("CI");
	ck_assert_int_eq(res, -1);

#test get_arabic_valid_args
	int res = get_arabic_numeral("LXXXVIII");
	ck_assert_int_eq(res, 88);

	res = get_arabic_numeral("I");
	ck_assert_int_eq(res, 1);

	res = get_arabic_numeral("C");
	ck_assert_int_eq(res, 100);
