PRJ_NAME = BhiCheck
CC = gcc

all:main.o bmp390.o
	$(CC) -Wall -Wconversion $? -o $(PRJ_NAME)

%.o:%.c
	$(CC) -Wall -Wconversion -c $<

clean:
	rm -rf *.o
	rm $(PRJ_NAME)
