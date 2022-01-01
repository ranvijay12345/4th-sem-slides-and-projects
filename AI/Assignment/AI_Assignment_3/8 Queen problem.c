#include<stdio.h>
#include<math.h>
#include<time.h>


#define N 8

void configureRandoml ( int board[][N], int *state)
{
   // srand(time(0));

    for(int i = 0; i< N; i++)
    {
     //   state[i] = rand() % N;  

        board[state[i]][i] = 1;  

    }
}

void printBoard(int board[][N])   
{
    for(int i = 0; i< N; i++)
    {
        printf(" ");

        for(int j =0;j < N; j++)
        {
            printf("%d ",&board[i][j]);
        }
        printf("\n");
    }
}

void printState(int *state)   
{
    for(int i = 0; i < N; i ++)
    {
        printf(" %d ",&state[i]);

    }
}

bool compareStates(int *state1, int *state2)  
{
    for (int i = 0; i < N; i++) {
        if (state1[i] != state2[i]) {
            return false;
        }
    }
    return true;
}

void fill(int board[][N], int value) 
{
    for(int i = 0;i < N; i++)
    {
        for(int j = 0; j < N ; j++)
        {
            board[i][j] = value;
        }
    }
}

int calculateObjectve(int board[][N], int * state)  
{

    // Number of queen attacking to each other initially zero

    int attacking = 0;

    // variables to index to a particular row and column on the board

    int row, col;

    for(int i=0;i<N:i++)
    {

        row = state[i],col = i - 1;
        while(col >= 0 && board[row][col] != 1)
        {
            col --;
        }

        if(col >= 0 && board[row][col] == 1)
        {
            attacking ++;
        }

        row = state[i], col = i + ;

        while(col < N && board[row][col] != 1)
        {
            col ++;
        }
        if (col < N
            && board[row][col] == 1) {
            attacking++;
        }

        //

        row = state[i] - 1, col = i - 1;
        while (col >= 0 && row >= 0
               && board[row][col] != 1) {
            col--;
            row--;
        }
        if (col >= 0 && row >= 0
            && board[row][col] == 1) {
            attacking++;
        }

        // 

        row = state[i] + 1, col = i + 1;
        while (col < N && row < N
               && board[row][col] != 1) {
            col++;
            row++;
        }
        if (col < N && row < N
            && board[row][col] == 1) {
            attacking++;
        }

        // 

        row = state[i] + 1, col = i - 1;
        while (col >= 0 && row < N
               && board[row][col] != 1) {
            col--;
            row++;
        }
        if (col >= 0 && row < N
            && board[row][col] == 1) {
            attacking++;
        }

        // 

        row = state[i] - 1, col = i + 1;
        while (col < N && row >= 0
               && board[row][col] != 1) {
            col++;
            row--;
        }
        if (col < N && row >= 0
            && board[row][col] == 1) {
            attacking++;
        }
    }

    // Return pairs.

    return (int)(attacking / 2);

}

void generateBoard(int board[][N],int* state) // a function that generate a board configuration to the given state
{

    fill(board, 0);
    for (int i = 0; i < N; i++) {
        board[state[i]][i] = 1;
    }
}
void copyState(int* state1, int* state2) // copy the content state1 to state2
{

    for (int i = 0; i < N; i++) {
        state1[i] = state2[i];
    }
}

void getNeighbour(int board[][N],
                  int* state)
{
    

    int opBoard[N][N];
    int opState[N];

    copyState(opState,
              state);
    generateBoard(opBoard,
                  opState);

    

    int opObjective
        = calculateObjective(opBoard,
                             opState);

    

    int NeighbourBoard[N][N];
    int NeighbourState[N];

    copyState(NeighbourState,
              state);
    generateBoard(NeighbourBoard,
                  NeighbourState);

    

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            

            if (j != state[i]) {

                

                NeighbourState[i] = j;
                NeighbourBoard[NeighbourState[i]][i]
                    = 1;
                NeighbourBoard[state[i]][i]
                    = 0;

                // Calculating the objective
                // value of the neighbour.

                int temp
                    = calculateObjective(
                        NeighbourBoard,
                        NeighbourState);

                

                if (temp <= opObjective) {
                    opObjective = temp;
                    copyState(opState,
                              NeighbourState);
                    generateBoard(opBoard,
                                  opState);
                }

                

                NeighbourBoard[NeighbourState[i]][i]
                    = 0;
                NeighbourState[i] = state[i];
                NeighbourBoard[state[i]][i] = 1;
            }
        }
    }

    

    copyState(state, opState);
    fill(board, 0);
    generateBoard(board, state);
}

void hillClimbing(int board[][N],
                  int* state)
{

    // Declaring  and initializing the
    // neighbour board and state with
    // the current board and the state
    // as the starting point.

    int neighbourBoard[N][N] = {};
    int neighbourState[N];

    copyState(neighbourState, state);
    generateBoard(neighbourBoard,
                  neighbourState);

    do {

        // Copying the neighbour board and
        // state to the current board and
        // state, since a neighbour
        // becomes current after the jump.

        copyState(state, neighbourState);
        generateBoard(board, state);

        // Getting the optimal neighbour

        getNeighbour(neighbourBoard,
                     neighbourState);

        if (compareStates(state,
                          neighbourState)) {

            

            printBoard(board);
            break;
        }
        else if (calculateObjective(board,
                                    state)
                 == calculateObjective(
                        neighbourBoard,
                        neighbourState)) {

            

            // Random neighbour
            neighbourState[rand() % N]
                = rand() % N;
            generateBoard(neighbourBoard,
                          neighbourState);
        }

    } while (true);
}

 int main()
{

    int state[N] = {};
    int board[N][N] = {};

    // Getting a starting point by
    // randomly configuring the board

    configureRandomly(board, state);

    //  hill climbing 

    hillClimbing(board, state);

    return 0;
}
