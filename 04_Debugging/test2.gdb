set pagination off

set $num = 1

b 63 if $num++ >= 28 && $num <= 36
command 1
	printf "@@@ %ld %ld %ld %ld\n", M, N, S, i
	cont
end

run -100 100 3 > /dev/null
quit
