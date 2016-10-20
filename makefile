OPTS = -std=c99 -g -Wall
OBJS = trees.o bst.o fatal.o scanner.o queue.o avl.o node.o stats.o
trees : $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees
trees.o : trees.c bst.h
	gcc $(OPTS) -c trees.c
bst.o : bst.h bst.c queue.h node.h
	gcc $(OPTS) -c bst.c
fatal.o : fatal.h fatal.c
	gcc $(OPTS) -c fatal.c
scanner.o : scanner.h scanner.c
	gcc $(OPTS) -c scanner.c
queue.o : queue.h queue.c bst.h node.h
	gcc $(OPTS) -c queue.c
avl.o : avl.h avl.c queue.h node.h
	gcc $(OPTS) -c avl.c
node.o : node.h node.c
	gcc $(OPTS) -c node.c
stats.o: stats.h stats.c queue.h bst.h
	gcc $(OPTS) -c stats.c
clean : 
	rm -rf $(OBJS) trees
test : trees
	@echo Include testing inputs
