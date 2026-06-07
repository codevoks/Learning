// Last updated: 6/7/2026, 11:26:57 PM
class Solution {
public:

    void f(int start,int end,string &s, vector<string> &collect,vector<string>& wordDict,vector<string> &ans)
    {
        if(start==end)
        {
            int n = collect.size();
            /*if(collect[n-1]==' ')
            {
                string t = collect.substr(0,n-1);
                cout<<" putting in t "<<t<<endl;
                ans.push_back(t);
                return;
            }*/
            string t = "";
            for(int i=0;i<n;i++)
            {
                if(i==0)
                {
                    t = t+collect[i];
                    continue;
                }
                t = t + " "+ collect[i];
            }
            ans.push_back(t);
        }
        int n = end-start;
        for(int i = 0;i<=n;i++)
        {
            string s1 = s.substr(start,i);
            //string s2 = s.substr(i,n-i);
            if(find(wordDict.begin(),wordDict.end(),s1)!=wordDict.end())
            {
                //cout<<" found "<<s1<<" with i = "<<i<<endl;
                //collect = collect + s1 + " ";
                collect.push_back(s1);
                //cout<<" collect is "<<collect<<endl;
                //cout<<" checking on "<<s.substr(start+i,n)<<endl;
                //cout<<" start +i "<<start+i<<" and  end "<<end<<" n is "<<n<<endl;
                f(start+i,end,s,collect,wordDict,ans);
                collect.pop_back();
            }
        }
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) 
    {    
        vector<string> ans;
        int n = s.size();
        int start = 0,end = n;
        for(int i = 0;i<=n;i++)
        {
            //string collect;
            vector<string> collect;
            string word = s.substr(0,i);
            if(find(wordDict.begin(),wordDict.end(),word)!=wordDict.end())
            {
                //collect = collect + word+" ";
                collect.push_back(word);
                f(i,end,s,collect,wordDict,ans); 
            }
        }
        return ans;
    }
};