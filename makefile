all:
	gcc -Wall -Wshadow -g -lm FEL.h ListNode.h Event.h Queue.h SimulationData.h Server.h main.c -o output
