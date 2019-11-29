#ifndef RMQLOG_H
#define RMQLOG_H

class RMQLog{

    int n;
    int *log, *pow;
    int **table;
    int *a;

public:

    RMQLog(int _n, int *_a) : n(_n){
        a = new int[n+1];
        log = new int[n+1];
        log[0] = 0;
        pow = new int[n+1];
        pow[0] = 1;
        a[0] = _a[0];
        for(int i = 1; i <= n; i ++){
            pow[i] = pow[i - 1] * 2;
            a[i] = _a[i];
            log[i] = pow[log[i-1] + 1] <= i ? log[i - 1] + 1 : log[i - 1];
        }
        table = new int*[log[n] + 1];
        for(int i = 0; i <= log[n]; i ++){
            table[i] = new int[n+1];
        }
        for(int i = 0; i < n; i ++){
            table[0][i] = i;
        }
        for(int i = 1; i <= log[n]; i ++){
            for(int j = 0; j + 2 * pow[i - 1] <= n; j ++){
                if(a[table[i - 1][j]] <= a[table[i - 1][j + pow[i - 1]]]){
                    table[i][j] = table[i - 1][j];
                }
                else{
                    table[i][j] = table[i - 1][j + pow[i - 1]];
                }
            }
        }
    }

    int Query(int i, int j){
        int l = log[j - i + 1];
        if(a[table[l][i]] <= a[table[l][j - pow[l] + 1]]){
            return table[l][i];
        }
        else{
            return table[l][j - pow[l] + 1];
        }
    }

    ~RMQLog(){
        for(int i = 0; i <= log[n]; i ++){
            delete[] table[i];
        }
        delete[] table;
        delete[] log;
        delete[] pow;
        delete[] a;
    }


};


#endif