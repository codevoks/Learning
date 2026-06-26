// Flyweight — share immutable intrinsic state across many objects to save memory.
// e.g. a text editor: one glyph object per character shared across thousands of positions.
#include <bits/stdc++.h>
using namespace std;

struct Glyph { char c; /* intrinsic, shared */ Glyph(char cc):c(cc){} };
class GlyphFactory {                                  // returns shared instances
    unordered_map<char, Glyph*> pool;
public:
    Glyph* get(char c){ auto& g = pool[c]; if(!g) g = new Glyph(c); return g; }
    size_t distinct() const { return pool.size(); }
};
int main(){
    GlyphFactory f; string text = "banana";
    vector<Glyph*> doc; for(char c: text) doc.push_back(f.get(c)); // 6 chars...
    cout << "glyphs in doc=" << doc.size() << ", distinct objects=" << f.distinct() << "\n"; // 6, 3
}
