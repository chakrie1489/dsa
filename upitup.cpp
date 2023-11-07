#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <queue>
#include <math.h>
#include <assert.h>
#include <utility>
using namespace std;

struct board {
    int e[3][3];
};

void print_board(const board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            printf("%3d", b.e[r][c]);
        }
        printf("\n");
    }
}

void read_board(board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            scanf("%d", &b.e[r][c]);
        }
    }
}

tuple<int, int> find_space(const board& b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (b.e[r][c] == 0) return { r, c };
    assert(0);
}

board up(const board& b)
{
    const auto [r,c]= find_space(b);
    if (r == 0) return b;
    board o = b;
    if (o.e[r-1][c]==1){
        o.e[r][c]=6;
    }else if (o.e[r-1][c]==2){
        o.e[r][c]=5;
    }else if (o.e[r-1][c]==5){
        o.e[r][c]=1;
    }else if (o.e[r-1][c]==6){
        o.e[r][c]=2;
    }else{
        o.e[r][c]=o.e[r-1][c];
    }
    o.e[r-1][c]=0;
    return o;
}

board down(const board& b)
{
    const auto [r,c]= find_space(b);
    if (r == 2) return b;
    board o = b;
    if (o.e[r+1][c]==1){
        o.e[r][c]=5;
    }else if (o.e[r+1][c]==2){
        o.e[r][c]=6;
    }else if (o.e[r+1][c]==5){
        o.e[r][c]=2;
    }else if (o.e[r+1][c]==6){
        o.e[r][c]=1;
    }else{
        o.e[r][c]=o.e[r+1][c];
    }
    o.e[r+1][c]=0;
    return o;
}

board left(const board& b)
{
    const auto [r,c]= find_space(b);
    if (c == 0) return b;
    board o = b;
    if (o.e[r][c-1]==1){
        o.e[r][c]=4;
    }else if (o.e[r][c-1]==4){
        o.e[r][c]=2;
    }else if (o.e[r][c-1]==2){
        o.e[r][c]=3;
    }else if (o.e[r][c-1]==3){
        o.e[r][c]=1;
    }else{
        o.e[r][c]=o.e[r][c-1];
    }
    o.e[r][c-1]=0;
    return o;
}

board right(const board& b)
{
    const auto [r,c]= find_space(b);
    if (c == 2) return b;
    board o = b;
    if (o.e[r][c+1]==1){
        o.e[r][c]=3;
    }else if (o.e[r][c+1]==3){
        o.e[r][c]=2;
    }else if (o.e[r][c+1]==2){
        o.e[r][c]=4;
    }else if (o.e[r][c+1]==4){
        o.e[r][c]=1;
    }else{
        o.e[r][c]=o.e[r][c+1];
    }
    o.e[r][c+1]=0;
    return o;
}

enum move { L = 1, R = 2, U = 3, D = 4 };

/*
 * Return a shortest path from src to dest.
 */

int ord(const board& board){
    int val=0;
    int k=8;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            int v=board.e[r][c];
            val+=v*pow(7,k);
            k-=1;
        }
    }
    return val;
}

board decode(int ord){
    board node;
    int temp=ord;
    
    for (int r = 2; r >=0; r--) {
        for (int c = 2; c >=0; c--) {
            node.e[r][c]=temp%7;
            temp=temp/7;
        }
    }
    // print_board(node);
    return node;
}
#define maxi (5003550000) 
std::vector<int> solve(const board& src, const board& dest)
{ 
    queue <int> q;
    int visited[maxi];
    int parent[maxi];
    int initial=ord(src);
    int final=ord(dest);
    q.push(ord(src));
    visited[ord(src)] = L;
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
            return moves;
        }

        board a = up(u);
        board b = down(u);
        board c = left(u);
        board d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);

        if (!visited[aord]) {
            visited[aord] = U;
            parent[aord] = child;
            q.push(aord);
        }
        if (!visited[bord]) {
            visited[bord] = D;
            parent[bord] = child;
            q.push( bord);
        }
        if (!visited[cord]) {
            visited[cord] = L;
            parent[cord] = child;
            q.push(cord);
        }
        if (!visited[dord]) {
            visited[dord] = R;
            parent[dord] = child;
            q.push(dord);
        }
        temp+=1;
    }
    return std::vector<int>();
    assert(0);
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case L: printf("L "); break;
        case R: printf("R "); break;
        case U: printf("U "); break;
        case D: printf("D "); break;
        }
    }
    printf("\n");
}

int main()
{
    board src, dest;

    //u read_board(src);
    // read_board(dest);
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            src.e[r][c]=1;
            dest.e[r][c]=2;
        }
    }
    src.e[1][1]=0;
    dest.e[1][1]=0;

    print_board(src);
    print_board(dest);
    auto moves = solve(src, dest);
    print_moves(moves);

    return 0;
}