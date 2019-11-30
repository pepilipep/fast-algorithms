#ifndef CARTESIANTREE_H
#define CARTESIANTREE_H

class CartesianTree{

    int *p;
    int n;
    int root;

    void Add(int *a, int s){
        int prev = -1;
        int v = s - 1;
        while(v != -1 && a[s] < a[v]){
            prev = v;
            v = p[v];
        }
        p[s] = v;
        if(v == -1){
            root = s;
        }
        if(prev != -1){
            p[prev] = s;
        }
    }

public:

    CartesianTree(int _n, int *a) : n(_n){

        p = new int[n];
        p[0] = -1;
        root = 0;
        for(int s = 1; s < n; s ++){
            Add(a, s);
        }
    }

    ~CartesianTree(){
        delete[] p;
    }

    int* getParents(){
        return p;
    }

    int getRoot(){
        return root;
    }

};


#endif