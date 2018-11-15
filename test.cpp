#include <bits/stdc++.h>
using namespace std;
#define TEST true

struct Node{
    int v;
    Node *nxt;
};
#if !TEST
int main(){

    Node *a = new Node{1, nullptr};
    Node *b = new Node{2, nullptr};
    Node *c = new Node{3, nullptr};
    a->nxt = b;
    b->nxt = c;
    a = b;

    for(Node *i = a; i != nullptr; i = i->nxt){
        cout<<i->v<<endl;
    }

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