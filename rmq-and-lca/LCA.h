#ifndef LCA_H
#define LCA_H

#include "RMQPlusMinus.h"
#include <vector>

class LCA{

    int n;
    int *depth;
    int *start;
    int *time;
    int root;
    vector<int> *children;
    RMQPlusMinus *rmq;

    void dfs(int v, int &t, int d){
        start[v] = t;
        time[t] = v;
        depth[t] = d;
        for(int next : children[v]){
            t ++;
            dfs(next, t, d + 1);
            time[t] = v;
            depth[t] = d;
        }
        t ++;
    }

public:

    LCA(int _n, int *p, int _root) : n(_n), root(_root) {

        depth = new int[2 * n - 1];
        start = new int[n];
        time = new int[2 * n - 1];
        children = new vector<int>[n];

        for(int i = 0; i < n; i ++){
            if(p[i] != -1){
                children[p[i]].push_back(i);
            }
        }

        int t = 0;
        dfs(root, t, 0);

        rmq = new RMQPlusMinus(2 * n - 1, depth);
        
    }

    int Query(int x, int y){
        return time[rmq->Query(min(start[x], start[y]),max(start[x], start[y]))];
    }

    ~LCA(){
        delete[] children;
        delete[] depth;
        delete[] start;
        delete[] time;
        delete rmq;

    }

};



#endif