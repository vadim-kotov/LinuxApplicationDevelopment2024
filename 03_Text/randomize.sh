#!/bin/bash

sleep_time=0.1
if [ $1 ]; then
	sleep_time=$1
fi

temp=$(mktemp)

IFS=''
Y=0
while read -r str; do
	X=0
	syms="$(echo "$str" | grep -o .)"
	while read -r sym; do
		if [ "$sym" != " " ]; then
			echo "$sym" $X $Y >> $temp
		fi
		X=$((X+1))
	done <<< "$syms"

	Y=$((Y+1))
done

tput clear
IFS=' '
while read -r sym x y; do
	tput cup $y $x
	echo -n "$sym"
	sleep $sleep_time
done <<< "$(shuf $temp)"

rm $temp

tput cup $Y 0
