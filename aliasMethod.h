#include <random>
#include <queue>
#pragma once
using namespace std;

template<typename T> 
class discreteProbabilityDistribution{

    public:
        discreteProbabilityDistribution(vector<pair<T, double> > aDistribution);
        T roll();
        void changeSeed(int aSeed);
    private:
        vector<T> aliasTranslation;
        vector<double> prob;
        vector<int> alias;
        mt19937 gen;


};

template <typename T> 
discreteProbabilityDistribution<T>::discreteProbabilityDistribution(vector<pair<T, double> > aDistribution):gen((random_device())())
{

    int amountOfItems = aDistribution.size();
    prob.resize(amountOfItems);
    alias.resize(amountOfItems);
    aliasTranslation.resize(amountOfItems);
    vector<double> probability(amountOfItems);

    queue<int> small;
    queue<int> large;

    for(int i = 0; i < amountOfItems; ++i){
        aliasTranslation[i] = aDistribution[i].first;
        probability[i] = aDistribution[i].second * amountOfItems;
        if(probability[i] < 1){
            small.push(i);
        }else{
            large.push(i);
        }
    }

    int big;
    int little;
    while(!small.empty() && !large.empty()){
        big = large.front();
        little = small.front();
        large.pop();
        small.pop();
        prob[little] = probability[little];
        alias[little] = big;
        
        probability[big] = (probability[big] + prob[little]) - 1;
        if(probability[big] < 1){
            small.push(big);
        } else{
            large.push(big);

        }
    }
    
    while(!large.empty()){
        big = large.front();
        large.pop();
        prob[big] = 1.0;
    }

    while(!small.empty()){
        little = small.front();
        small.pop();
        prob[little] = 1.0;
    }
}
template <typename T> 
T  discreteProbabilityDistribution<T>::roll(){

    int index;
    uniform_int_distribution<int> die(0, alias.size() - 1);

    int rolled = die(gen);
    bernoulli_distribution coin(prob[rolled]);
    if(coin(gen)){
        index = rolled;
    } else{
        index = alias[rolled];
    }
    return aliasTranslation[index];
}

template <typename T>

void discreteProbabilityDistribution<T>::changeSeed(int aSeed){
    gen.seed(aSeed);
}
