# A Makefile to build trove
# adapted from lecture 17

PROJECT =  trove
HEADERS =  $(PROJECT).h
OBJ     =  trove.o file1.o build.o compression.o filenames.o findfiles.o findwords.o globals.o remove.o trovefile.o update.o words.o


C11     =  cc -std=c11
CFLAGS  =  -Wall -Werror -pedantic


$(PROJECT) : $(OBJ)
		$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm


%.o : %.c $(HEADERS)
		$(C11) $(CFLAGS) -c $<

clean:
		rm -f $(PROJECT) $(OBJ)
