#include <stdio.h>
#include<stdlib.h>
#include <time.h>
char board[3][3]={' ',' ',' ',' ',' ',' ',' ',' ',' '};//the tic tac toe board with all initital elements equal to blank
void initializeBoard(){//initialising the board with all elements equal to blank
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      board[i][j]=' ';
    }
  }
}
void displayInitial(){//used for displaying the board initially to the user with the cells marked
  printf("\n\t\t 1 | 2 | 3\n");
  printf("\t\t ----------\n");
  printf("\t\t 4 | 5 | 6\n");
  printf("\t\t ----------\n");
  printf("\t\t 7 | 8 | 9\n");
}


int check(int move){//checking if the move is valid
 int row=(move-1)/3;
 int column=(move-1)%3;
 if(board[row][column]==' ')
  return 1;
else
  return 0;
}


int winner(char a){//to determine the winner
  int lc=0,mc=0,tc=0,lr=0,tr=0,mr=0;
    for(int j=0; j<3; j++){//checks if winning combination is achieved row-wise
      if(board[0][j]==a)
      {
        tr=tr+1;
      }
      if(board[1][j]==a)
        mr=mr+1;
      if(board[2][j]==a)
        lr=lr+1;
    }
    for(int i=0;i<3;i++){//checks if winning combination is achieved column-wise
      if(board[i][0]==a)
        tc=tc+1;
      if(board[i][1]==a)
        mc=mc+1;
      if(board[i][2]==a)
        lc=lc+1;
    }
    if((board[0][0]==a && board[1][1]==a && board[2][2]==a)||(board[0][2]==a && board[1][1]==a && board[2][0]==a))//checks if winning combination is achieved diagonally
      return 1;
    if(tr==3||mr==3||lr==3||tc==3||mc==3||lc==3)
      return 1;
    return 0;
  }


void playerMove(int player){//function for player move in case of human vs human mode
  int move;
  while(1){
    printf("\n\tPlayer %d move : ",player);
    scanf("%d",&move);
    if(check(move)){
      int row=(move-1)/3;//calculating the index of row
      int column=(move-1)%3;//calculating the index of column
      if(player==1){
        board[row][column]='O';
        break;
      }
      else{
        board[row][column]='X';
        break;
      }
    }
    printf("\n\tInvalid Move...Try Again\n");
  }
}



void display(){//displaying the board during game
  int i,j;
  printf("\n");
  for(i=0;i<2;i++){
    printf("\t\t\t\t");
    for(j=0;j<2;j++){
      printf(" %c |",board[i][j]);
    }
    printf(" %c",board[i][2]);
    printf("\n");
    printf("\t\t\t\t");
    for(j=0;j<3;j++){
      printf("----");
    }
    printf("\n");
  }
  printf("\t\t\t\t");
  for(i=0;i<2;i++){
    printf(" %c |",board[2][i]);
  }
  printf(" %c",board[2][2]);
  printf("\n");
}

void displayScore(int score1,int score2, char name1[],char name2[]){

  printf("\n\n\t------------------------------------");
  printf("\n\n\t|                                   |");
  printf("\n\n\t|     %s: %d - %d : %s",name1,score1,score2,name2);
  printf("\n\n\t|                                   |");
  printf("\n\n\t------------------------------------ ");

}

void humanPlay(){//game controller for human vs human mode
 char ch='Y';
 int p1score=0,p2score=0;
 char player1[10],player2[10];
 printf("\n\tEnter name (Player 1) : ");
 scanf("%s",player1);
 printf("\n\tEnter name (Player 2) : ");
 scanf("%s",player2);
 do{
  initializeBoard();
  printf("\n\t%s chooses O and %s chooses X....\n",player1,player2);
  printf("\n\tEnter desired choice in the cell numbers as mentioned : \n");
  displayInitial();
    int total_moves=0;//total moves counter used for calculating if game is a draw
    while(1){
      playerMove(1);
      display();
      total_moves++;
      if(winner('O')){
        printf("\n\t%s wins\n",player1);
        p1score++;
        break;
      };
      if(total_moves>=9){
        printf("\n\tMatch Draw...\n");
        break;
      }
      playerMove(2);
      display();
      total_moves++;
      if(winner('X')){
        p2score++;
        printf("\n\t%s wins\n",player2);
        break;
      };
    }
    displayScore(p1score,p2score,player1,player2);
    printf("\n\n\nRematch?(Y to continue, any other to stop) : ");
    scanf("%c",&ch);
    scanf("%c",&ch);
  }while(ch=='Y'||ch=='y');
}


struct node{//node for a linked list used during human vs computer
  int data;
  struct node *next;
};
struct node *head = NULL;

//function to creat a new linked-list of 9 nodes
void createLinkedList()
{
  head = NULL;
  for(int i=1; i<=9; i++)
  {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = i;
    temp->next = NULL;
    if(head == NULL)
    {
      head = temp;
    }
    else
    {
      struct node *p;
      p = head;
      while (p->next != NULL)
      {
        p = p->next;
      }
      p->next = temp;
    }
  }


}

//function to delete computer move from linked-list
int deletePosition(int num)
{
  int pos;
  struct node *curnt = head;
  struct node *prev;
    //if 1st node is the given move
  if(num == 1)
  {
    pos = curnt->data;
    head = curnt->next;
  }
  else
  {
        //if current node is the given move then delete it
    for(int i=1; i<num; i++)
    {
      prev = curnt;
      curnt = curnt->next;
    }
    pos = curnt->data;
    prev->next = curnt->next;
  }
  return pos;
}

//function to delete move by player_1 from linked-list
int deleteByValue(int val)
{
  struct node *curnt = head;
  struct node *prev;
    //check if 1st node is the given move
  if(head->data == val)
  {
    head = curnt->next;
    return 1;
  }
  else
  {
    while(curnt != NULL)
    {
            //if current node value is given move then delete current node
      if(curnt->data == val)
      {
        prev->next = curnt->next;
        return 1;
      }
      prev = curnt;
      curnt = curnt->next;
    }
  }
  return 0;
}

//function to get a random number for computer move
int computerMove(int lower, int upper)
{
  int pos;
  int num;
  printf("\n\tComputer moves...\n");
  int calculation;
    //generate a random number
  num = (rand() % (upper - lower + 1)) + lower;
  pos = deletePosition(num);
  return pos;
}

//main function for computer vs human game
void playWithComputer()
{
  char ch='Y';
  int cscore=0;
  int pscore=0;
  char player[10];
  printf("\n\tEnter player name : ");
  scanf("%s",player);
  do{
        //function call to create the linked-list
    createLinkedList();
        int upper = 9;//upper limit for random number generation to make sure that the number selected for a computer's move is valid
        int lower = 1;
        //function call to initialise game board
        initializeBoard();
        printf("\n\t%s chooses O and Computer chooses X....\n",player);
        printf("\n\tEnter desired choice in the cell numbers as mentioned : \n");
        //function to display initial tic-tac-toe board
        displayInitial();
        int total_moves=0;
        int w=0;

        //loop to continue the game
        //loop will go on until player enter character other than 'Y' or 'y'
        while(1){
            //inner loop to get a valid move from human player
          while(1)
          {
            int move;
            printf("\n\tPlayer move : ");
            scanf("%d",&move);
            if(deleteByValue(move))
            {
              int row=(move-1)/3;
              int column=(move-1)%3;
              board[row][column]='O';
              total_moves++;
              break;
            }
            printf("\n\tInvalid Move...Try Again\n");
          }
            //display the game board
          display();
            //check if player_1 wins
          if(winner('O')){
            printf("\n\t%s wins...\n\n",player);
            pscore++;
            w=1;
            break;
          };
          upper=upper-1;
            //all possible moves are done
          if(head==NULL){
            break;
          }
            //Computer moves
          int move2 = computerMove(lower, upper);
          int row2 = (move2-1)/3;
          int column2 = (move2-1)%3;
          board[row2][column2] = 'X';
          display();
            //check if computer wins
          if(winner('X')){
            printf("\n\n\tComputer wins...\n\n");
            cscore++;
            w=1;
            break;
          };
          total_moves++;
          upper = upper-1;
        }
        //condition for match draw
        if(w!=1){
          printf("\n\tMatch Draw!..\n");
        }
        displayScore(pscore,cscore,player,"Computer");


        printf("\n\n\tRematch?(Y to continue, any other to stop) : ");
        scanf("%c",&ch);
        scanf("%c",&ch);
      }while(ch=='Y'||ch=='y');
    }

void changeTheme(){//function to change text color...works only in command prompt as it executes system function..
  printf("\n\tNOTE : WORKS DEPENDENT ON SYSTEM(WILL NOT WORK IN ONLINE COMPILERS! FOR RESULTS RUN VIA CMD)! \n");
  printf("\n\tAvailable colors :\n\n\t0 = Black\n\t1 = Blue\n\t2 = Green\n\t3 = Aqua\n\t4 = Red\n\t5 = Purple\n\t6 = Yellow\n\t7 = White\n\t8 = Gray\n\t9 = Light Blue\n\tA = Light Green\n\tB = Light Aqua\n\tC = Light Red\n\tD = Light Purple\n\tE = Light Yellow\n\tF = Bright White");
  char c;
  printf("\n\n\tEnter a color : ");
  scanf("%c",&c);
  scanf("%c",&c);
  switch(c){//conditions as per command prompt values
    case '0':
    system("COLOR 0");
    break;
    case '1':
    system("COLOR 1");
    break;
    case '2':
    system("COLOR 2");
    break;
    case '3':
    system("COLOR 3");
    break;
    case '4':
    system("COLOR 4");
    break;
    case '5':
    system("COLOR 5");
    break;
    case '6':
    system("COLOR 6");
    break;
    case '7':
    system("COLOR 7");
    break;
    case '8':
    system("COLOR 8");
    break;
    case '9':
    system("COLOR 9");
    break;
    case 'A':
    system("COLOR A");
    break;
    case 'B':
    system("COLOR B");
    break;
    case 'C':
    system("COLOR C");
    break;
    case 'D':
    system("COLOR D");
    break;
    case 'E':
    system("COLOR E");
    break;
    case 'F':
    system("COLOR F");
    break;
    default:
    system("COLOR 0");
  }
}

int main() {
  srand(time(0));
  system("cls");//clearing the screen...works in cmd
  do{
    int ch;
    printf("\n\t############# WELCOME TO TIC TAC TOE #############\n\n");
    printf("\n\tSelect mode :- \n");
    printf("\n\t1 -> HUMAN VS HUMAN \n");
    printf("\t2 -> HUMAN VS COMPUTER\n");
    printf("\t3 -> CHANGE THEME\n" );
    printf("\t4 -> CLEAR SCREEN\n" );
    printf("\tANY OTHER KEY TO QUIT\n");
    printf("\n\tMode -> ");
    scanf("%d",&ch);
    switch(ch){
      case 1:humanPlay();
      break;
      case 2:playWithComputer();
      break;
      case 3:changeTheme();
      break;
      case 4:system("cls");
      break;
      default:system("COLOR 7");
      exit(0);
    }
  }while(1);
  return 0;
}
