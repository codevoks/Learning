// Chess - LLD starter stub (C++, polymorphic pieces).
#include <bits/stdc++.h>
using namespace std;
struct Board;
using Pos = pair<int,int>;

struct Piece {
    string color; Piece(string c):color(move(c)){}
    virtual bool isValidMove(const Board& b, Pos from, Pos to) const = 0;
    virtual ~Piece()=default;
};

struct Board {
    map<Pos,Piece*> grid;
    void place(Pos p, Piece* pc){ grid[p]=pc; }
    Piece* at(Pos p) const { auto it=grid.find(p); return it==grid.end()?nullptr:it->second; }
    bool pathClear(Pos from, Pos to) const {
        // TODO: for sliding pieces ensure no piece strictly between from and to
        throw logic_error("TODO");
    }
};

struct Rook : Piece {
    Rook(string c):Piece(move(c)){}
    bool isValidMove(const Board& b, Pos from, Pos to) const override {
        // TODO: same row or col AND path clear
        throw logic_error("TODO");
    }
};
struct Knight : Piece {
    Knight(string c):Piece(move(c)){}
    bool isValidMove(const Board&, Pos from, Pos to) const override {
        // TODO: L-shape (2,1)
        throw logic_error("TODO");
    }
};

int main(){
    Board b; Rook* r=new Rook("white"); b.place({0,0},r);
    assert(b.at({0,0})->isValidMove(b,{0,0},{0,5})==true);
    Knight k("white");
    assert(k.isValidMove(b,{0,0},{1,2})==true);
    cout<<"PASS\n";
}
// PASSING: each piece validates own moves (polymorphism); sliders respect blocked paths; new piece needs no Board change.
