#ifndef RMQPLUSMINUS_H
#define RMQPLUSMINUS_H

#include "RMQNaive.h"
#include "RMQLog.h"

#include <cmath>
#include <unordered_map>

using namespace std;

class RMQPlusMinus{

    int *a;
    int n, m;
    int *numD;
    int *ind;
    RMQLog *rmqLog;
    int B;
    unordered_map<int, RMQNaive*> rmqNaive; 

public:

    RMQPlusMinus(int _n, int *_a) {
        
        n = _n;
        a = new int[n];
        B = log2(n) / 2;
        if(!B) B = 1;
        m = n / B;
        if(m * B != n){
            m ++;
        }
        
        numD = new int[m];
        ind = new int[m];
        int *minSt = new int[m];

        for(int i = 0; i < n; i ++){
            a[i] = _a[i];
        }

        int *D = new int[B];
        for(int i = 0; i < m; i ++){
            numD[i] = 0;
            D[0] = 0;
            int j;
            for(j = 1; j < B && i * B + j < n; j ++){
                numD[i] *= 2;
                D[j] = a[i * B + j] - a[i * B];
                numD[i] += (a[i * B + j - 1] - a[i * B + j] + 1) / 2;
            }
            while(j < B){
                numD[i] *= 2;
                D[j] = D[j-1] + 1;
                numD[i] += (a[i * B + j - 1] - a[i * B + j] + 1) / 2;
                j++;
            }
            if(!rmqNaive.count(numD[i])){
                rmqNaive[numD[i]] = new RMQNaive(B, D);
            }
            ind[i] = rmqNaive[numD[i]]->Query(0, B-1);
            minSt[i] = a[i * B + ind[i]];
        }
        rmqLog = new RMQLog(m, minSt);
        delete[] minSt;
        delete[] D;
    }

    int Query(int i, int j){
        int I = i / B;
        int J = j / B;
        if(I == J){
            return I * B + rmqNaive[numD[I]]->Query(i - I * B, j - J * B);
        }
        int x1 = rmqNaive[numD[I]]->Query(i - I * B, B - 1);
        int y1 = I * B + x1;
        int x2 = rmqNaive[numD[J]]->Query(0, j - J * B);
        int y2 = J * B + x2;
        if(I + 1 == J){
            if(a[y1] <= a[y2]){
                return y1;
            }
            else{
                return y2;
            }
        }
        int x3 = rmqLog->Query(I + 1, J - 1);
        int y3 = x3 * B + ind[x3];
        if(a[y1] <= a[y2] && a[y1] <= a[y3]){
            return y1;
        }
        if(a[y3] <= a[y2]){
            return y3;
        }
        return y2;
    }


    ~RMQPlusMinus(){
        delete rmqLog;
        delete[] a;
        delete[] numD;
        for(auto& x : rmqNaive){
            delete x.second;
        }
    }

};


#endif