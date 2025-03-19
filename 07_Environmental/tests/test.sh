#!/bin/bash

test_file='configure.ac'
test_str='"qwerty'

res=$(echo "sha1 $test_file" | ./rhasher | sed -z 's/> //g; s/\n//g')
ref=$(sha1sum "$test_file" | awk '{print $1}')

if test "$res" != "$ref"; then
	exit 1
fi

res=$(echo "sha1 $test_str" | ./rhasher | sed -z 's/> //g; s/\n//g')
ref=$(echo -n "$test_str" | sha1sum | awk '{print $1}')

if test "$res" != "$ref"; then
	exit 1
fi

res=$(echo "md5 $test_file" | ./rhasher | sed -z 's/> //g; s/\n//g')
ref=$(md5sum "$test_file" | awk '{print $1}')

if test "$res" != "$ref"; then
	exit 1
fi

res=$(echo "md5 $test_str" | ./rhasher | sed -z 's/> //g; s/\n//g')
ref=$(echo -n "$test_str" | md5sum | awk '{print $1}')

if test "$res" != "$ref"; then
	exit 1
fi


exit 0

