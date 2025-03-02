#!/bin/bash

noargs() {
	echo "Test: ./move foo"

	./move foo > /dev/null 2>&1

	if [[ $? -eq 1 ]]; then
		echo OK
	else
		echo FAIL
	fi
}

open_src() {
	echo "Test: error occurs while opening source file"

	strace -e fault=openat:error=EACCES -P in.txt ./move in.txt out.txt > /dev/null 2>&1
	
	if [[ $? -eq 2 && -f "in.txt" && ! -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

open_dest() {
	echo "Test: error occurs while opening destination file"

	strace -e fault=openat:error=EACCES -P out.txt ./move in.txt out.txt > /dev/null 2>&1

	if [[ $? -eq 2 && -f "in.txt" && ! -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

read_src() {
	echo "Test: error occurs while reading file"

	strace -e fault=read:error=EIO -e fd=100 ./move in.txt out.txt > /dev/null 2>&1

	if [[ $? -eq 3 && -f "in.txt" && ! -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

write_dest() {
	echo "Test: error occurs while writing to file"

	strace -e fault=write:error=EAGAIN -e fd=101 ./move in.txt out.txt > /dev/null 2>&1

	if [[ $? -eq 4 && -f "in.txt" && ! -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

close_src() {
	echo "Test: error occurs while closing source file"
	
	strace -e fault=close:error=EIO -e fd=100 ./move in.txt out.txt > /dev/null 2>&1

	if [[ $? -eq 5 && -f "in.txt" && ! -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

close_dest() {
	echo "Test: error occurs while closing destination file"

	strace -e fault=close:error=EIO -e fd=101 ./move in.txt out.txt > /dev/null 2>&1

	if [[ $? -eq 5 && -f "in.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

unlink_src() {
	echo "Test: error occurs while source file removal"

	strace -e fault=unlink:error=EACCES -P in.txt ./move in.txt out.txt > /dev/null 2>&1

	if [[ $? -eq 6 && -f "in.txt" && -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

protect1() {
	echo "Test: library unlink.so LD_PRELOADed and source file has 'PROTECTED' in name"

	cp "move.c" "PROTECTEDfile.txt"
	LD_PRELOAD=`pwd`/unlink.so ./move PROTECTEDfile.txt out.txt

	if [[ $? -eq 0 && -f "PROTECTEDfile.txt" && -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi

	rm -f "PROTECTEDfile.txt"
}

protect2() {
	echo "Test: library unlink.so LD_PRELOADed but source filename w/o 'PROTECTED'"

	LD_PRELOAD=`pwd`/unlink.so ./move in.txt out.txt

	if [[ $? -eq 0 && ! -f "in.txt" && -f "out.txt" ]]; then
		echo OK
	else
		echo FAIL
	fi
}

func=$1

if declare -f "$func" > /dev/null; then
	rm -f "in.txt" "out.txt"
	cp "move.c" "in.txt"

	"$func"

	rm -f "in.txt" "out.txt"
else
	echo "Test "$func" not found"
	exit 1
fi
