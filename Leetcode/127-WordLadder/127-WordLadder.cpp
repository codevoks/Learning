// Last updated: 6/7/2026, 11:27:04 PM
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        int n = beginWord.size();
        unordered_set<string> allowedWords(wordList.begin(),wordList.end());
        unordered_map<string,int> distance,visited;
        queue<string> q;
        distance[beginWord]=1;
        visited[beginWord]=1;
        q.push(beginWord);
        while(!q.empty()){
            auto node = q.front();
            q.pop();
            for(int i=0;i<n;i++){
                string nextWord = node;
                for(auto a: alphabet){
                    nextWord[i]=a;
                    if(nextWord==node||!allowedWords.count(nextWord)||visited[nextWord]){
                        continue;
                    }
                    distance[nextWord]=distance[node]+1;
                    visited[nextWord]=1;
                    q.push(nextWord);
                }
            }
        }
        return visited[endWord]?distance[endWord]:0;
    }
};