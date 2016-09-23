OPTS = -std=c99 -g -Wall
OBJS = trees.o bst.o fatal.o scanner.o queue.o
trees : $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees
trees.o : trees.c bst.h
	gcc $(OPTS) -c trees.c
bst.o : bst.h bst.c queue.h
	gcc $(OPTS) -c bst.c
fatal.o : fatal.h fatal.c
	gcc $(OPTS) -c fatal.c
scanner.o : scanner.h scanner.c
	gcc $(OPTS) -c scanner.c
queue.o : queue.h queue.c bst.h
	gcc $(OPTS) -c queue.c
clean : 
	rm -rf $(OBJS) trees
test : trees
	@echo Include testing inputs
