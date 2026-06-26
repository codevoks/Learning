// SRP — Single Responsibility: a class should have ONE reason to change.
// VIOLATION: Report below mixes data, formatting, and persistence -> 3 reasons to change.
//   class Report { string data; string toHTML(); void saveToFile(); };  // BAD
// FIX: split each responsibility into its own class.
#include <bits/stdc++.h>
using namespace std;

struct Report { string title, body; };               // 1) just the data
struct HtmlFormatter {                                // 2) only formatting
    string format(const Report& r) const { return "<h1>"+r.title+"</h1><p>"+r.body+"</p>"; }
};
struct FileSaver {                                    // 3) only persistence
    void save(const string& content, const string& path) const {
        /* write to path */ cout << "saved " << content.size() << " bytes to " << path << "\n";
    }
};
int main(){
    Report r{"Q4","revenue up"};
    HtmlFormatter f; FileSaver s;
    s.save(f.format(r), "report.html");
    // Changing the file format does NOT touch Report or FileSaver. One reason to change each.
}
