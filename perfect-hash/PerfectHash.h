#ifndef PERFECTHASH_H
#define PERFECTHASH_H

#include <vector>

typedef long long ll;

class PerfectHash{

    ll p;
    int n;
    ll C;
    std::vector<ll> c;
    std::vector<std::vector<ll> > S;
    std::vector<std::vector<ll> > H;

    int hash(const ll& x, const ll& _c, const ll& m){
        return ((_c * x) % p) % m;
    }

    bool checkAdmissible2(std::vector<ll> _S){
        ll cnt = 0;
        for(ll s : _S){
            int hit = hash(s, C, n);
            cnt += S[hit].size();
            if(cnt > n){
                return false;
            }
            S[hit].push_back(s);
        }
        return true;
    }

    bool checkAdmissible(int idx){
        ll m = (ll)S[idx].size() * S[idx].size();
        for(ll s : S[idx]){
            int hit = hash(s, c[idx], m);
            if(H[idx][hit] != -1){
                return false;
            }
            H[idx][hit] = s;
        }
        return true;
    }

    void SquarePerfectHash(int idx){
        int curN = S[idx].size();
        if(curN == 0){
            return;
        }
        H[idx].assign(curN * curN, -1);
        while(!checkAdmissible(idx)){
            H[idx].assign(curN * curN, -1);
            c[idx] ++;
        }
    }

public:

    PerfectHash(std::vector<ll> _S, ll _p) : n(_S.size()), p(_p){
        C = 1;
        S.assign(n, {});
        H.assign(n, {});
        c.assign(n, 1);
        while(!checkAdmissible2(_S)){
            C ++;
            S.assign(n, {});
        }
        for(int i = 0; i < n; i ++){
            SquarePerfectHash(i);
        }


    }

    bool Search(ll x){
        int j = hash(x, C, n);
        if(H[j].size() == 0){
            return false;
        }
        int i = hash(x, c[j], S[j].size() * S[j].size());
        return H[j][i] == x;
    }


};

#endif