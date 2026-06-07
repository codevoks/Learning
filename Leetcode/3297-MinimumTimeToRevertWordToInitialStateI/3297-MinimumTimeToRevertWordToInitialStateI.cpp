// Last updated: 6/7/2026, 11:24:38 PM
class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        //first mistake that I made is that I should have approximated the time complexity of algorithm beforehand
        //first thing to notice that we can always do it , as the choice of chareters to be added is completely in our hands
        int n = word.size();
        
        int i =1;
        while(i<=(n+k-1)/k)
        {
            //now check if the reaming of the string after i removals is same as the starting part of the string of same length
            int d = i*k;    //lenght of string removed
            int r = n-d;    //length of string remaining
            int flag = 1;
            for(int i = 0;i<r;i++)
            {
                if(word[i]!=word[i+d])
                {
                    flag =0;
                    break;
                }
            }
            if(flag)
            {
                break;
            }
            i++;
        }
        return i;
    }
};