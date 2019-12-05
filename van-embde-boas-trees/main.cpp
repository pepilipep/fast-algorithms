#include <iostream>
#include <cassert>

#include "VanEmbdeTree.h"
#include <set>

using namespace std;

void testVanEmbdeTree(){
    ll U = 1LL << 12;
    VanEmbdeTree tree(U);
    set<ll> s;
    int n = 1e4 + 7;
    for(int i = 0; i < n; i ++){
        ll x = rand() % U;
        s.insert(x);
        tree.insert(x);
    }
    for(int i = 0; i < U; i ++){
        assert(tree.Search(i) == (s.find(i) != s.end()));
    }
    for(int i = 0; i < U; i ++){
        ll ans1 = tree.prev(i);
        auto ans2 = s.upper_bound(i);
        if(ans2 == s.begin()){
            assert(ans1 == -1);
            continue;
        }
        if(ans2 == s.end()){
            assert(ans1 == *s.rbegin());
            continue;
        }
        ans2 --;
        assert(ans1 == *ans2);
    }
    for(int i = 0; i < 1e4; i ++){
        ll x = rand() % U;
        s.erase(x);
        tree.erase(x);
        assert(s.size() == tree.size());
        for(int j = 0; j < U; j ++){
            assert(tree.Search(j) == (s.find(j) != s.end()));
        }
        for(int j = 0; j < U; j ++){
            ll ans1 = tree.prev(j);
            auto ans2 = s.upper_bound(j);
            if(ans2 == s.begin()){
                assert(ans1 == -1);
                continue;
            }
            if(ans2 == s.end()){
                assert(ans1 == *s.rbegin());
                continue;
            }
            ans2 --;
            assert(ans1 == *ans2);
        }
    }
}

int main(){

    testVanEmbdeTree();

    return 0;
}