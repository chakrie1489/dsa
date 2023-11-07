#include <stdio.h>
/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

typedef char board_t[15];
typedef char player_t; 
player_t other ( player_t player){
        switch (player) {
        case RED: return 2; break;
        case BLUE: return 1; break;
        }
}
int has_won(board_t board, player_t player)
{
    player_t opp= other(player);
    int pos[20][3] = {
        {0,1,5},
        {0,2,6},
        {0,3,7},
        {0,4,8},
        {1,2,9},
        {1,3,10},
        {1,4,11},
        {2,3,12},
        {2,4,13},
        {3,4,14},
        {5,6,9},
        {5,7,10},
        {5,8,11},
        {6,7,12},
        {6,8,13},
        {7,8,14},
        {9,10,12},
        {9,11,13},
        {10,11,14},
        {12,13,14}
    };
    for (int i =0; i<20; i++){
        if (board[pos[i][0]]==opp && board[pos[i][1]]==opp && board[pos[i][2]]==opp){
            return 1;
        }
    }
  return 0;
}

int is_full(board_t board)
{   
    for ( int i=0 ; i < 15 ; i++){
        if ( board[i] == NO ){
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int line;
    int score;
} move_t;

move_t best_move(board_t board, player_t player)
{   move_t m1,m2;
    
    int old=10;
    m1.score=-1;
    m1.line=-1;
    for(int i=0; i<15;i++){
      if (board[i]!=0){
        continue;
      }
      board[i]=player;
      if (has_won(board,other(player))){
        board[i]=0;
        if (m1.line==-1){
          m1.line=i;
        }
        continue;
      }
      m2=best_move(board, other(player));
      if (m2.score<0){
        m1.line=i;
        m1.score=1-m2.score;
        board[i]=0;
        return m1;
      }
      else{
        int temp=-1-m2.score;
        if (temp<old){
          m1.score=temp;
          old=temp;
          m1.line=i;
        }
      }
      board[i]=0;
    }
    return m1;
}

void print_board(board_t board)
{   
    int i, j;
    for (j=0; j<15; j++){
       printf("%d ",j);
    }
    printf("\n");
    for (i = 0; i < 10; i++) {
      if (board[i]==0){
        printf(". ");
      }else if(board[i]==1){
        printf("R ");
        }
      else{
        printf("B ");
      }
    }
    for (i = 10; i < 15; i++) {
      if (board[i]==0){
        printf(".  ");
      }else if(board[i]==1){
        printf("R  ");
        }
      else{
        printf("B  ");
      }
    }
    printf("\n");
}

int main()
{   
    board_t board;
    player_t player;
    int inp,res,cur;
    for (int i=0; i<15; i++){
        board[i]=0;
    }
    printf("Choose a colour : \nEnter 1 for RED\nEnter 2 for BLUE\n");
    scanf("%d",&res);
    if (res==1){
      player=RED;
    }else{
      player=BLUE;
    }
    if (res==1){
      printf("     Your are RED\n");
    }else{
      printf("     Your are BLUE\n");
    }
    
    printf("    \n");
    printf("Who should make the first move : \nEnter 1 for Player\nEnter 2 for Computer\n");
    scanf("%d",&cur);
    if(cur==2){
      player=other(player);
    }
    printf("    \n");
    print_board(board);
    printf("    \n");
    while(1){
        if (cur==1){
            if (is_full(board)){
                printf("it is a tie");
                break;
            }
            while(1){
              scanf("%d",&inp);
              if (board[inp]==0){
                break;
              }
              printf("    \n");
              printf("Please give vaild input !\n");
              
            }
            
            printf("    \n");
            printf("player chose : ""%d\n",inp);
            board[inp]=player;
            // move_t ai1=best_move(board,BLUE);
            // printf("player chose : ""%d\n",ai1.line);
            // board[ai1.line]=BLUE;
          
            print_board(board);
            printf("    \n");
          
            if (has_won(board,other(player))){
                printf("Computer Has Won");
                break;
            }
        }else{
            if (is_full(board)){
                printf("it is a tie");
                break;
            }
            printf("    \n");
            move_t ai=best_move(board,player);
            printf("computer chose : ""%d\n",ai.line);
            board[ai.line]=player;
            
            print_board(board);
          
            if (has_won(board,other(player))){
                printf("Player Has Won");
                break;
            }
        }
    cur=3-cur;
    player=other(player);  
    }
    return 0;
}