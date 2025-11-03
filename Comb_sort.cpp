//
// Created by xenia on 10/31/2025.
//

#include "Comb_sort.h"

//Comb sort for alphabet
void combsort_alphabet(vector<pair<string,string>>& alphabet){
    int gap = alphabet.size();
    float shrink= 1.3;
    bool sorted = false;

    //If the gap is 1, while loop ends
    while(!sorted){
        //gap is divided by shrink size of 1.3
        gap = int(gap/shrink);
        if(gap <= 1){
            gap=1;
            sorted = true;
        }

        //switches the position of two if the string of i is infront of the string of i plus gap
        for(int i=0;i+gap <alphabet.size();i++){
            if(alphabet[i].first > alphabet[i+gap].first){
                swap(alphabet[i],alphabet[i+gap]);
                sorted = false;
            }

        }
    }
}

//Comb sort for upvotes
void combsort_upvotes(vector<tuple<int,string,string>>& alphabet){
    int gap = alphabet.size();
    float shrink= 1.3;
    bool sorted = false;

    //If the gap is 1, while loop ends
    while(!sorted){
        //gap is divided by shrink size of 1.3
        gap = int(gap/shrink);
        if(gap <= 1){
            gap=1;
            sorted = true;
        }
        //switches the position of two if the string of i is infront of the upvote of i plus gap
        for(int i=0;i+gap <alphabet.size();i++){
            if(get<0>(alphabet[i]) < get<0>(alphabet[i+gap])){
                swap(alphabet[i],alphabet[i+gap]);
                sorted = false;
            }

        }
    }
}

//Combsort by downvotes
void combsort_downvotes(vector<tuple<int,string,string>>& alphabet){
    int gap = alphabet.size();
    float shrink= 1.3;
    bool sorted = false;

    //If the gap is 1, while loop ends
    while(!sorted){
        //gap is divided by shrink size of 1.3
        gap = int(gap/shrink);
        if(gap <= 1){
            gap=1;
            sorted = true;
        }

        //switches the position of two if the string of i is infront of the downvote of i plus gap
        for(int i=0;i+gap <alphabet.size();i++){
            if(get<0>(alphabet[i]) < get<0>(alphabet[i+gap])){
                swap(alphabet[i],alphabet[i+gap]);
                sorted = false;
            }

        }
    }
}

