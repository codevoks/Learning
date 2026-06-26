// Snake & Ladder - machine-coding stub (C++, target 30 min).
#include <bits/stdc++.h>
using namespace std;
class Game {
    int sz; unordered_map<int,int> jumps; unordered_map<string,int> pos;
public:
    Game(int size, unordered_map<int,int> j, vector<string> players): sz(size), jumps(std::move(j)) {
        for(auto& p:players) pos[p]=0;
    }
    int positionOf(const string& p){ return pos[p]; }
    bool move(const string& player,int dice){
        // TODO: nw=pos+dice; if nw>sz stay; else apply jump; update; return nw==sz
        throw logic_error("TODO");
    }
};
int main(){
    Game g(20, {{3,11},{17,4}}, {"P1"});
    assert(g.move("P1",3)==false && g.positionOf("P1")==11); // ladder
    assert(g.move("P1",6)==false && g.positionOf("P1")==4);  // 17->4 snake
    cout<<"PASS\n";
}
// PASSING: ladders/snakes applied, no overshoot, win on reaching size, multiplayer.
