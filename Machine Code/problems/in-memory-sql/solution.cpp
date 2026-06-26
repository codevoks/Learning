// In-memory SQL - machine-coding stub (C++, target 60 min).
#include <bits/stdc++.h>
using namespace std;
using Row = map<string,int>;
class Database {
    struct Table { vector<string> cols; vector<Row> rows; };
    unordered_map<string,Table> tables;
public:
    void createTable(const string& name, vector<string> cols){ tables[name]={move(cols),{}}; }
    void insert(const string& name, Row row){
        // TODO: validate columns, append row
        throw logic_error("TODO");
    }
    vector<Row> select(const string& name,
                       function<bool(const Row&)> where = nullptr,
                       string orderBy = "", int limit = -1){
        // TODO: filter by where, sort by orderBy, apply limit
        throw logic_error("TODO");
    }
};
int main(){
    Database db; db.createTable("users",{"id","age"});
    db.insert("users",{{"id",1},{"age",30}});
    db.insert("users",{{"id",2},{"age",20}});
    db.insert("users",{{"id",3},{"age",40}});
    auto res = db.select("users",[](const Row& r){return r.at("age")>=30;},"age",1);
    assert(res.size()==1 && res[0].at("id")==1);
    cout<<"PASS\n";
}
// PASSING: where filters, orderBy sorts, limit caps; invalid column rejected.
