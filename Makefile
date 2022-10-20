# A Makefile to build trove
# adapted from lecture 17

PROJECT =  trove
HEADERS =  $(PROJECT).h
OBJ     =  trove.o build.o findfiles.o words.o trovefile.o findwords.o remove.o update.o
# To add later to OBJ
# file1.o compression.o filenames.o globals.o

C11     =  cc -std=c11
CFLAGS  =  -Wall -Werror -pedantic


$(PROJECT) : $(OBJ)
		$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm


%.o : %.c $(HEADERS)
		$(C11) $(CFLAGS) -c $<

clean:
		rm -f $(PROJECT) $(OBJ)
