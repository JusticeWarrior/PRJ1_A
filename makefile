all:
	gcc -Wall -Wshadow -g -lm FEL.c ListNode.c Event.c Queue.c SimulationData.c Server.c Control.c UnitTestSet3.c -o output
