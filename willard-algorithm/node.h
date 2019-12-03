#ifndef NODE_H
#define NODE_H

typedef long long ll;

struct node{

    ll num;
    node *left, *right;
    node *leftLeaf, *rightLeaf;

    node(ll _num) : num(_num) {
        left = right = nullptr;
        leftLeaf = rightLeaf = this;
    }

    void calc(){
        if(left != nullptr)
            leftLeaf = left->leftLeaf;
        else
            leftLeaf = right->leftLeaf;
        if(right != nullptr)
            rightLeaf = right->rightLeaf;
        else
            rightLeaf = left->rightLeaf;
    }

    node(ll _num, node *_left, node *_right) : num(_num), left(_left), right(_right) {
        calc();
    }


};

#endif