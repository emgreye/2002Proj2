# A Makefile to build trove
# adapted from lecture 17

PROJECT =  trove
HEADERS =  $(PROJECT).h
OBJ     =  trove.o tbd.o


C11     =  cc -std=c11
CFLAGS  =  -Wall -Werror -pedantic


$(PROJECT) : $(OBJ)
       $(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm


%.o : %.c $(HEADERS)
       $(C11) $(CFLAGS) -c $<

clean:
       rm -f $(PROJECT) $(OBJ)
