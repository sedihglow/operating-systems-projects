CC = gcc
CPPFLAGS = -c -Wall -Wextra -pthread -m64 -O0 -g 
LDFLAGS = -pthread -m64 -g

a.out:					main.o header.o err_handle.o convNum.o
						$(CC) $(LDFLAGS) *.o -o a.out

main.o:					main.c ../utility_sys.h
						$(CC) $(CPPFLAGS) main.c

err_handle.o:			../err_handle/err_handle.c ../utility_sys.h
						$(CC) $(CPPFLAGS) ../err_handle/err_handle.c

convNum.o:				../convNum/convNum.c ../utility_sys.h
						$(CC) $(CPPFLAGS) ../convNum/convNum.c

header.o:				header.c ../utility_sys.h
						$(CC) $(CPPFLAGS) header.c

.PHONY: check
check:					# check for memory leak
						$(info -- Checking For Memory Leaks --)
						valgrind --leak-check=full ./a.out

.PHONY: debug
debug:					# GNU debugger
						$(info -- Debugging --)
						gdb ./a.out

.PHONY: clean
clean:					# clean the directory
						$(info -- Cleaning The Directory --)
						rm -rf *.o a.out

.PHONY: run
run:					# run the program as follows
						$(info -- Running Program --)
						./a.out
