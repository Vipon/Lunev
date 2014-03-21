#include <stdlib.h>
       #include <limits.h>
       #include <stdio.h>
       #include <errno.h>

       int get (int argc, char *argv[])
       {
           int base;
           char *endptr, *str;
           long val;

           if (argc < 2) {
               fprintf(stderr, "Usage: %s str [base]\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           str = argv[1];
           base = (argc > 2) ? atoi(argv[2]) : 10;

           errno = 0;    /* To distinguish success/failure after call */
           val = strtol(str, &endptr, base);
              
           
           
       }

   
