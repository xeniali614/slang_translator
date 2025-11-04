//
// Created by pvyas on 10/28/2025.
//
#include <string>
#include <vector>
#include "merge_sort.h"
#include <tuple>
#include <utility>

//browse alphabetically or by upvotes
//merge sort: split search in half continuously, sort each smaller piece
//vector pair of word and def
void mergeAlphaData(std::vector<std::pair<std::string ,std::string>>& slang, int low, int mid, int high){
  //put left half of data into a vector
  std::vector<std::pair<std::string ,std::string>> leftData(slang.begin() + low, slang.begin() + mid + 1);
  //put right half of data into a vector
  std::vector<std::pair<std::string ,std::string>> rightData(slang.begin() + mid + 1, slang.begin() + high + 1);
  int i = 0;
  int j = 0;
  int k = low;
  while(i < leftData.size() && j < rightData.size()){
    //if the data on the left is less than or equal to the data on the right, put that data in slang
    if(leftData[i] <= rightData[j]){
      slang[k] = leftData[i];
      //move i forward
      i++;
    }else{
      //if the data on the left is greater than the data on the right, put that data in slang
      slang[k] = rightData[j];
      //move j forward
      j++;
    }
    //move k forward to continue comparisons
    k++;
  }
  //copy any other data missing from the original comparisons for the left side
  while(i < leftData.size()){
    slang[k] = leftData[i];
    i++;
    k++;
  }
  //copy any other data missing from the original comparisons for the right side
  while(j < rightData.size()){
    slang[k] = rightData[j];
    j++;
    k++;
  }
}

void mergeAlphaSort(std::vector<std::pair<std::string ,std::string>>& slang, int low, int high){
  if(low < high){
    int mid = low + (high - low) / 2;
    //sort left
    mergeAlphaSort(slang, low, mid);
    //sort right
    mergeAlphaSort(slang, mid + 1, high);
    //merge
    mergeAlphaData(slang, low, mid, high);
  }
}

void mergeVoteData(std::vector<std::tuple<int, std::string, std::string>>& slang, int low, int mid, int high) {
  //put left half of data into a vector
  std::vector<std::tuple<int, std::string, std::string>> leftData(slang.begin() + low, slang.begin() + mid + 1);
  //put right half of data into a vector
  std::vector<std::tuple<int, std::string, std::string>> rightData(slang.begin() + mid + 1, slang.begin() + high + 1);
  int i = 0;
  int j = 0;
  int k = low;

  while(i < leftData.size() && j < rightData.size()){
    //if the data on the left is greater than or equal to the data on the right, put that data in slang
    //std::get<0> is used for tuples, accesses index 0 of data[i]
    if(std::get<0>(leftData[i]) >= std::get<0>(rightData[j])){
      slang[k] = leftData[i];
      //increment i
      i++;
    }else{
      //if the data on the left is greater than the data on the right, put that data in slang
      slang[k] = rightData[j];
      //increment j
      j++;
    }
    //move k forward to continue comparisons
    k++;
  }
  //copy any other data missing from the original comparisons for the left side
  while(i < leftData.size()){
    slang[k] = leftData[i];
    i++;
    k++;
  }
  //copy any other data missing from the original comparisons for the right side
  while(j < rightData.size()){
    slang[k] = rightData[j];
    j++;
    k++;
  }
}

void mergeVoteSort(std::vector<std::tuple<int, std::string, std::string>>& slang, int low, int high) {
  if(low < high){
    int mid = low + (high - low) / 2;
    //sort left
    mergeVoteSort(slang, low, mid);
    //sort right
    mergeVoteSort(slang, mid + 1, high);
    //merge
    mergeVoteData(slang, low, mid, high);
  }
}
