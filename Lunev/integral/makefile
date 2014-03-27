#Constants
##Flags
CFLAGS = -g -Wall 
##Libs
CLIB = -lm -lpthread

#Main Goal
main: main.o v_dIntegral.o v_parser.o 
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

#Dependences
main.o: main.c v_dIntegral.h
	$(CC) -c $(CFLAGS) $< $(CLIB)

v_dIntegral.o: v_dIntegral.c v_dIntegral.h v_parser.h
	$(CC) -c $(CFLAGS) $< $(CLIB)

v_parser.o: v_parser.c v_parser.h
	$(CC) -c $(CFLAGS) $< $(CLIB)


#support
clean:
	rm -rf *.o main
