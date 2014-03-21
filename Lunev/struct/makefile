R = ar
ARFLAGS = rcs

main: main.o V_VarLArray.o
	$(CC) -g -Wall  $^ -o $@

main.o: main.c V_VarLArray.h
	$(CC) -c  $<
V_VarLArray.a: V_VarLArray.o
	$(AR) $(ARFLAGS) $@ $^ 
V_VarLArray.o: V_VarLArray.c V_VarLArray.h
	$(CC) -c  $<

clean:
	rm *.o *.c.gcov *.gcda *.gcno main

