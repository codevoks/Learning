// Last updated: 7/10/2026, 8:52:10 PM
class Solution {
public:
    static int comp(vector<int>& a, vector<int>& b){
        if(a[0]==b[0]){
            return a[1]>b[1];
        }
        return a[0]<b[0];
    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        //dp[i]=maximum number of envelopes you can russian doll ending at ith element, but this approach won't pass as O(N^2) result in TLE
        //use tails approach
        //tails[i]=smallest possible ending for a LIS of length i+1
        // append ki shart hai "naya element end se bada ho." Decreasing mein naya element hamesha chhota hota hai. Toh shart kabhi poori nahi hoti, append kabhi nahi hota. Bas replace.
        sort(envelopes.begin(),envelopes.end(),comp);
        int n=envelopes.size();
        vector<int> tails;
        for(int i=0;i<n;i++){
            int element=envelopes[i][1];
            auto it=lower_bound(tails.begin(),tails.end(),element);
            if(it!=tails.end()){
                *it=element;
            }else{
                tails.push_back(element);
            }
        }
        return tails.size();
    }
};