// Tic-Tac-Toe - LLD starter stub (C++, NxN).
#include <bits/stdc++.h>
using namespace std;

class Board {
    int n; vector<vector<char>> g;
public:
    Board(int nn=3): n(nn), g(nn, vector<char>(nn,' ')) {}
    bool place(int r,int c,char mark){
        // TODO: place if empty + in-bounds; return success
        throw logic_error("TODO");
    }
    bool hasWon(char mark){
        // TODO: any full row/col/diagonal of mark
        throw logic_error("TODO");
    }
    bool isFull(){ for(auto&row:g) for(char c:row) if(c==' ') return false; return true; }
};

class Game {
    Board board; vector<char> marks{'X','O'}; int turn=0;
public:
    Game(int n=3): board(n) {}
    string move(int r,int c){
        char mark=marks[turn%2];
        // TODO: place; if win -> mark+" wins"; if full -> "draw"; else turn++ and "next"
        throw logic_error("TODO");
    }
};

int main(){
    Game g(3);
    int seq[5][2]={{0,0},{1,0},{0,1},{1,1},{0,2}}; string res;
    for(auto& m:seq) res=g.move(m[0],m[1]);
    assert(res=="X wins");
    cout<<"PASS\n";
}
// PASSING: correct win/draw/invalid for NxN; alternating turns.
