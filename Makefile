CC = gcc
CFLAGS = -Wall
OBJ = main.o lista.o pcv.o
EXEC = programa

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

main.o: main.c cidade.h lista.h pcv.h
	$(CC) $(CFLAGS) -c main.c -o main.o

lista.o: lista.c lista.h cidade.h
	$(CC) $(CFLAGS) -c lista.c -o lista.o

pcv.o: pcv.c pcv.h lista.h
	$(CC) $(CFLAGS) -c pcv.c -o pcv.o

run: $(EXEC)
	./$(EXEC) input.in
clean:
	rm -f $(EXEC) $(OBJ)
