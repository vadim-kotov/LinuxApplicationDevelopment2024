#!/bin/bash

test_file='configure.ac'
test_str='"qwerty'

test1() {
	res=$(echo "sha1 $test_file" | ./rhasher | sed -z 's/> //g; s/\n//g')
	ref=$(sha1sum "$test_file" | awk '{print $1}')

	if test "$res" = "$ref"; then
		exit 0
	else
		exit 1
	fi
}

test3() {
	res=$(echo "md5 $test_file" | ./rhasher | sed -z 's/> //g; s/\n//g')
	ref=$(md5sum "$test_file" | awk '{print $1}')

	if test "$res" = "$ref"; then
		exit 0
	else
		exit 1
	fi
}

func=$1

if declare -f "$func" > /dev/null; then
	"$func"
else
	echo "Test '$func' not found"
	exit 1
fi
