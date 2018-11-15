#include <bits/stdc++.h>
using namespace std;
#define TEST true

#if !TEST
int main(){
    string temp = "1234";
    cout<<temp.size()<<endl;
    unordered_map<string, int> mp;
    mp["a"] = 1;
    mp["b"] = 2;
    string s;
    while(cin>>s){
        if(mp.count(s)){
            mp[s]++;
            cout<<mp[s]<<endl;
        }else{
            cout<<mp[s]++<<endl;
        }
    }
}
#else

#endif