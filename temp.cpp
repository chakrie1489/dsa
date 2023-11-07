#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include "queue.hpp"
#define d10 13508161

struct board {
    int e[8];
};

int ord(const board& board)
{
    int a = 0;
    for (int i=0;i<8;i++){
        if (i==6){continue;}
        // a=((a*21)%d10+board.e[i])%d10;
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

void read_board(board& b)
{
    for (int r = 0; r < 8; ++r) {
            scanf("%d", &b.e[r]);
    }
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


std::vector<int> solve(const board& src, const board& dest)
{
    queue<board, 1800000000> q;
    int visited[1800000000];
    board parent[1800000000];

    enqueue(q, src);
    visited[ord(src)] = R;

    while (!is_empty(q)) {
        board u = dequeue(q);
        if (is_same(u, dest)) {
            std::vector<int> moves;
            board c = u;
            int o = ord(c);
            while (!is_same(c, src)) {
                moves.push_back(visited[o]);
                c = parent[o];
                o = ord(c);
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = side(u);
        board b = top(u);
        board c = face(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);

        if (!visited[aord]) {
            visited[aord] = R;
            parent[aord] = u;
            enqueue(q, a);
        }
        if (!visited[bord]) {
            visited[bord] = U;
            parent[bord] = u;
            enqueue(q, b);
        }
        if (!visited[cord]) {
            visited[cord] = F;
            parent[cord] = u;
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

int main()
{
    
    board src, dest;
    read_board(src);
    // dest = side(src);
    
    // dest = top(src);
    // dest = face(src);
    // dest = side(src);
    read_board(dest);
    // print_board(dest);
    // printf("%d",ord(src));
    auto moves = solve(src, dest);
    print_moves(moves);

    return 0;
}