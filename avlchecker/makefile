OBJS = avlchecker.o queue.o avl.o scanner.o

avlchecker : $(OBJS)
		gcc -Wall -g -o avlchecker $(OBJS)

avlchecker.o :	avlchecker.c queue.h avl.h
		gcc -Wall -g -c avlchecker.c

queue.o :	queue.c queue.h avl.h
		gcc -Wall -g -c queue.c

avl.o :	avl.c avl.h
		gcc -Wall -g -c avl.c

scanner.o	: scanner.c scanner.h
		gcc -Wall -g -c scanner.c

clean	:
		rm -f $(OBJS) avlchecker
