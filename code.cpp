#include <cstdio>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <queue>
#include <math.h>
#include <assert.h>
#include <utility>
using namespace std;

struct board {
    int e[7];
};
struct colb {
    char c[6][4];
};
struct tesl {
    string t[21];
};
// int rgw = 0, flu = 0;
// int gwr = 1, luf = 1;
// int wrg = 2, ufl = 2;

// int rwb = 3, fur = 3;
// int wbr = 4, urf = 4;
// int brw = 5, rfu = 5;

// int ryg = 6, fdl = 6;
// int ygr = 7, dlf = 7;
// int gry = 8, lfd = 8;

// int rby = 9, frd = 9;
// int byr = 10, rdf = 10;
// int yrb = 11, dfr = 11;

// int owg = 12, bul = 12;
// int wgo = 13, ulb = 13;
// int gow = 14, lbu = 14;

// int obw = 15, bru = 15;
// int bwo = 16, rub = 16;
// int wob = 17, ubr = 17;

// int ogy = 18, bld = 18;
// int gyo = 19, ldb = 19;
// int yog = 20, dbl = 20;

// int oyb = 21, bdr = 21;
// int ybo = 22, drb = 22;
// int boy = 23, rbd = 23;
tesl brg(const colb & b){
    tesl arr;
    char col[6]={b.c[0][0],b.c[1][0],b.c[2][0],b.c[3][0],b.c[4][0],b.c[5][0]};
    int res[21][3]={
        {0,3,4},{4,0,3},{3,4,0},
        {0,4,1},{1,0,4},{4,1,0},
        {0,5,3},{3,0,5},{5,3,0},
        {0,1,5},{5,0,1},{1,5,0},
        {2,4,3},{3,2,4},{4,3,2},
        {2,1,4},{4,2,1},{1,4,2},
        {2,5,1},{1,2,5},{5,1,2}};
    for(int i=0;i<21;i++){
        string str;
        for(int j=0;j<3;j++){
            str.push_back(col[res[i][j]]);
        }
        arr.t[i]=str;
        str.clear();
    }    
    return arr;
}
board trans(const colb& b,const tesl& arr){
    board ans;
    string str;
    // string arr[21]={"rgw","wrg","gwr","rwb","brw","wbr","ryg","gry","ygr","rby","yrb","byr","owg","gow","wgo","obw","wob","bwo","oyb","boy","ybo"};
    str.push_back(b.c[0][0]);
    str.push_back(b.c[3][1]);
    str.push_back(b.c[4][2]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(0)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[0][1]);
    str.push_back(b.c[4][3]);
    str.push_back(b.c[1][0]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(1)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[0][2]);
    str.push_back(b.c[5][0]);
    str.push_back(b.c[3][3]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(2)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[0][3]);
    str.push_back(b.c[1][2]);
    str.push_back(b.c[5][1]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(3)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[2][0]);
    str.push_back(b.c[4][0]);
    str.push_back(b.c[3][0]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(4)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[2][1]);
    str.push_back(b.c[1][1]);
    str.push_back(b.c[4][1]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(5)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[2][3]);
    str.push_back(b.c[5][3]);
    str.push_back(b.c[1][3]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(6)*3+(i%3);
        }
    }
    return ans;
}
char clr(const char c){
    if(c=='r'){
        return 'o';
    }
    if(c=='o'){
        return 'r';
    }
    if(c=='w'){
        return 'y';
    }
    if(c=='y'){
        return 'w';
    }
    if(c=='b'){
        return 'g';
    }
    if(c=='g'){
        return 'b';
    }
    return ' ';
}
colb trans1(const colb & b)
{
    colb temp;

    for(int i=0;i<4;i++){
        temp.c[2][i]=b.c[2][2];
    }
    for(int i=0;i<4;i++){
        temp.c[3][i]=b.c[3][2];
    }
    for(int i=0;i<4;i++){
        temp.c[5][i]=b.c[5][2];
    }
    for(int i=0;i<4;i++){
        temp.c[0][i]=clr(b.c[2][2]);
    }
    for(int i=0;i<4;i++){
        temp.c[1][i]=clr(b.c[3][2]);
    }
    for(int i=0;i<4;i++){
        temp.c[4][i]=clr(b.c[5][2]);
    }
    return temp;

}
void print_board(const board& b)
{
    for (int r = 0; r < 7; ++r) {
        printf("%3d", b.e[r]);
    }
    printf("\n");
}

void print_board(const colb& b)
{
    for (int r = 0; r < 6; ++r) {
        for (int c = 0; c < 4; ++c) {
            printf("%c", b.c[r][c]);
        }
        printf("\n");
    }
}

void read_board(colb& b)
{
    for (int r = 0; r < 6; ++r) {
        for(int cl = 0; cl < 4; ++cl){
            scanf("%s", &b.c[r][cl]);
            if (b.c[r][cl]=='r'){
                b.c[r][cl]='o';
            }else if (b.c[r][cl]=='o'){
                b.c[r][cl]='r';
            }
        }
    }
}

board front(const board& b)
{
    board o = b;
    int arr[21]={3,4,5,9,10,11,0,1,2,6,7,8,12,13,14,15,16,17,18,19,20};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

board right(const board& b)
{
    board o = b;
    int arr[21]={0,1,2,17,15,16,6,7,8,4,5,3,12,13,14,19,20,18,11,9,10};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

board up(const board& b)
{
    board o = b;
    int arr[21]={14,12,13,1,2,0,6,7,8,9,10,11,16,17,15,5,3,4,18,19,20};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

enum move { R=1,U=2,F=3,R2=4,U2=5,F2=6,R1=7,U1=8,F1=9};

/*
 * Return a shortest path from src to dest.
 */

int ord(const board& board){
    int val=0;
    int k=6;
    for (int r = 0; r < 7; ++r) {
        int v=board.e[r];
        val+=v*pow(21,k);
        k-=1;
    }
    // printf("%d",val);
    return val;
}

board decode(int ord){
    board node;
    int temp=ord;
    
    for (int r = 6; r >=0; r--) {
        node.e[r]=temp%21;
        temp=temp/21;
    }
    // print_board(node);
    return node;
}
#define maxi (1800000000) 
std::vector<int> solve(const board& src, const board& dest)
{ 
    queue <int> q;
    int cnt=0;
    int visited[maxi];
    int parent[maxi];
    int initial=ord(src);
    int final=ord(dest);
    q.push(ord(src));
    visited[ord(src)] = U;
    int temp=0;
    while (!q.empty()) {
        int child = q.front();
        q.pop();
        board u=decode(child);
        if (child==final) {
            /* return the moves to get to u from src. */
            std::vector<int> moves;
            while (child!=initial) {
                moves.push_back(visited[child]);
                child=parent[child];
            }
            std::reverse(moves.begin(), moves.end());
            std::vector<int> ans;
            int prev=0;
            for (auto cur:moves){
                auto tem=cur;
                if (cur==prev){
                    int fla=ans.back();
                    ans.pop_back();
                    if(fla==cur){
                        tem+=3;
                    }else{
                        tem+=6;
                    }
                }
                prev=cur;
                ans.push_back(tem);
            }
            return ans;
        }

        board a = front(u);
        board b = right(u);
        board c = up(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);

        if (!visited[aord]) {
            visited[aord] = F;
            parent[aord] = child;
            q.push(aord);
            cnt+=1;
        }
        if (!visited[bord]) {
            visited[bord] = R;
            parent[bord] = child;
            q.push( bord);
            cnt+=1;
        }
        if (!visited[cord]) {
            visited[cord] = U;
            parent[cord] = child;
            q.push(cord);
            cnt+=1;
        }
        temp+=1;
    }
    printf("Not possible");
    return std::vector<int>( );
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case U: printf("U "); break;
        case F: printf("F "); break;
        case R: printf("R "); break;
        case U1: printf("U' "); break;
        case F1: printf("F' "); break;
        case R1: printf("R' "); break;
        case U2: printf("U2 "); break;
        case F2: printf("F2 "); break;
        case R2: printf("R2 "); break;
        }
    }
    printf("\n");
}

int main()
{
    // board src, dest;
    // colb src1;
    // // char gem[6]={'r','b','o','g','w','y'};
    // // for(int i=0;i<6;i++){
    // //     for(int j=0;j<4;j++){
    // //         src1.c[i][j]=gem[i];
    // //     }
    // // }
    // read_board(src1);
    // // src1.c[5][0]='b';
    // // src1.c[5][1]='b';
    // // src1.c[1][0]='w';
    // // src1.c[1][2]='w';
    // // src1.c[4][2]='g';
    // // src1.c[4][3]='g';
    // // src1.c[3][1]='y';
    // // src1.c[3][3]='y';
    // board src2=trans(src1);
    // print_board(src2);
    // // read_board(src);
    // // read_board(dest);
    // for (int i=0;i<7;i++){
    //     src.e[i]=(i)*3;
    //     dest.e[i]=i*3;
    // }
    
    // // dest=up(dest);
    // dest=front(dest);
    // // dest=right(dest);

    // print_board(src);
    // print_board(dest);

    // // auto moves = solve(src, dest);
    // // print_moves(moves);
    colb src1;
    read_board(src1);
    colb dest1=trans1(src1);
    // print_board(dest1);
    board src=trans(src1,brg(dest1));
    board dest=trans(dest1,brg(dest1));
    printf("Given Input :\n");
    print_board(src);
    printf("\n");
    printf("Destination :\n");
    print_board(dest);
    printf("\n");
    auto moves = solve(src, dest);
    print_moves(moves);
    return 0;
}