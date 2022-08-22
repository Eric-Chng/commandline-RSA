OBJS	= rsa.o
SOURCE	= rsa.cpp
HEADER	= 
OUT	= rsa
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

rsa.o: rsa.cpp
	$(CC) $(FLAGS) rsa.cpp 


clean:
	rm -f $(OBJS) $(OUT)