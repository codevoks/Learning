// Last updated: 6/7/2026, 11:25:40 PM
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        pair<int,int> next[8] = {{0,1},{0,-1},{1,1},{1,-1},{2,1},{2,-1},{3,1},{3,-1}};
        string source = "0000";
        queue<string> q;
        unordered_map<string,int> distance, visited, dead;
        for(auto d: deadends){
            dead[d]=1;
        }
        if(dead[source]){
            return -1;
        }
        distance[source]=0;
        visited[source]=1;
        q.push(source);
        while(!q.empty()){
            auto node = q.front();
            q.pop();
            for(auto n: next){
                auto nextNode = node;
                int index = n.first;
                int move = n.second;
                if(node[index]=='0' && move==-1){
                    nextNode[index]='9';
                } else if (node[index]=='9' && move==1){
                    nextNode[index]='0';
                }else{
                    nextNode[index]=nextNode[index]+move;
                }
                if(dead[nextNode]||visited[nextNode]){
                    continue;
                }
                q.push(nextNode);
                visited[nextNode]=1;
                distance[nextNode]=distance[node]+1;
            }
        }
        return visited[target] ?distance[target]:-1;
    }
};