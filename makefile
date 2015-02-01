all:
	gcc -Wall -Wshadow -g -lm FEL.c ListNode.c Event.c Queue.c SimulationData.c Server.c UnitTestSet2.c -o output
