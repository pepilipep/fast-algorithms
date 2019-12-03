#include <iostream>
#include <cassert>
#include <vector>
#include <set>

#include "PerfectHash.h"

using namespace std;

void validate(vector<long long>& v, long long p){
    PerfectHash hash(v, p);
    cout << "hash is built\n";
    std::set<long long> s;
    for(long long x : v){
        s.insert(x);
    }

    for(int i = 0; i < p; i ++){
        bool in = (s.find(i) != s.end());
        assert(in == hash.Search(i));
    }
}

void testHash(){

    vector<long long> v({1, 4, 6, 8, 9, 11, 14});
    PerfectHash hash(v, 17);

    validate(v, 17);
}

void testHashGen(){
    vector<long long> v;
    v.push_back(1);
    long long p = 1e8 + 7;
    while(420){
        ll r = rand() % 100 + 1;
        if(v.back() + r >= p){
            break;
        }
        v.push_back(v.back() + r);
    }
    validate(v, p);
}

int main(){

    testHash();
    testHashGen();

    return 0;
}