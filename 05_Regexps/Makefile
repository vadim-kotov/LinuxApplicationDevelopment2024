.PHONY:	test clean
GENS = esub
CFLAGS = -Wall -Wextra
TESTS = *.txt

REGEXP-test1 = "((abc)(.))[0-9](abc)"
SUBST-test1 = "<1=\1><2=\2><3=\3><4=\4>"
STRING-test1 = ababcx3abcabc

REGEXP-test2 = "((abc)(.))[0-9](abc)"
SUBST-test2 = "<1=\\\\_\\1\\\\\\1_\\\\_\\1><2=\2><3=\3><4=\4>"
STRING-test2 = abcx3abc

REGEXP-test3 = "((abc)(.))[0-9](abc)"
SUBST-test3 = "<1=\\\\\\1\\\\\\1\\\\\\1><2=\2><3=\3><4=\4>"
STRING-test3 = _abcx3abc_

REGEXP-error-test1 = "((abc(.))[0-9](abc)"
SUBST-error-test1 = "<1=\1><2=\2><3=\3><4=\4>"
STRING-error-test1 = ababcx3abcabc
ERROR-error-test1 = "Regular expression compilation error"

REGEXP-error-test2 = "((abc)(.))[0-9](abc)"
SUBST-error-test2 = "<1=\1><2=\2><3=\3><4=\4><5=\5>"
STRING-error-test2 = abcx3abc
ERROR-error-test2 = "no back reference with number"

REGEXP-error-test3 = "((abc)(.))[0-9](abc)"
SUBST-error-test3 = "<1=\1><2=\2><3=\3><4=\4><5=\5>"
STRING-error-test3 = abbx3abc
ERROR-error-test3 = "Regular expression execution error"

all:	esub

test:	test1 test2 test3 error-test1 error-test2 error-test3 usage-test

test%:	esub
	./esub $(REGEXP-$@) $(SUBST-$@) $(STRING-$@) > $@.out.txt
	/bin/echo $(STRING-$@) | sed -E s/$(REGEXP-$@)/$(SUBST-$@)/ > $@.sed.txt
	diff -us $@.out.txt $@.sed.txt

error-test%:	esub
	./esub $(REGEXP-$@) $(SUBST-$@) $(STRING-$@) 2>&1 | grep -c $(ERROR-$@) > $@.out.txt
	echo 1 > $@.exp.txt
	cmp $@.out.txt $@.exp.txt
	
usage-test:	esub
	./esub xxx xxx 2>&1 | grep -c Usage > $@.out.txt
	echo 1 > $@.exp.txt
	cmp $@.out.txt $@.exp.txt

clean:
	rm -f $(GENS) $(TESTS)
