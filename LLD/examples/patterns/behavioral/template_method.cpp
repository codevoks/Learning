// Template Method — base defines the algorithm SKELETON; subclasses fill in specific steps.
// The invariant order lives in the base; only the varying steps are overridden.
#include <bits/stdc++.h>
using namespace std;

struct DataProcessor {
    void run(){ read(); process(); write(); }        // the fixed skeleton (template method)
    virtual ~DataProcessor()=default;
protected:
    virtual void read() = 0;                          // steps subclasses customize
    virtual void process() = 0;
    void write(){ cout<<"writing result\n"; }         // shared step
};
struct CsvProcessor : DataProcessor {
    void read() override { cout<<"read CSV\n"; }
    void process() override { cout<<"parse rows\n"; }
};
int main(){ CsvProcessor p; p.run(); }                // read CSV / parse rows / writing result
