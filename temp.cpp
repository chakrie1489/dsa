#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <array>
#include <algorithm>
#include <tuple>
#include "queue.hpp"

struct board {
    int e[8];
};
struct cube
{
    char e[6][4];
};
struct cubelet{
    char e[8][3];
};
struct cubelets1{
    char e[24][3];    
};


long long ord(const board& board)
{
    long long a = 0;
    for (int i=0;i<8;i++){
        if (i==6){continue;}
        a=((a*21)+board.e[i]);
    }
    return a;
}

void print_board(const board& b)
{
    for (int r = 0; r < 8; ++r) {
            printf("%d ", b.e[r]);
        }
}

void print_board1(const cube &c){
    for (int i=0;i<6;i++){
        for (int j=0;j<4;j++){
            printf("%c ", c.e[i][j]);
        }
        printf("\n");
    }
    printf("--------\n");
}
void read_board(board& b)
{
    for (int r = 0; r < 8; ++r) {
            scanf("%d", &b.e[r]);
    }
}
void read_board1(cube& c){
    for (int i=0;i<6;i++){
        for (int j=0;j<4;j++){
            scanf(" %c",&c.e[i][j]);
        }
    }
}

char find_opp(char side){
    switch (side)
    {
    case 'y':return 'w';break;
    case 'w':return 'y';break;
    case 'o':return 'r';break;
    case 'g':return 'b';break;
    case 'r':return 'o';break;
    case 'b':return 'g';break;
    default:
    return '0';
        break;
    }
}

cube destination(const cube &c){
    cube temp;
    for (int i=0;i<4;i++){
        temp.e[3][i]=c.e[3][2];
        temp.e[2][i]=c.e[2][3];
        temp.e[5][i]=c.e[5][2];
    }
    for (int i=0;i<4;i++){
        temp.e[0][i]=find_opp(temp.e[2][0]);
        temp.e[1][i]=find_opp(temp.e[3][0]);
        temp.e[4][i]=find_opp(temp.e[5][0]);
    }
    return temp;
}
void swap1(char *str, int i, int j) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}

cubelets1 template_cubelet(cube& c){
    cubelets1 c1;
    char temp1[3];
    c1.e[0][0]=c.e[0][0];
    c1.e[0][1]=c.e[3][1];
    c1.e[0][2]=c.e[4][2];
    c1.e[3][0]=c.e[0][2];
    c1.e[3][1]=c.e[5][0];
    c1.e[3][2]=c.e[3][3];

    c1.e[6][0]=c.e[1][0];
    c1.e[6][1]=c.e[0][1];
    c1.e[6][2]=c.e[4][3];
    c1.e[9][0]=c.e[1][2];
    c1.e[9][1]=c.e[5][1];
    c1.e[9][2]=c.e[0][3];

    c1.e[12][0]=c.e[2][0];
    c1.e[12][1]=c.e[1][1];
    c1.e[12][2]=c.e[4][1];
    c1.e[15][0]=c.e[2][2];
    c1.e[15][1]=c.e[5][3];
    c1.e[15][2]=c.e[1][3];

    c1.e[18][0]=c.e[3][0];
    c1.e[18][1]=c.e[2][1];
    c1.e[18][2]=c.e[4][0];
    c1.e[21][0]=c.e[3][2];
    c1.e[21][1]=c.e[5][2];
    c1.e[21][2]=c.e[2][3];
    for (int i=1;i<24;i++){
        if (i%3==0){
            continue;
        }
        for(int j=0;j<3;j++){
            temp1[j]=c1.e[i-1][j];
        }
        swap1(temp1,0,2);
        swap1(temp1,1,2);
        for (int j=0;j<3;j++){
            c1.e[i][j]=temp1[j];
        }
    }
    return c1;
}

cubelet convert_to_cubelet(const cube &c){
    cubelet c1;
    c1.e[0][0]=c.e[0][0];
    c1.e[0][1]=c.e[3][1];
    c1.e[0][2]=c.e[4][2];
    c1.e[2][0]=c.e[0][2];
    c1.e[2][1]=c.e[5][0];
    c1.e[2][2]=c.e[3][3];

    c1.e[1][0]=c.e[1][0];
    c1.e[1][1]=c.e[0][1];
    c1.e[1][2]=c.e[4][3];
    c1.e[3][0]=c.e[1][2];
    c1.e[3][1]=c.e[5][1];
    c1.e[3][2]=c.e[0][3];

    c1.e[5][0]=c.e[2][0];
    c1.e[5][1]=c.e[1][1];
    c1.e[5][2]=c.e[4][1];
    c1.e[7][0]=c.e[2][2];
    c1.e[7][1]=c.e[5][3];
    c1.e[7][2]=c.e[1][3];

    c1.e[4][0]=c.e[3][0];
    c1.e[4][1]=c.e[2][1];
    c1.e[4][2]=c.e[4][0];
    c1.e[6][0]=c.e[3][2];
    c1.e[6][1]=c.e[5][2];
    c1.e[6][2]=c.e[2][3];
    return c1;
}
int compare(char a[],char b[]){
    for (int j=0;j<3;j++){
        if (a[j]!=b[j]){
            return 0;
        }
    }
    return 1;
}
int search(char a[],const cubelets1 &dic){
    char temp2[3];
    for (int j=0;j<24;j++){
        for (int t=0;t<3;t++){
            temp2[t]=dic.e[j][t];
        }
        if (compare(a,temp2)==1){
            return j;
        }
    }
    return -1;
}
board convert_to_board(cubelet &c1,const cubelets1 &dic){
    board b;
    char temp[3];
    for (int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            temp[j]=c1.e[i][j];
        }
        b.e[i]=search(temp,dic);
    }
    return b;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

int helper(int k){
    if ((k+1)%3==0){
        return (k-2);
    }
    return (k+1);
}

board side(const board& b)
{
    board o = b;
    o.e[1]=(b.e[3]);
    o.e[3]=helper(b.e[7]);
    o.e[7]=helper(b.e[5]);
    o.e[5]=helper(b.e[1]);
    return o;
}

board top(const board& b)
{
    board o = b;
    o.e[0]=b.e[1];
    o.e[1]=b.e[5];
    o.e[4]=b.e[0];
    o.e[5]=b.e[4];
    return o;
}

board face(const board& b)
{
    board o = b;
    o.e[0]=b.e[2];
    o.e[1]=helper(b.e[0]);
    o.e[2]=helper(b.e[3]);
    o.e[3]=helper(b.e[1]);
    return o;
}


bool is_same(const board& a, const board &b)
{
    for (int r = 0; r < 8; ++r){
            if (a.e[r] != b.e[r]) return false;}
    return true;
}

enum move { R = 1, U = 2, F = 3};

#define SIZE 13508161
#define maxi 13508161
struct DataItem { 
   int key;
   int parent[2];
   int move;
   struct DataItem* next;
};
struct DataItem* hashArray[SIZE]; 
int hashCode(long long key) {
   return key % SIZE;
}
void insert(long long key,long long parent, int move ) {
   struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
   item->parent[0] = parent/maxi;
   item->parent[1] = parent % maxi;  
   item->key = key/maxi;
   item->move=move;     
   int hashIndex = hashCode(key);
   if (hashArray[hashIndex]){
   item->next =hashArray[hashIndex];}
   hashArray[hashIndex] = item; 
}
int check(long long key){
    int hashIndex=hashCode(key);
    struct DataItem* k=hashArray[hashIndex];
    while(k){
        if(k->key==key/maxi){
            return 1;
        }
        k=k->next;
    }
    return 0;
}
struct DataItem* find(long long key){
    int hashIndex=hashCode(key);
    struct DataItem* k=hashArray[hashIndex];
    long long temp = key/maxi;
    while(k){
        if(k->key==temp){
            return k;
        }
        k=k->next;
    }
    assert(0);
}

std::vector<int> solve(const board& src, const board& dest)
{
    queue<board, 2000000000> q;
    // int visited[1787580378];
    // std::vector<int>visied;
    // board parent[11022480];

    enqueue(q, src);
    
    // visited[ord(src)] = R;
    long long s1=ord(src);
    while (!is_empty(q)) {
        board u = dequeue(q);
        long long l =ord(u);
        if (is_same(u, dest)) {
            std::vector<int> moves;
            board c = u;
            long long o = ord(c);
            while (!(o==s1)) {
                struct DataItem* m=find(o);
                moves.push_back(m->move);
                o = m->parent[0]*maxi + m->parent[1];
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = side(u);
        board b = top(u);
        board c = face(u);

        long long aord = ord(a);
        long long bord = ord(b);
        long long cord = ord(c);

        if (!check(aord)) {
            insert(aord,l,R);
            // visited[aord] = R;
            // parent[aord] = u;
            enqueue(q, a);
        }
        if (!check(bord)) {
            insert(bord,l,U);
            // visited[bord] = U;
            // parent[bord] = u;
            enqueue(q, b);
        }
        if (!check(cord)) {
            insert(cord,l,F);
            // visited[cord] = F;
            // parent[cord] = u;
            enqueue(q, c);
        }
    }
    assert(0);
}

void print_moves(const std::vector<int>& moves)
{
    int i=0;
    while (i<moves.size()){
        if ((i!=moves.size()-1) && (moves[i]==moves[i+1])){
            switch (moves[i]) {
                case F: printf("F2 "); break;
                case R: printf("R2 "); break;
                case U: printf("U2 "); break;
            }
            i++;
        }
        else{
            switch (moves[i]) {
                case F: printf("F "); break;
                case R: printf("R "); break;
                case U: printf("U "); break;
            }
        }
        i++;
    }
    printf("\n");
}
void print_cubelets1(const cubelets1& c1) {
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", c1.e[i][j]);
        }
        printf("\n");
    }
}

void print_cubelet(const cubelet& c) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", c.e[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    cube src;
    read_board1(src);
    cube dest =destination(src);
    cubelets1 temp = template_cubelet(dest);
    cubelet c1=convert_to_cubelet(src);
    cubelet c2 = convert_to_cubelet(dest);
    board b1=convert_to_board(c1,temp);
    board b2=convert_to_board(c2,temp);
    // board src, dest;
    // // int arr1[8]={0,6,3,9,18,12,21,15};
    // // int arr2[8]={0,9,3,16,18,7,21,13};
    // // for (int i=0;i<8;i++){
    // //     src.e[i]=arr1[i];
    // //     dest.e[i]=arr2[i];
    // // }
    // read_board(src);
    // // dest = side(src);
    
    // // dest = top(src);
    // // dest = face(src);
    // // dest = side(src);
    // read_board(dest);
    // // print_board(dest);
    // // printf("%d",ord(src));
    auto moves = solve(b1, b2);
    print_moves(moves);

    return 0;
}