// Last updated: 6/7/2026, 11:25:27 PM
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int modulo =1e9 + 7;
        int n = arr.size();
        vector<int> lessThan(n,0), greaterThanEqual(n,0);
        stack<int> st1,st2;
        for(int i=0;i<n;i++){
            while(!st1.empty()&&arr[st1.top()]>=arr[i]){
                st1.pop();
            }
            lessThan[i]=!st1.empty()?st1.top():-1;
            st1.push(i);
        }
        for(int i=n-1;i>=0;i--){
            while(!st2.empty()&&arr[st2.top()]>arr[i]){
                st2.pop();
            }
            greaterThanEqual[i]=!st2.empty()?st2.top():n;
            st2.push(i);
        }
        long long int sum = 0;
        for(int i = 0;i<n;i++){
            long long int left = (i-lessThan[i])%modulo;
            long long int right = ((greaterThanEqual[i]-1)-i+1)%modulo;
            sum+=((left*(arr[i]%modulo))*right)%modulo;
            sum%=modulo;
        }
        return sum;
    }
};