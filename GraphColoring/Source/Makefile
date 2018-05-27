#AEDS III: Trabalho Pratico 3 - Coloracao de Grafos
#Vinicius de Oliveira Silva

CC	= gcc
CFLAGS	= -g -Wall
CCFLAGS = -lpthread
LIBS	= -lm
OBJS 	= Graph.o IOHandler.o AdjList.o PaintUtils.o TP3.o

all: TP3

TP3: $(OBJS)
	$(CC) $(CFLAGS) $(CCFLAGS) $(OBJS) -o $@ $(LIBS)

TP3.o: TP3.c
	$(CC) $(CFLAGS) -c TP3.c

Graph.o: Graph.h
Graph.o: Graph.c
	$(CC) $(CFLAGS) -c Graph.c

IOHandler.o: IOHandler.h
IOHandler.o: IOHandler.c
	$(CC) $(CFLAGS) -c IOHandler.c

AdjList.o: AdjList.h
AdjList.o: AdjList.c
	$(CC) $(CFLAGS) -c AdjList.c

PaintUtils.o: PaintUtils.h
PaintUtils.o: PaintUtils.c
	$(CC) $(CFLAGS) -c PaintUtils.c

clean:
	rm *.o