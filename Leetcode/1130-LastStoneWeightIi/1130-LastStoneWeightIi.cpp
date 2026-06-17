// Last updated: 6/17/2026, 11:07:43 PM
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        //note that the final left over can be writen as ±s1±s2±s3...±sN
        //now some of the are going to have +sign and some are going to have -
        //if we write all si's with different signs together we get two groups/subarrays - P(plus) and N(minus)
        //now let total sum of all stones=S
        //note that P+N=S (constant and known)
        //2P - S always positive nahi hota, kyunki P ko hum kabhi chhota group bhi chun sakte hain. Par final stone ka weight always non-negative hota hai, isliye |2P - S|.
        //the weight of final stone = |P-N|
        //N=S-P => weight of final stone = |P-(S-P)|=|2P-S|
        // we have to minimize |2P-S|
        // Goal: minimize |2P - S|  ->  P ko S/2 ke jitna paas le jao
        // Symmetry: P aur (S-P) same answer dete hain, toh sirf P <= S/2 dekho (aadha kaam)
        // Us range mein P max karo -> 0/1 knapsack, bag capacity = S/2
        // best = max subset sum <= S/2
        // answer = S - 2*best
        int n=stones.size();
        int S=0;
        for(int i=0;i<n;i++){
            S+=stones[i];
        }
        vector<int> prev((S/2)+1,0);
        for(int i=1;i<=n;i++){
            vector<int> cur((S/2)+1,0);
            int stoneWeight=stones[i-1];
            for(int j=1;j<=S/2;j++){
                if(j>=stoneWeight){
                    cur[j]=max(prev[j],stoneWeight+prev[j-stoneWeight]);
                }else{
                    cur[j]=prev[j];
                }
            }
            prev=cur;
        }
        return abs(2*prev[S/2]-S);
    }
};