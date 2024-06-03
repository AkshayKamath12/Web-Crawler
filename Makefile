CC = gcc

SOURCE = pagedir.c curl.c url.c bag.c hashtable.c set.c crawler.c
OBJ = pagedir.o curl.o url.o bag.o hashtable.o set.o crawler.o
HEADER = crawler.h curl.h url.h hashtable.h set.h

password_checker: ${OBJ} ${HEADER}
	$(CC) -Wall -Wextra $(OBJ) -lcurl -o runTest

%.o: %.c $(HEADER)
	$(CC) $< -c

clean:
	rm -rf runTest
	rm -rf *.o
