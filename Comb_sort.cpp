//
// Created by xenia on 10/31/2025.
//

#include "Comb_sort.h"


void combsort_alphabet(vector<pair<string,string>>& alphabet){
    int gap = alphabet.size();
    float shrink= 1.3;
    bool sorted = false;

    while(!sorted){
        gap = int(gap/shrink);
        if(gap <= 1){
            gap=1;
            sorted = true;
        }
        for(int i=0;i+gap <alphabet.size();i++){
            if(alphabet[i].first > alphabet[i+gap].first){
                swap(alphabet[i],alphabet[i+gap]);
                sorted = false;
            }
            else if(alphabet[i].first == alphabet[i+gap].first){
              sorted = false;
            }
        }
    }
}

void combsort_upvotes(vector<tuple<int,string,string>>& alphabet){
    int gap = alphabet.size();
    float shrink= 1.3;
    bool sorted = false;

    while(!sorted){
        gap = int(gap/shrink);
        if(gap <= 1){
            gap=1;
            sorted = true;
        }
        for(int i=0;i+gap <alphabet.size();i++){
            if(get<0>(alphabet[i]) > get<0>(alphabet[i+gap])){
                swap(alphabet[i],alphabet[i+gap]);
                sorted = false;
            }
            else if(get<0>(alphabet[i]) == get<0>(alphabet[i+gap])){
              sorted = false;
            }
        }
    }
}

void combsort_downvotes(vector<tuple<int,string,string>>& alphabet){
    int gap = alphabet.size();
    float shrink= 1.3;
    bool sorted = false;

    while(!sorted){
        gap = int(gap/shrink);
        if(gap <= 1){
            gap=1;
            sorted = true;
        }
        for(int i=0;i+gap <alphabet.size();i++){
            if(get<0>(alphabet[i]) > get<0>(alphabet[i+gap])){
                swap(alphabet[i],alphabet[i+gap]);
                sorted = false;
            }
            else if(get<0>(alphabet[i]) == get<0>(alphabet[i+gap])){
                sorted = false;
            }
        }
    }
}

