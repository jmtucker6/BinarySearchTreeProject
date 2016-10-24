OBJS = avlchecker.o queue.o avl.o scanner.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

avlchecker : $(OBJS)
		gcc $(LOPTS) -o avlchecker $(OBJS)

avlchecker.o :	avlchecker.c queue.h avl.h
		gcc $(OOPTS) avlchecker.c

queue.o :	queue.c queue.h avl.h
		gcc $(OOPTS) queue.c

avl.o :	avl.c avl.h
		gcc $(OOPTS) avl.c

scanner.o	: scanner.c scanner.h
		gcc $(OOPTS) scanner.c

test : avlchecker
		avlchecker testfile

clean	:
		rm -f $(OBJS) avlchecker
