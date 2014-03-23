#Constants
##Flags
CFLAGS = -g -Wall

#Main Goal
main: main.o v_parser.o
	$(CC) $(CFLAGS) $^ -o $@

#Dependences
main.o: main.c v_parser.h
	$(CC) -c $(CFLAGS) $<

v_parser.o: v_parser.c v_parser.h
	$(CC) -c $(CFLAGS) $< 


#support
clean:
	rm -rf *.o main
