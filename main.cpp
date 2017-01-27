#include <vector>
#include <utility>
#include <iostream>
#include "aliasMethod.h"
using namespace std;
int main(){      
    vector<pair<int, double>> dist;
    dist.push_back(make_pair(0, 0.2 + 1e-16));
    dist.push_back(make_pair(1, 0.15));
    dist.push_back(make_pair(2, 0.05));
    dist.push_back(make_pair(3, 0.05));
    dist.push_back(make_pair(4, 0.15));
    dist.push_back(make_pair(5, 0.2));
    dist.push_back(make_pair(6, 0.05));
    dist.push_back(make_pair(7, 0.05));
    dist.push_back(make_pair(8, 0.06));
    dist.push_back(make_pair(9, 0.04));
    discreteProbabilityDistribution <int> aliasM(dist);
    vector<int> appearances(10, 0);
    for(int i = 0; i < 1000000; ++i){
        int rolling = aliasM.roll();
        appearances[rolling]++;
    }
    for(int i = 0; i < 10; ++i){
        cout << i << ": " << appearances[i] << endl;
    }
    return 0;
}
