#all: RepeaterAttackServer
all: test

test: test.cpp
	g++ -std=c++11 test.cpp SimplePRNG.o -o test

SimplePRNG.o: SimplePRNG.cpp SimplePRNG.h
	g++ -std=c++11 -c SimplePRNG.cpp -o SimplePRNG.o

#RepeaterAttackClient: RepeaterAttackClient_v4.c
#	gcc RepeaterAttackClient_v4.c Tunnel_client.c -o RepeaterAttackClient_v4 -lm -lpthread -lpcap 

clean:
	rm test *.o
