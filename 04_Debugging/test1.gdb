set pagination off
b 67 if i % 5 == 0
command 1
	printf "@@@ %ld %ld %ld %ld\n", M, N, S, i
	cont
end

run 1 12 > /dev/null
quit
