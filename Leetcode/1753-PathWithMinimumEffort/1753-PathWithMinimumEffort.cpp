// Last updated: 6/7/2026, 11:24:55 PM
class Solution {
public:
    int dr[4]= {-1,0,1,0};
    int dc[4]= {0,1,0,-1};
    int rows,columns;
    int isValid(int r,int c){
        return !(r<0||r>=rows||c<0||c>=columns);
    }
    void djikstra(int sourceR, int sourceC, vector<vector<int>>& heights, vector<vector<int>>& dist){
        using P = pair<int,pair<int,int>>;
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push(make_pair(0,make_pair(sourceR,sourceC)));
        dist[sourceR][sourceC]=0;
        while(!pq.empty()){
            auto [d,node]=pq.top();
            int r=node.first;
            int c=node.second;
            pq.pop();
            for(int i=0;i<4;i++){
                int nr=r+dr[i];
                int nc=c+dc[i];
                if(!isValid(nr,nc)){
                    continue;
                }
                int distance = abs(heights[nr][nc]-heights[r][c]);
                if(max(dist[r][c],distance)<dist[nr][nc]){
                    dist[nr][nc]=max(dist[r][c],distance);
                    pq.push(make_pair(dist[nr][nc],make_pair(nr,nc)));
                }
            }
        }
    }
    int minimumEffortPath(vector<vector<int>>& heights) {
        const int INF=1e9;
        rows=heights.size();
        columns=heights[0].size();
        vector<vector<int>> dist(rows,vector<int>(columns,INF));
        djikstra(0,0,heights,dist);
        return dist[rows-1][columns-1];
    }
};