#ifndef WILLARDXFAST_H
#define WILLARDXFAST_H

#include "node.h"
#include <unordered_map>
#include <vector>
#include <cmath>

#include <iostream>

typedef long long ll;

class WillardXfast{

    node* root;
    ll U;
    ll logU;
    std::vector< std::unordered_map<ll, node*> > S;

    std::vector<char> bits(ll x){
        std::vector<char> bits;
        bits.assign(logU, 0);
        int idx = logU - 1;
        while(x){
            bits[idx] = x & 1;
            x /= 2;
            idx --;
        }
        return bits;
    }

    void insert(const std::vector<char>& x, ll num, node *& cur, int depth){
        if(depth == logU){
            cur = new node(num);
            return;
        }
        if(cur == nullptr){
            cur = new node(num);
        }
        insert(x, 2 * num + x[depth], x[depth] ? cur->right : cur->left, depth + 1);
        cur->calc();
    } 

    void dfs(node *& cur, int depth, node **&pr){
        if(cur == nullptr){
            return;
        }
        S[depth][cur->num] = cur;
        if(depth == logU){
            if(pr != nullptr){
                cur->left = (*pr);
                (*pr)->right = cur;
            }
            pr = &cur;
            return;
        }
        dfs(cur->left, depth + 1, pr);
        dfs(cur->right, depth + 1, pr);
    }

    void deleteDfs(node *& cur, int depth){
        if(cur == nullptr){
            return;
        }
        if(depth == logU){
            delete cur;
            return;
        }
        deleteDfs(cur->left, depth + 1);
        deleteDfs(cur->right, depth + 1);
        delete cur;
    }

public:

    WillardXfast(ll _U, std::vector<ll> nums) : U(_U){
        root = nullptr;
        logU = ceil(log2(U));
        S.resize(logU + 1);
        for(ll x : nums){
            insert(bits(x), 0, root, 0);
        }
        node **nz = nullptr;
        dfs(root, 0, nz);
    }

    ~WillardXfast(){
        deleteDfs(root, 0);
    }

    ll upper_bound(ll x){
        if(root->rightLeaf->num < x){
            return -1;
        }
        int l = -1;
        int r = logU;
        int mid;
        node *q;

        if(S[r].find(x) != S[r].end()){
            return x;
        }
        while(l + 1 < r){
            mid = (l + r) / 2;
            auto found = S[mid].find(x >> (logU - mid));
            if(found != S[mid].end()){
                l = mid;
                q = found->second;
            }
            else{
                r = mid;
            }
        }

        if(q->right != nullptr){
            return q->leftLeaf->num;
        }
        else{
            return q->rightLeaf->right->num;
        }

    }

    ll lower_bound(ll x){
        if(root->leftLeaf->num > x){
            return -1;
        }
        int l = -1;
        int r = logU;
        int mid;
        node *q;

        if(S[r].find(x) != S[r].end()){
            return x;
        }

        while(l + 1 < r){
            mid = (l + r) / 2;
            auto found = S[mid].find(x >> (logU - mid));
            if(found != S[mid].end()){
                l = mid;
                q = found->second;
            }
            else{
                r = mid;
            }
        }
        if(q->left != nullptr){
            return q->rightLeaf->num;
        }
        else{
            return q->leftLeaf->left->num;
        }

    }

    

};

#endif