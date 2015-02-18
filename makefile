all:
	gcc $(flags) $(source) main.c -o PRJ1_A

flags = -Wall -Wshadow -g
source = FEL.c ListNode.c Event.c Queue.c SimulationData.c Server.c Control.c -lm
