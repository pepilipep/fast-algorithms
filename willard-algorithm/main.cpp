#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>

#include "WillardXfast.h"
#include "WillardYfast.h"

using namespace std;

void testWillardX(){
    vector<long long> v({3, 15, 42, 13, 20, 60, 57, 31, 7});
    WillardXfast will(64, v);
    sort(v.begin(), v.end());
    int x = 0;
    for(int i = 0; i < 64; i ++){
        int willA = will.upper_bound(i);
        bool l = false;
        for( ; x < v.size(); x++){
            if(v[x] >= i){
                l = true;
                assert(v[x] == willA);
                break;
            }
        }
        assert(l || (willA == -1));
    }

}

void testWillardY(){
    vector<long long> v({3, 15, 42, 13, 20, 60, 57, 31, 7});
    WillardYfast will(64, v);
    sort(v.begin(), v.end());
    int x = 0;
    for(int i = 0; i < 64; i ++){
        int willA = will.upper_bound(i);
        bool l = false;
        for( ; x < v.size(); x++){
            if(v[x] >= i){
                l = true;
                assert(v[x] == willA);
                break;
            }
        }
        assert(l || (willA == -1));
    }

}

void testWillardXgen(){
    vector<long long> v;
    long long U = (1LL << 26);
    int n = 1e5 + 2;
    for(int i = 0; i < n; i ++){
        v.push_back(rand() % U);
    }
    WillardXfast will(U, v);
    int x = 0;
    sort(v.begin(), v.end());
    for(int i = 0; i < U; i ++){
        long long willA = will.upper_bound(i);
        bool l = false;
        for( ; x < v.size(); x ++){
            if(v[x] >= i){
                l = true;
                assert(v[x] == willA);
                break;
            }
        }
        assert(l || willA == -1);
    }
    x = v.size() - 1;
    for(int i = U - 1; i >= 0; i --){
        long long willA = will.lower_bound(i);
        bool l = false;
        for( ; x >= 0; x --){
            if(v[x] <= i){
                l = true;
                assert(v[x] == willA);
                break;
            }
        }
        assert(l || willA == -1);
    }
}

void testWillardYgen(){
    vector<long long> v;
    long long U = (1LL << 28);
    int n = 1e5 + 2;
    for(int i = 0; i < n; i ++){
        v.push_back(rand() % U);
    }
    WillardYfast will(U, v);
    int x = 0;
    sort(v.begin(), v.end());
    for(int i = 0; i < U; i ++){
        long long willA = will.upper_bound(i);
        bool l = false;
        for( ; x < v.size(); x ++){
            if(v[x] >= i){
                l = true;
                assert(v[x] == willA);
                break;
            }
        }
        assert(l || willA == -1);
    }
    x = v.size() - 1;
    for(int i = U - 1; i >= 0; i --){
        long long willA = will.lower_bound(i);
        bool l = false;
        for( ; x >= 0; x --){
            if(v[x] <= i){
                l = true;
                assert(v[x] == willA);
                break;
            }
        }
        assert(l || willA == -1);
    }
}

int main(){

    testWillardX();
    testWillardXgen();
    testWillardY();
    testWillardYgen();

    return 0;
}