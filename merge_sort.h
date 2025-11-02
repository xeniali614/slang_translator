//
// Created by pvyas on 10/28/2025.
//
#include <string>
#include <vector>
#include <tuple>

#ifndef MERGE_SORT_H
#define MERGE_SORT_H
//browse alphabetically or by upvotes
//merge sort: split search in half continuously, sort each smaller piece


void mergeAlphaData(std::vector<pair<std::string ,std::string>>& slang, int low, int mid, int high);
void mergeAlphaSort(std::vector<pair<std::string ,std::string>>& slang, int low, int high);
void mergeVoteData(std::vector<std::tuple<int, std::string, std::string>>& slang, int low, int mid, int high);
void mergeVoteSort(std::vector<<std::tuple<int, std::string, std::string>>>& slang, int low, int high);
#endif //MERGE_SORT_H
