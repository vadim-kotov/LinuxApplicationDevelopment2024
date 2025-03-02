.PHONY: test_* clean
GENS=move unlink.so
CFLAGS=-Wall -Wextra
TESTS=*.txt

all:	move unlink.so

move:	move.c

unlink.so:	unlink.c
	$(CC) -shared -fPIC $^ -ldl -o $@

tests: test_noargs test_open_src test_open_dest test_read_src test_write_dest test_close_src test_close_dest test_unlink_src test_protect1 test_protect2

test_%: move
	./test.sh $(subst test_,,$@)

clean:	
	rm -f $(GENS) $(TESTS)
