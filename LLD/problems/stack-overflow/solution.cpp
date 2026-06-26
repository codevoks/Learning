// Stack Overflow - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;

struct Answer { int id; string author; string body; int votes=0; bool accepted=false; };
struct Question {
    int id; string author; string title; int votes=0;
    vector<Answer> answers; vector<string> tags;
};

class StackOverflow {
    int nextQ=1, nextA=1;
    unordered_map<int,Question> questions;
public:
    int postQuestion(const string& author, const string& title, vector<string> tags){
        // TODO: create question, return id
        throw logic_error("TODO");
    }
    int postAnswer(int qid, const string& author, const string& body){
        // TODO: append answer to question, return answer id
        throw logic_error("TODO");
    }
    void vote(int qid, int delta){
        // TODO: question votes += delta (delta = +1/-1)
        throw logic_error("TODO");
    }
    void acceptAnswer(int qid, int aid){
        // TODO: only question author can accept; mark that answer accepted (only one)
        throw logic_error("TODO");
    }
    const Question& getQuestion(int qid){ return questions.at(qid); }
};

int main(){
    StackOverflow so;
    int q = so.postQuestion("vansh","What is MVCC?",{"db","postgres"});
    int a = so.postAnswer(q,"coach","snapshot isolation...");
    so.vote(q,1); so.vote(q,1);
    so.acceptAnswer(q,a);
    assert(so.getQuestion(q).votes==2);
    assert(so.getQuestion(q).answers[0].accepted==true);
    cout<<"PASS\n";
}
// PASSING: questions/answers/voting; only author accepts; single accepted answer; (bonus) tag search, reputation.
