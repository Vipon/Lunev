#Constants
##Flags
CFLAGS = -g -Wall 
##Libs
CLIB = -lm

#Main Goal
main: main.o v_parser.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

#Dependences
main.o: main.c v_parser.h
	$(CC) -c $(CFLAGS) $< $(CLIB)

v_parser.o: v_parser.c v_parser.h
	$(CC) -c $(CFLAGS) $< $(CLIB)


#support
clean:
	rm -rf *.o main
