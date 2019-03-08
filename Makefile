CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

test: tests.out
	@./tests.out

rpn_calc: rpn_calc.out
	@./rpn_calc.out

echo_server: echo_server.out
	@./echo_server.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: lib/*.c lib/*.h test/*.c test_main.c
	@$(CC) $(CFLAGS) lib/*.c test/*.c test_main.c -lm -o tests.out

rpn_calc.out: lib/*.c lib/*.h rpn_main.c
	@$(CC) $(CFLAGS) lib/*.c rpn_main.c -o rpn_calc.out

echo_server.out: lib/*.c lib/*.h echo_server_main.c
	@$(CC) $(CFLAGS) lib/simple_server.c echo_server_main.c -o echo_server.out
