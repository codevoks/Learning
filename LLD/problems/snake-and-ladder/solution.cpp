// Snake & Ladder - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;

class Board {
    int sz; unordered_map<int,int> jumps; // start->end
public:
    Board(int s, unordered_map<int,int> j): sz(s), jumps(move(j)) {}
    int size() const { return sz; }
    int resolve(int pos) const {
        // TODO: apply jump if pos has one
        throw logic_error("TODO");
    }
};

class Game {
    Board board; vector<string> players; unordered_map<string,int> pos;
public:
    Game(Board b, vector<string> pl): board(move(b)), players(move(pl)) {
        for(auto& p:players) pos[p]=0;
    }
    int positionOf(const string& p){ return pos[p]; }
    bool playTurn(const string& player, int dice){
        // TODO: move by dice (no overshoot past size), resolve jumps, return true if reached size
        throw logic_error("TODO");
    }
};

int main(){
    Board b(30, {{3,22},{27,5}});
    Game g(b, {"P1"});
    g.playTurn("P1",3);
    assert(g.positionOf("P1")==22);
    cout<<"PASS\n";
}
// PASSING: ladders/snakes applied; no overshoot; win detection; multiplayer.
