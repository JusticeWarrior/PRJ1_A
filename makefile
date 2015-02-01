all:
	gcc -Wall -Wshadow -g -lm FEL.c ListNode.c Event.c Queue.c SimulationData.c Server.c UnitTestSet1.c -o output
