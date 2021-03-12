#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void intrographic();		//It prints the opening graphic


void trilizathegame();	//It prints the graphic with the analysis of the game and the gameplay rules


void printarray(int A[][3]);	//Prints the array. Checks


int winnerchecker(int A[][3]);		/*Checks who is the winner and returns 1 if human wins or -1 if pc wins*/


int firstplayer();		/*Generates a random number with the use of which is decided who will play first */


int validationcheck(int row,int col,int A[][3])	;	/*Checks if inputs are correct*/


/*This is the first strategy of the pc. */
int winingsquare(int A[3][3],int *check,int *pi,int *pj);		/*It plays it character in the square that wins the game, if there is one*/


/*Second strategy of the pc.*/	
int opponentcut(int A[][3],int *check,int *pi,int *pj);/*Checks if there is a row/column/diagonal/counterdiagonal with sum of 2 and finds the empty square in order to put in it the value -1 and prevent opponent from winning*/


/*Third pc strategy.*/
int middlesquare (int *pi,int *pj,int A[][3],int *check);	/*It plays the middle square,if it is free*/


/*Fourth pc strategy*/
int twoinarow(int A[3][3],int *check,int *pi,int *pj);	/*This strategy,if none of the previous has been activated,checks if it is possible to put two squares in a row*/


/*Fifth strategy.*/
int edgesquare(int A[3][3],int *check,int *pi,int *pj);	/*In this strategy pc checks if the squares in the edges are empty. And if so,it occupies one of them*/


/*Sixth strategy*/ 
int othersquare(int A[3][3],int *check,int *pi,int *pj);	/*If none of the previous strategies gets activated, pc checks if there is an empty square in the whole array, in order to occupie it*/


/*This pclogic function is called in the main function whenever it's pc's round.This function itself calls the 6 previous function,and enters in only one
of them at a time.It enters in the one that must be used and using the check variable it does not enter in no one else ''*/		
int pclogic(int A[3][3],int *pi,int *pj);


		/********************************************************************************************************************
		 *                                                                                                                  *
		 *												MAIN STARTS!!!!														*
		 *																													*
		 *******************************************************************************************************************/
		 
		
		
																																
main ()				/*row inserted by the user is row=i+1 and for columns col=j+1*/
{		/*initialisation of variables*/
	int A[3][3],fp,row,col,i,pi,pj,winner,check,j,turn=0,gamenum=0,w=0,l=0,d=0,k=0,bestmoves=10,bestgame=0,bestdur=0,worstgame=0,worstdur,worstmoves=10;
	float avgdur=0,avgmov=0;
	char play='y';			/*Initializes this variable at 'y' so as not to exit while loop imediately after the first round*/
	time_t t,t1,t2;
	struct					/*Struct-array initialization*/
	{
		int result;	
		int moves;
		int duration;
	}statistics[500];
	
	statistics[0].moves=0;	/*the counter of the moves for the statistics in initialized with value Zero*/
	
	intrographic();				/*Prints the first graphic*/
	system("pause");
	system("cls");
	trilizathegame();			/*Prints game analysis graphic*/
	system("pause");
	system("cls");				/*Clears black screen*/
	
	
	do
	{
		
		if (turn==0)
		{
			t1=0;				/*initialization of the variable that holds the time that the game starts.This variable must be initialized everytime a new game starts*/
			t2=0;				/*initialization of the variable that holds the time that the game finishes. This variable must be initialized everytime a new game stasrts*/
			t1=time(NULL);		/*t1 gets the clock time when the game starts*/
			fp=firstplayer();;	/*call of the function that picks "randomly" the fist player*/
	
		
			
	
			for(i=0;i<=2;i++)	/*Initialisation of the array A everytime a new game starts*/
			{
				for(j=0;j<=2;j++)
				{
					A[i][j]=0;		/*The array is filled with Zeros*/
				}	
		
			}
		}
		
		if (turn==0 && fp==1)	/*The display in the first round, whenever the player plays first*/
		{
			printf("\tTic-Tac-Toe\n\n");
			printarray(A);	
		}
		
		if(fp==1)		/*Each time it's players turn, he is asked to give a valid combination of row and column numbers*/
		{
			do{
				printf("\nPlease enter a valid choice (row,col):\n");	
				scanf("%d %d",&row,&col);								
				fflush(stdin);											/*cleans the input buffer*/
	
				
			}while (validationcheck(row,col,A)==-1);		/*Checks if the numbers given are valid and chosen square is empty
															.If not it continously asks for new,valid inputs*/
			A[row-1][col-1]=1;								/*row inserted by the user is row=i+1 and for columns col=j+1*/
			fp=2;											/*After the first random pick,variable fp indicates the next player,if fp=1; the next player will be human,otherwise if fp=2, next player will be pc*/
			statistics[k].moves=statistics[k].moves+1;		/*Saves into the moves variable of the struct the number of moves player has playied in each game (game k=1 game k=2 etc...)*/
		}
		else
		{
			pclogic(A,&pi,&pj);	/*Pc logic is called, completes some checks, and picks the suitable strategy as explained*/
			fp=1;				/*fp variable in changes so as the next player will be the human*/
		}
		turn=turn+1;			/* a counter that indicates the turns,in order to indicate later when it is a draw*/
		system("cls");			/*clears the blackscreen*/
		printf("\tTic-Tac-Toe");	
		printf("\n\n");
		printarray(A);	/*prints the array as it is in the end of each turn*/
		t2=time(NULL);	/*hold the time that the game finishes because it's last value is taken when the game finishes*/
		
		
	
		if(turn==1 && fp==1)	/*in the first turn and if the player plays first special messages must be shown on the black screen*/
		{
			printf("\n-You haven't played yet.\n");
			printf("-Computer's last valid choice is:(%d,%d)\n\n",pi+1,pj+1);
		}
		else if (turn!=1)	/*in every other turn the messages are almost the same*/
		{
			printf("\n-Your last valid choice is (X):(%d,%d)\n",row,col);
			printf("-Computer's last valid choice is (O):(%d,%d)\n\n",pi+1,pj+1);	
		}
		
		winner=winnerchecker(A);/*if winner takes the value 1 ,human wins, if the value returned in the variable is -1,pc wins,if the value is 0 it's a draw*/
		statistics[k].result=winnerchecker(A);	/*This variable saves the result of each game into the struct*/
		
		
		
		/*in the following lines,the program checks who is the winner and shows the appropriate message*/
		if(winner==1)
		{
			printf("The game has finished. You win!\n\n");
			w=w+1;	/*Saves the total wins in the session ,in order to indicate them at the final statistics*/
		}
		else if(winner==-1)
		{
			printf("The game is over. You lose!\n\n");
			l=l+1;	/*Saves the total losses in the session, in order to indicate them at the final statistics*/
		}
		else if(turn==9)
		{
			printf("It's a Draw!!\n\n");
			d=d+1;	/*Saves the total draws in the session*/
		}
	
		if(winner==-1 || winner==1 || turn==9)	/*in the end if there is a result the programme asks the user if he wants to play again and awaints for an answer of (y) for yes or (n) for no*/
		{
			statistics[k].duration=t2-t1;
			gamenum=gamenum+1;		/*This variable is used later in order to show the total number of games*/
			k=k+1;					/*this counter variable is used in order to increase the struct-array variables*/
			do{						/*This do-while is used,in order to check if the inputs are correct*/
			printf("Do you wish to play again?(y/n):");
			scanf("%c",&play);
			fflush(stdin);
			}while(play!='y' && play!='n');
			turn=0;						/*if a games is finished turn variable must be initialised with the value 0 in order to start the counting from the begining in the next game*/
			system("cls");
		
		}
		
		
		
	}
	while (play=='y');	/*if n is chosen the game exits and shows some statistics of each played game,some total statistics, and also statistics for the best and worst game*/
	


/*-------------------------CREATING AND PRINTING STATISTICS-----------------------------*/	
	
	
	for(k=0;k<=gamenum-1;k++)		/*Statistics for the best game*/
	
	{
		if(w>0 && statistics[k].result==1)	/*if there is at last one win program enters*/
		{
			if(statistics[k].moves<bestmoves) /*Variable bestmoves is initialised with tha value 10 which will always be higher than the moves made in the game
												for k=0 the programe everytime enters in the first if. Next for k>0 if moves made in the next game are less
												than in the previous it will enter in the first if. Else if there is a difference in the duration it will
												enter the second if and change the values of the variables*/
			
			{
				bestmoves=statistics[k].moves;
				bestgame=k+1;					
				bestdur=statistics[k].duration;
			}
			else if (statistics[k].moves==bestmoves && statistics[k].duration<bestdur)
			{
				bestdur=statistics[k].duration;
				bestgame=k+1;
			}
		}
		
		if(l>0 && statistics[k].result==-1)	/*This works exactly the same way previous lines worked for the best games. This is about the worst game*/
		{
			if(statistics[k].moves<worstmoves )
			{
				worstmoves=statistics[k].moves;
				worstgame=k+1;				/*k+1 because k counter starts counting from zero*/
				worstdur=statistics[k].duration;
			}
		else if(statistics[k].moves==worstmoves && statistics[k].duration<worstdur)
		{
			worstdur=statistics[k].duration;
			worstgame=k+1;	
		}
		}
	
		printf("Game Number:%d\n",k+1);
		if(statistics[k].result==1)		/*The display in the result field changes depending on the result of the game.*/
		printf("Result:Win\n");
		else if(statistics[k].result==0)
		printf("Result:Draw\n");
		else if(statistics[k].result==-1)
		printf("Result:Defeat\n");
		printf("Moves:%d\n",statistics[k].moves);
		printf("Duration:%d\n\n",statistics[k].duration);
		
		avgmov=avgmov+statistics[k].moves;	/*At the beginning,in variable avgmov we sum all the moves made in all the games played on this session*/
		avgdur=avgdur+statistics[k].duration;	/*Exactly the same with above is also done with the variable avgdur */
	}	
		avgmov=avgmov/gamenum;	/*After that in the variable avgmov we save the previous value of avgmov(calculated above,it is the total of moves in every game,)divided by the total number of games.
								 This gives us the average moves per game quantinty saved in avgmov variable.Avgdur works exactly the same way with avgmove*/		
		avgdur=avgdur/gamenum;	 
	
	/*The following lines print the statistics on the black screen*/
	printf("Total Games:%d\n",gamenum);			
	printf("Total Wins:%d\n",w);
	printf("Total Loses:%d\n",l);
	printf("Total Draws:%d\n",d);
	printf("Average Moves per Game:%f\n",avgmov);
	printf("Average duration per Game:%f sec\n\n",avgdur);
	if(w>0)	/*The statistics for the best game are only shown when there is at least one win*/
	{
		printf("Best Game!\n----------\n");
		printf("Game Number:%d\n",bestgame);
		printf("Moves:%d\n",bestmoves);
		printf("Duration:%d sec\n\n",bestdur);
	}
	if(l>0)	/*The statistics for the worst game are only shown when there is at least one defeat*/
	{
		printf("Worst Game!\n-----------\n");
		printf("Game Number:%d\n",worstgame);
		printf("Moves:%d\n",worstmoves);
		printf("Duration:%d sec\n\n",worstdur);
	}
	system("pause");
		
}






void intrographic()		//It prints the opening graphic
{
	printf("----------------------------------------------------------------------------\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                              Welcome To:                                 |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|      #######  #  ####  #######    #      ####  #######  #####  ####      |\n");
	printf("|         #     #  #        #      # #     #        #     #   #  #         |\n");
	printf("|         #     #  #        #     #   #    #        #     #   #  ###       |\n");
	printf("|         #     #  #        #    #######   #        #     #   #  #         |\n");
	printf("|         #     #  ####     #   #       #  ####     #     #####  ####      |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("----------------------------------------------------------------------------\n");
	
}

void trilizathegame()	//It prints the graphic with the analysis of the game and the gameplay rules
{
	printf("----------------------------------------------------------------------------\n");
	printf("|                              Tic-Tac-Toe:                                |\n");
	printf("|                                The Game.                                 |\n");
	printf("|                                                                          |\n");
	printf("|       In this game you have to give the right coordinates,               |\n");
	printf("|       of the 3x3 grid shown, from your keyboard (row,column),            |\n");
	printf("|       in order to succeed in placing three respective marks              |\n");
	printf("|       in a horizontal ,vertical, or diagonal row and finally win!        |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                    !!!IMPORTANT GAMEPLAY WARNING!!!                      |\n");
	printf("|                                                                          |\n");
	printf("|       Row and Column must be sepperated by the 'ENTER' key or            |\n");
	printf("|       by a void between them (created by the 'SPACE' key)!!              |\n");
	printf("|       Row and Column inputs seperated with comma (,) will                |\n");
	printf("|       NOT function properly!                                             |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("|                                                                          |\n");
	printf("----------------------------------------------------------------------------\n");
}
void printarray(int A[][3])	//Prints the array. Checks if the numbers are -1 0 1 and prints the appropriate symbol O/' '/X
{ 								
	char x;
	int i,j;
	
	for (i=0;i<=2;i++)
	
	{
		for(j=0;j<=2;j++)
		{
			if (A[i][j]==1) x='X';
			else if (A[i][j]==-1) x='O';
			else x=' ';
			
			if (j==1) printf(" %c *",x);
			else if (j==0) printf("\t %c *",x);
			else 
			{
				if(i!=2) printf(" %c\n\t *********\n",x);	/*The scheme with the stars that sepperate X/' '/O is created*/
				else printf(" %c\n",x);
			}
		}
	}
}

int winnerchecker(int A[][3])		/*Checks who is the winner and returns 1 if human wins or -1 if pc wins(the values of done)*/
{
	int i,j,sum1,sum2,sum3,sum4,done=0;
	i=0;
	sum3=0;							/*Sum3 represents the sum of the main diagonal.If it equals -3 , pc wins, else if it equals 3, human wins*/
	sum4=0;							/*Sum4 represents the sum of the antidiagonal.If sum4=-3 pc wins, else if sum4=3 human wins*/
	while (i<=2 && done==0 )
	{
		sum1=0;						/*Sum1 is the sum for the rows and works as sum3 and sum4 do*/
		sum2=0;						/*Sum2 is the sum for the columns*/
		j=0;						/*Note that in the whole programme,whenever used,sum1 is for the rows,sum2 for the columns,sum3 for diagonal and sum4 for diagonal*/
		while(j<=2 && done==0)
		{
			sum1=sum1+A[i][j];		/*calculates sums*/
			sum2=sum2+A[j][i];
			j=j+1;					
		}
		if (sum1==3 || sum2==3)		/*checks if sums are 3 or -3 and gives at done variable the appropriate value*/
		done=1;						
		else if (sum1==-3 || sum2==-3)
		done=-1;
		
		sum3=sum3+A[i][i];			/*calculates sums again for diagonal and counterdiagonal which are depended only by i counter*/
		sum4=sum4+A[i][2-i];
		i=i+1;
	}

if(sum3==3 || sum4==3)				/*and then checks if sums are 3 or -3 and gives at done variable the appropriate value*/
done=1;
else if(sum3==-3 || sum4==-3)
done=-1;


return done;		/*Returns in her name the final value that the variable 'done' has taken*/

}

int firstplayer()		/*Generates a random number */
{
	int r;
	time_t t;
	srand((unsigned) time(&t));		/*clock is used a seed for srand*/
	r=(rand() % 100);		/*Returns random number from zero to 100 */	
	if (r>=50)
	return(1);		/*Human plays first*/
	else
	return(2);		/*Pc plays first*/
}

int validationcheck(int row,int col,int A[][3])		/*Checks if inputs are correct*/
{
	if ((row<=3 && row>=0) && (col<=3 && col>=0) && A[row-1][col-1]==0 )
	return(0);
	else
	{
		if(row<0 || row>3 || col<0 || col>3)		/*Check if the inputs are out of borders*/
		printf("Error Numbers Given.\n\n");
		else if(A[row-1][col-1]!=0)					/*Checks if the selected square is preocuppied*/
		printf("The chosen square is already occupied!\n\n");
		
		return(-1);
	}
	
}
/*This is the first strategy of the pc. Sums are used as previously, in order to calculate the sum of a row,col,diagonal,coutnerdiagonal
Variable check is used so as to break the while loop when needed.Check is also used in order to prevent pc from entering in multiple strategies
at once,at the same turn,(you can see this usage of check variable in the other strategy-fuctions and in the function pc-logic).Check variable is used as a pointer
in the functions because it is also used in the main function*/
int winingsquare(int A[3][3],int *check,int *pi,int *pj)		/*It plays it character in the square that wins the game, if there is one*/
{																/*This is done by checking if in a row/column/diagonal/counterdiagonal there is a sum of -2 and searches for a square in the same row/column/diagonal/counterdiagonal in order to put -1 in it*/
	int j,i=0,sum3=0,sum4=0,sum1,sum2,indicator=0;
	
	
	while (i<=2 && *check==0)	
	{
		sum1=0;
		sum2=0;
		j=0;
 		while(j<=2 && *check==0)		
		{
			sum1=sum1+A[i][j];
			sum2=sum2+A[j][i];
			j=j+1;
		}
		if(sum1==-2 || sum2==-2)		
		{
			*check=1;	/*If after the calculation of sums there is a result and programme enters this 'if', check value is set to 1 in order to break the while loop and prevent it to reenter in another strategy*/
			for(j=0;j<=2;j++)
			{
				if(sum1==-2 && A[i][j]==0)		/*Finds the empty square fills it with -1 and wins the game*/
				{
					A[i][j]=-1;
					*pi=i;		/*Note that pi and pj variables are used like pointers in order to transfer into main the last valid choise of the computer*/
					*pj=j;		/*Those variables are used in every function-pcstrategy throughout the whole programme*/
				}
				else if (sum2==-2 && A[j][i]==0)
				{
					A[j][i]=-1;
					*pi=j;
					*pj=i;
				}
			}
		}
		sum3=sum3+A[i][i];
		sum4=sum4+A[i][2-i];
		i=i+1;
	}
	if((sum3==-2 || sum4==-2) && *check!=1)
	{
		*check=1;
		for(i=0;i<=2;i++)
		{
			if(A[i][i]==0 && sum3==-2 && indicator!=1)	
			{
			A[i][i]=-1;
			*pi=i;
			*pj=i;
			indicator=1;
			}
			else if(A[i][2-i]==0 && sum4==-2 && indicator!=1)
			{
			A[i][2-i]=-1;
			*pi=i;
			*pj=(2-i);
			indicator=1;
			}
		}
	}
}
/*Second strategy of the pc.Check variable used the same way, in order to break the loop and prevent pc from entering in multiple function at once.
Pointer pi and pj are used in order to keep and transfer to main fucntion the last valid choice of the pc.Pi transfers the last valid row and pj transfers
the last valid column given by the pc*/	
int opponentcut(int A[][3],int *check,int *pi,int *pj)/*Checks if there is a row/column/diagonal/counterdiagonal with sum of 2 and finds the empty square in order to put in it the value -1 and prevent opponent from winning*/
{
	int j,i=0,sum3=0,sum4=0,sum1,sum2,indicator=0;		
	
	while (i<=2 && *check==0)
	{
		sum1=0;
		sum2=0;
		j=0;
 		while(j<=2 && *check!=2)
		{
			sum1=sum1+A[i][j];		/*calculates sums*/
			sum2=sum2+A[j][i];
			j=j+1;
		}
		if(sum1==2 || sum2==2)
		{
			j=0;
			while(j<=2 && *check!=2)
			{
				if(sum1==2 && A[i][j]==0 && *check!=2)  /*Finds the empty square and fills it in order to cut the opponent*/
				{
					A[i][j]=-1;
					*pi=i;
					*pj=j;
					*check=2;
				}
			    if (sum2==2 && A[j][i]==0)
				{
					A[j][i]=-1;
					*pi=j;
					*pj=i;
					*check=2;
				}
				j=j+1;
			}
		}
		sum3=sum3+A[i][i];
		sum4=sum4+A[i][2-i];
		i=i+1;
	}
	if((sum3==2 || sum4==2) && *check!=2)	/*if there is not result for rows and colums the same happes for diagonal and counterdiagonal*/
	{
		*check=2;
		i=0;
		while(i<=2 && indicator!=1)
		{
			if(A[i][i]==0 && sum3==2)
			{
			A[i][i]=-1;
			*pi=i;
			*pj=i;
			indicator=1;	/*indicator is used in order to prevent programme from cuttin both at diagonal or counterdiagonal if there is such a chance*/
			}
			else if(A[i][2-i]==0 && sum4==2)
			{
			A[i][2-i]=-1;
			*pi=i;
			*pj=(2-i);
			indicator=1;
			}
			i=i+1;
		}
	}
}
/*Third pc strategy.If none of the previous strategies have activated,pc checks if the middle square is empty, and if does, it occupies it
otherwise it continius to the next strategy*/
int middlesquare (int *pi,int *pj,int A[][3],int *check)	/*It plays the middle square,if it is free*/
{
	if (A[1][1]==0 && *check==0)
	{
	A[1][1]=-1;
	*check=3;
	*pi=1;
	*pj=1;
	}
}
/*Fourth pc strategy.This strategy,if none of the previous has been activated,checks if it is possible to put two squares in a row*/
int twoinarow(int A[3][3],int *check,int *pi,int *pj)
{
	int indicator=0;		/*indicator is used in order to break the while loop*/
	int i=0,j;

	/*basically this strategy checks all the borders of every single 'O' and finds an empty one in order to put another 'O' and create two-in-a -row */
	
		while (i<=2 && indicator!=1)
		{
			j=0;
			while(j<=2 && indicator!=1)
			{
				if(A[i][j]==-1)
				{
					if(i+1<=2 && A[i+1][j]==0)		/*i+1<2 assures that we dont get out of the table borders*/
					{
						A[i+1][j]=-1;
						indicator=1;
						*check=4;
						*pi=i+1;
						*pj=j;
					}
					else if (i+1<=2 && j+1<=2 && A[i+1][j+1]==0)
					{ 
						A[i+1][j+1]=-1;
						indicator=1;
						*check=4;
						*pi=i+1;
						*pj=j+1;
					}
					else if (j+1<=2 && A[i][j+1]==0)
					{
						A[i][j+1]=-1;
						indicator=1;
						*check=4;
						*pi=i;
						*pj=j+1;
					}
					else if (i-1>=0 && A[i-1][j]==0)
					{
						A[i-1][j]=-1;
						indicator=1;
						*check=4;
						*pi=i-1;
						*pj=j;
					}
					else if (i-1>=0 && j-1>=0 && A[i-1][j-1]==0)
					{
						A[i-1][j-1]=-1;
						indicator=1;
						*check=4;
						*pi=i-1;
						*pj=j-1;
					}
					else if (j-1>=0 && A[i][j-1]==0)
					{
						A[i][j-1]=-1;
						indicator=1;
						*check=4;
						*pi=i;
						*pj=j-1;
					}
					
				
				}
				j=j+1;
			}
			i=i+1;
		}
}
/*Fifth strategy.In this strategy pc checks if the squares in the edges are empty. And if so,it occupies one of them*/
int edgesquare(int A[3][3],int *check,int *pi,int *pj)
{
	int i,j;
	i=0;
	while (i<=2 && *check==0)
	{
		j=0;
		while(j<=2 && *check==0)
		{
			if(A[i][j]==0 && *check==0)
			{
				A[i][j]=-1;
				*check=5;
				*pi=i;
				*pj=j;		
			}
			j=j+2; /*counter i and j are increased by 2 each time, in order to check all the edge squares*/
		}
		i=i+2;
	}
}
/*Sixth strategy. If none of the previous strategies gets activated, pc checks if there is an empty square in the whole array, in order to occupie it*/
int othersquare(int A[3][3],int *check,int *pi,int *pj)
{
	int i,j;
	i=0;
	while(i<=2 && *check==0)
	{
		j=0;
		while(j<=2 && *check==0)
		{
			if (A[i][j]==0)
			{
				A[i][j]=-1;
				*check=6;
				*pi=i;
				*pj=j;
			}
			j=j+1;
		}
		i=i+1;
	}
}
/*This pclogic function is called in the main function whenever it's pc's round.This function itself calls the 6 previous function,and enters in only one
of them at a time.It enters in the one that must be used and using the check variable it does not enter in no one else ''*/		
int pclogic(int A[3][3],int *pi,int *pj)
{
	int check=0;
	winingsquare(A,&check,pi,pj);
	if (check!=1)
	{
		opponentcut(A,&check,pi,pj);
		if (check!=2)
		{		
			middlesquare (pi,pj,A,&check);
			if (check!=3)
			{
				twoinarow(A,&check,pi,pj);
				if (check!=4)
				{
					edgesquare(A,&check,pi,pj);
					if (check!=5)
					othersquare(A,&check,pi,pj);	
				}
			}
		}
	}	
}

	

	



