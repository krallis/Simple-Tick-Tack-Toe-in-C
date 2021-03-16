# Simple-Tick-Tack-Toe-in-C
A very simple implementation of the well known Tic Tac Toe game using C.
The user plays against the PC. The player that starts first in round 1, is selected randomly.

The NPC uses a very simplistic algorithm in order to play its turn.

1. The first step is to check whether there is a winning square available.
2. If not, the algorithm moves to the second step, were it checks whether the opponent is about to win and tries to prevent user's winning move.
3. The third case is to check if the middle square is empty.
4. Checks if it can put two squares in a row.
5. Occupies an edge square.


After the end of each match, the programe asks if the user wants to play another match with the NPC.
Finally the user gets some stats and a score record.
