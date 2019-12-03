#ifndef WILLARDYFAST_H
#define WILLARDYFAST_H

#include "WillardXfast.h"
#include <set>
#include <algorithm>
#include <vector>
#include <unordered_map>

typedef long long ll;

class WillardYfast{

    WillardXfast *willXfast;
    int n;
    int m;
    ll U;
    int logU;
    std::vector<std::set<ll> > B;
    std::vector<ll> S;
    std::unordered_map<ll, int> idx;

public:

    WillardYfast(ll _U, std::vector<ll> nums) : U(_U) {

        logU = ceil(log2(U));
        n = nums.size();
        std::sort(nums.begin(), nums.end());
        m = n / logU;
        if(m * logU != n)
            m ++;
        B.resize(m);
        for(int i = 0; i < m; i ++){
            S.push_back(nums[i * logU]);
            idx[S.back()] = i;
            for(int j = 0; j < logU && i * logU + j < n; j ++){
                B[i].insert(nums[i * logU + j]);
            }
        }
        willXfast = new WillardXfast(U, S);

    }

    ll upper_bound(ll x){
        ll s = willXfast->upper_bound(x);
        if(s == -1){
            auto s1 = B[m-1].lower_bound(x);
            if(s1 != B[m-1].end()){
                return *s1;
            }
            return -1;
        }
        int i = idx[s];
        if(i == 0){
            return S[0];
        }
        if(x == s){
            return x;
        }
        auto s1 = B[i - 1].lower_bound(x);
        if(s1 == B[i - 1].end()){
            return s;
        }
        return *s1;



    }

    ll lower_bound(ll x){
        ll s = willXfast->lower_bound(x);
        if(s == -1){
            return -1;
        } 
        if(x == s){
            return x;
        }
        int i = idx[s];
       
        auto s1 = B[i].upper_bound(x);
        if(s1 == B[i].begin()){
            if((*s1) == x)
                return x;
            return -1;
        }
        if(s1 == B[i].end()){
            return *(B[i].rbegin());
        }
        return *(--s1);

    }


    ~WillardYfast(){
        delete willXfast;
    }

};


#endif