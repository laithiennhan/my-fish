#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Creating the grid data structure with a character to represent the value and pointers to 8 directions around.
struct Grid {
    char data;
    struct Grid * up;
    struct Grid * down;
    struct Grid * left;
    struct Grid * right;
    struct Grid * upLeft;
    struct Grid * upRight;
    struct Grid * downLeft;
    struct Grid * downRight;

};
typedef struct Grid grid;

//Creating the node data structure, which stores a character and a pointer to the next node
struct Node {
    char data;
    struct Node * next;
};
typedef struct Node node;

//Creating the path data structure to store directions and number of steps that the player takes
struct Path {
    char * dir;
    int steps;
};
typedef struct Path path;

//Function to create the grid and set default values
struct Grid * createGrid()
{
   grid* p = (struct Grid *) malloc(36*sizeof(struct Grid));
   for (int i = 0; i < 36; i++){

        (p+i)->right = (p + i + 1);
        (p+i)->left = (p+ i -1);
        (p+i)->up = (p+ i -6);
        (p+i)->down = (p + i + 6);
        (p+i)->upLeft = (p + i - 7);
        (p+i)->upRight = (p + i - 5);
        (p+i)->downLeft = (p+ i + 5);
        (p+i)->downRight = (p + i + 7);



        if (i<6)
        {
            p[i].up = NULL;
            p[i].upLeft = NULL;
            p[i].upRight = NULL;
            p[i].data ='1';
        }

        if (i % 6 == 0)
        {
            p[i].left = NULL;
            p[i].upLeft = NULL;
            p[i].downLeft = NULL;
            p[i].data = '1';


        }

        if (i % 6 == 5)
        {
            p[i].right = NULL;
            p[i].upRight = NULL;
            p[i].downRight = NULL;
            p[i].data = '1';
        }

        if (i > 29)
         {
            p[i].down = NULL;
            p[i].downLeft = NULL;
            p[i].downRight = NULL;
            p[i].data = '1';
         }
         if ((i > 6 && i < 11) || (i > 12 && i < 17) || (i > 18 && i < 23) || (i > 24 && i < 29)){
            p[i].data = '2';
         }
         if ((i == 14) || (i == 15) || (i == 20) || (i == 21))
         {
             p[i].data = '3';
         }
   }
   return p;
}

//Function to create a linked list of nodes
struct Node* createNode()
{
    struct Node *linkedList = (struct Node*) malloc(sizeof(struct Node));
    linkedList->data = '1';
    linkedList->next = NULL;
    return linkedList;
}

//Function to make a single step to either direction. It will return the destination point on the grid
grid* singleMove(grid * p, char * dir )
{
    if (!strcmp(dir,"RIGHT")){
        return p->right;
    }
    if (!strcmp(dir,"LEFT")){
        return p->left;
    }
    if (!strcmp(dir,"UP")){
        return p->up;
    }
    if (!strcmp(dir,"DOWN")){
        return p->down;
    }
    if (!strcmp(dir,"UPRIGHT")){
        return p->upRight;
    }
    if (!strcmp(dir,"UPLEFT")){
        return p->upLeft;
    }
    if (!strcmp(dir,"DOWNRIGHT")){
        return p->downRight;
    }
    if (!strcmp(dir,"DOWNLEFT")){
        return p->downLeft;
    }
}

//Function to check if there is any move available at the specified point. Return 1 if there is and 0 if there is no available move
bool checkAvailableMove(grid * p)
{
    if (((p->right == NULL) ||((p->right->data < '1' ) || (p->right->data) > '3'))
        && ((p->left == NULL) || ((p->left->data < '1' ) || (p->left->data) > '3'))
        && ((p->up == NULL) || ((p->up->data < '1' ) || (p->up->data) > '3') )
        && ((p->down == NULL) || ((p->down->data < '1' ) || (p->down->data) > '3') )
        && ((p->upLeft == NULL) || ((p->upLeft->data < '1' ) || (p->upLeft->data) > '3'))
        && ((p->upRight == NULL) || ((p->upRight->data < '1' ) || (p->upRight->data) > '3'))
        && ((p->downLeft == NULL)|| ((p->downLeft->data < '1' ) || (p->downLeft->data) > '3'))
        && ((p->downRight == NULL)|| ((p->downRight->data < '1' ) || (p->downRight->data) > '3') ))
    {
       return 0;
    }
    return 1;
}

// This function will be used to update the score after each of the player's/AI's moves.
void appendNode(node * head, char v) {
    node * temp = (node *)malloc(sizeof (node));
    temp->data = v;
    temp->next = NULL;
    while(head->next != NULL) {
        head = head->next;
    }
    head->next = temp;
}



//Function to check if the input path (direction and steps) is available. Return 1 if available and 0 if not
bool checkPath(grid * p, char * dir, int steps)
{
    grid *temp = p;
    for (int i = 0; i < steps; i++)
    {
        temp = singleMove(temp, dir);
        if ((!temp) || (temp->data != '1' && temp->data != '2' && temp->data != '3'))
        {
            return 0;
        }
        return 1;

    }
}

//Function to get the path input from user. Will prompt user to type in the direction and number of steps and return it as the path data structure.
path inputPath(grid * p)
{
    char * dir = (char*)malloc(100*sizeof(char));
    int steps;
    printf("Input your move here: ");
    scanf("%s", dir);
    scanf("%d", &steps);
    while (!checkPath(p, dir, steps))
    {
        printf("Path Invalid! Please select another path: ");
        scanf("%s", dir);
        scanf("%d", &steps);
    }
    path input = {.dir = dir, .steps = steps};
    return input;
}

/*Function to make a move on the game board for player. This function takes the current board, direction and number of steps,
the score list as parameters. It will return the destination point on the game board, update the values on the path
and update the score
*/
grid * makeMovePlayer(grid * p, char * dir, int steps, node *scoreList)
{
    grid *temp = p;
    temp->data = '.';

    for (int i = 0; i < steps; i++)
    {
        temp = singleMove(temp, dir);
    }
    appendNode(scoreList, temp->data);
    temp->data = 'P';
    p->data = '.';
    return temp;
}

/* Function to handle a move from the player. It implements: checkAvailableMove(), inputPath(), makeMove().
It returns the destination point if the player can still move and NULL if they cannot move anymore.
*/
grid * playerMove(grid * p, node *playerScoreList)
{
    if (checkAvailableMove(p))
    {
        path input = inputPath(p);
        char *dir = input.dir;
        int steps = input.steps;
        p->data = '.';
        p = makeMovePlayer(p, dir, steps, playerScoreList);
        return p;

    }
    else
    {
        return NULL;
    }
}
//This helper function returns the pointer to grid position with higher value
grid * comparePath(grid * a, grid * b) {
    if (!a) return b;
    if (!b) return a;
    if (a->data > b->data) return a;
    return b;
}

//This function finds the best point available in the given direction for the AI. It takes the AI's position and a direction as parameters.
grid* findPathAIHelper(grid * p, char * dir)
{
    grid *maxPoint = NULL;
    grid *temp = singleMove(p, dir);
    while(temp != NULL && (temp->data >= '0') && (temp->data <= '9')){
        maxPoint = comparePath(maxPoint, temp);
        temp = singleMove(temp, dir);
    }
    return maxPoint;
}



/*This function finds the best path available for the AI.
It takes the board as the argument and find the point that yields the highest score */

grid * findPathAI(grid * p)
 {
    grid * maxPoint = NULL;
    maxPoint = comparePath(findPathAIHelper(p, "LEFT"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "RIGHT"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "UP"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "DOWN"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "UPRIGHT"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "UPLEFT"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "DOWNRIGHT"), maxPoint);
    maxPoint = comparePath(findPathAIHelper(p, "DOWNLEFT"), maxPoint);
    return maxPoint;
 }

 /*This is the main function to make the AI's moves. It checks to see if there are still moves available. If not, it returns NULL.
 If there is, the AI will follow the best path and return the destination pointer*/
grid* aiMove(grid * p, node * scoreList)
{

    if (checkAvailableMove(p))
    {

        grid *move = findPathAI(p);

        p->data = '.';
        appendNode(scoreList, move->data);
        move->data ='A';
        return move;
    }
    else return NULL;
}


//Draw out the grid
void displayGrid(grid * p)
{

  for (int i = 0; i < 36; i+=6){
    printf("%c %c %c %c %c %c \n",(p+i)->data, (p+i +1)->data, (p+i +2)->data, (p+i +3)->data, (p+i +4)->data, (p+i +5)->data);
  }
}

//This function will iterate through the player and AI's score lists and will print out the winner.
void checkWinner(node* playerScoreList, grid* aiScoreList)
{
   printf("\nPlayer's points: ");
   node* temp1 = playerScoreList;
   int sum1 = 0;
   int sum2 = 0;
   while (temp1 != NULL){
        printf("%c",temp1->data);
        if (temp1->next == NULL) printf("=");
        else    printf("+");
        sum1+= temp1->data - '0';
        node * toDel1 = temp1;
        temp1 = temp1->next;
        free(toDel1);
   }
   printf("%d\n", sum1);
   printf("AI's points: ");
   node* temp2 = aiScoreList;
   while (temp2 != NULL){
        printf("%c",temp2->data);
        if (temp2->next == NULL) printf("=");
        else    printf("+");
        sum2+= temp2->data - '0';
        node * toDel2 = temp2;
        temp2 = temp2->next;
        free(toDel2);
   }
   printf("%d\n", sum2);
    if (sum1>sum2) printf("Player Wins!\n");
    else printf("AI wins!\n");

}




int main()
{
    printf("Welcome to\n");
    printf("HEY THAT'S MY FISH\n");
    //Initialize the game board
    grid * p = createGrid();
    //Linked list to keep track of player's score
    node * playerScoreList = createNode();
    //Linked list to keep track of AI's score
    node * aiScoreList = createNode();
    //Initialize a variable to keep track of the player's current position
    grid *playerPos = p;
    //Initialize a variable to keep track of the AI's current position
    grid *aiPos = p->right;
    //Set the value at the player's initial position to 'P'
    playerPos->data = 'P';
    //Set the value at the AI's initial position to 'A'
    aiPos->data = 'A';
    //Boolean variable to control the game's flow
    bool gameOn = 1;
    /*The main loop of the game. If both players cannot make a move (both functions to make moves returns NULL), the loop will be broken
    and the game will end*/
    while (gameOn == 1){
        displayGrid(p);
        gameOn = 0;
        grid * temp = playerMove(playerPos, playerScoreList);
        displayGrid(p);

        if (temp) {
            gameOn = 1;
            playerPos = temp;
        }

        temp = aiMove(aiPos, aiScoreList);

        if (temp) {
            gameOn = 1;
            aiPos = temp;
        }
        printf("AI's turn:\n");


    }
    printf("This is the end of the game!");
    checkWinner(playerScoreList, aiScoreList);
    free(p);
    return 0;

}
