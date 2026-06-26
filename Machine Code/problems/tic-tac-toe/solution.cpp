// Tic-Tac-Toe - machine-coding stub (C++, target 30 min).
#include <bits/stdc++.h>
using namespace std;
class TicTacToe {
    int n; vector<vector<char>> g; vector<char> marks{'X','O'}; int turn=0;
    bool wins(char m){
        // TODO: any full row/col/diagonal of m
        throw logic_error("TODO");
    }
public:
    TicTacToe(int nn=3): n(nn), g(nn,vector<char>(nn,' ')) {}
    string move(int r,int c){
        // TODO: validate; place current mark; return "X wins"/"O wins"/"draw"/"ok"/"invalid"
        throw logic_error("TODO");
    }
};
int main(){
    TicTacToe g(3);
    int seq[5][2]={{0,0},{1,0},{0,1},{1,1},{0,2}};
    const char* exp[5]={"ok","ok","ok","ok","X wins"};
    for(int i=0;i<5;i++) assert(g.move(seq[i][0],seq[i][1])==string(exp[i]));
    cout<<"PASS\n";
}
// PASSING: correct win/draw/invalid for NxN, alternating turns.
