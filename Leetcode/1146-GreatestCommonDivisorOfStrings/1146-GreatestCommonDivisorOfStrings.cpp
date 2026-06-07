// Last updated: 6/7/2026, 11:25:09 PM
class Solution {
public:
    int gcd(int a,int b)
    {
        if(a==0)
        {
            return b;
        }
        return gcd(b%a,a);
    }
    string gcdOfStrings(string str1, string str2) {
        if(str1+str2!=str2+str1)
        {
            return "";
        }
        int g=gcd(str1.length(),str2.length());
        return str1.substr(0,g);
    }
};