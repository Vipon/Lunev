R = ar
ARFLAGS = rcs

main: main.o V_VarLArray.o
	$(CC) -g -fprofile-arcs -ftest-coverage -Wall  $^ -o $@

main.o: main.c V_VarLArray.h
	$(CC) -c  -fprofile-arcs -ftest-coverage $<
V_VarLArray.a: V_VarLArray.o
	$(AR) $(ARFLAGS) $@ $^ 
V_VarLArray.o: V_VarLArray.c V_VarLArray.h
	$(CC) -c  -fprofile-arcs -ftest-coverage $<

clean:
	rm *.o *.c.gcov *.gcda *.gcno main

