#ifndef RMQNAIVE_H
#define RMQNAIVE_H

class RMQNaive{
    
    int **table;
    int n;

public:

    RMQNaive(int _n, int *a) : n(_n){
        table = new int*[n];
        for(int i = 0; i < n; i ++){
            table[i] = new int[n];
        }
        for(int i = 0; i < n; i ++){
            table[i][i] = i;
            for(int j = i + 1; j < n; j ++){
                if(a[j] < a[table[i][j - 1]]){
                    table[i][j] = j;
                }
                else{
                    table[i][j]  = table[i][j - 1];
                }
            }
        }
    }

    int Query(int i, int j){
        return table[i][j];
    }

    ~RMQNaive(){
        for(int i = 0; i < n; i ++){
            delete[] table[i];
        }
        delete[] table;
    }
};

#endif