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

void mergeAlphaData(std::vector<std::string>& slang, int low, int mid, int high){
  //put left half of data into a vector
  std::vector<std::string> leftData(slang.begin() + low, slang.begin() + mid + 1);
  //put right half of data into a vector
  std::vector<std::string> rightData(slang.begin() + mid + 1, slang.begin() + high + 1);
  int i = 0;
  int j = 0;
  int k = low;

  while(i < leftData.size() && j < rightData.size()){
    if(leftData[i] <= rightData[j]){
      slang[k] = leftData[i];
      i++;
    }else{
      slang[k] = rightData[j];
      j++;
    }
    k++;
  }

  while(i < leftData.size()){
    slang[k] = leftData[i];
    i++;
    k++;
  }
  while(j < rightData.size()){
    slang[k] = rightData[j];
    j++;
    k++;
  }
}

void mergeAlphaSort(std::vector<std::string>& slang, int low, int high){
  if(low < high){
    int mid = low + (high - low) / 2;
    mergeAlphaSort(slang, low, mid);
    mergeAlphaSort(slang, mid + 1, high);
    mergeAlphaData(slang, low, mid, high);
  }
  std::vector<std::string> final;
  for(int i = 0; i < 25; i++){
    final.push_back(slang[i]);
  }
  return final;
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
    if(std::get<0>(leftData[i]) => std::get<0>(rightData[j])){
      slang[k] = leftData[i];
      i++;
    }else{
      slang[k] = rightData[j];
      j++;
    }
    k++;
  }

  while(i < leftData.size()){
    slang[k] = leftData[i];
    i++;
    k++;
  }
  while(j < rightData.size()){
    slang[k] = rightData[j];
    j++;
    k++;
  }
}

void mergeVoteSort(std::vector<std::tuple<int, std::string, std::string>>& slang, int low, int high) {
  if(low < high){
    int mid = low + (high - low) / 2;
    mergeVoteSort(slang, low, mid);
    mergeVoteSort(slang, mid + 1, high);
    mergeVoteData(slang, low, mid, high);
  }
}
