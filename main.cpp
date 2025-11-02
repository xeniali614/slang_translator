//
// Created by joyce on 11/2/2025.
//

#include <iostream>
#include <sstream>
#include <tuple>
#include "helper_functions.cpp"
#include "Comb_sort.h"

int main() {
    // Parse the CSV
    std::vector<fileRow> fileData = processFile();

    // Set data into pairs to be processed by the sorts
    std::vector<pair<std::string ,std::string>> byAlphabet;
    std::vector<tuple<int, std::string, std::string>> byUpvotes;
    std::vector<tuple<int, std::string, std::string>> byDownvotes;
    for (int i = 0; i < fileData.size(); i++) {
        byAlphabet.push_back({fileData[i].word, fileData[i].definition});
        byUpvotes.emplace_back(fileData[i].upvotes, fileData[i].word, fileData[i].definition);
        byDownvotes.emplace_back(fileData[i].downvotes, fileData[i].word, fileData[i].definition);
    }

    // Flags for sorts (used for execution times at the end)
    bool combSorted = false;
    bool mergeSorted = false;

    // Print welcome message and directions
    std::cout << "Welcome to Slang Translator!" << std::endl;
    std::cout << "*Viewer discretion advised due to potential vulgar/offensive language from Urban Dictionary*" << std::endl << std::endl;
    commandInstructions();

    // Get user input
    int first_choice = getInput(0, 2);

    // Loop until the user exits
    while (first_choice != 0) {
        // Search slang
        if (first_choice == 1) {
            // Print instructions and get user input
            std::cout << "Please enter the slang term/phrase you would like to search: " << std::endl;
            std::string slangInput;
            std::getline(std::cin, slangInput);

            // Process user input to be fully lowercase
            for (auto& letter : slangInput) {
                letter = tolower(letter);
            }

            // Search for user input in fileData and print definitions
            int count = 0;
            for (int i = 0; i < fileData.size(); i++) {
                // Process words in the dataset to be fully lowercase
                std::string dataSlang = fileData[i].word;
                for (auto& letter : dataSlang) {
                    letter = tolower(letter);
                }

                if (dataSlang == slangInput) {
                    count++;
                    std::cout << count << ") " << fileData[i].word << " - \"" << fileData[i].definition << "\"" << std::endl;
                }
            }

            if (count == 0) {
                std::cout << "No results found :/" << std::endl;
            }

            // Re-print instructions
            std::cout << std::endl;
            commandInstructions();

            // Get user's next choice
            first_choice = getInput(0, 2);

        // Browse
        } else if (first_choice == 2) {
            // Print instructions
            std::cout << "Please select the browse method: " << std::endl;
            std::cout << "1. Browse by alphabetical order" << std::endl;
            std::cout << "2. Browse by upvotes" << std::endl;
            std::cout << "3. Browse by downvotes" << std::endl;

            // Safely get and process user input for browse
            int second_choice = getInput(1, 3);

            sortInstructions();
            int third_choice = getInput(1, 2);

            // Browse by alphabetical order
            if (second_choice == 1) {
                // Comb sort
                if (third_choice == 1) {
                    combSorted = true;
                    combsort_alphabet(byAlphabet);

                    std::cout << "First 25 results: " << std::endl;
                    for (int i = 0; i < 25; i++) {
                        std::cout << i + 1 << ") " << std::get<0>(byAlphabet[i]) << " - " << std::get<1>(byAlphabet[i]) << std::endl;
                    }

                // Merge sort
                } else if (third_choice == 2) {
                    mergeSorted = true;
                    std::cout << "to do - merge sort alpha" << std::endl << std::endl;
                }


            // Browse by upvotes
            } else if (second_choice == 2) {
                // Comb sort
                if (third_choice == 1) {
                    combSorted = true;
                    combsort_upvotes(byUpvotes);

                    std::cout << "First 25 results: " << std::endl;
                    for (int i = 0; i < 25; i++) {
                        std::cout << i + 1 << ") ↑" << std::get<0>(byUpvotes[i]) << " " << std::get<1>(byUpvotes[i]) << " - " << std::get<2>(byUpvotes[i]) << std::endl;
                    }

                // Merge sort
                } else if (third_choice == 2) {
                    mergeSorted = true;
                    std::cout << "to do - merge sort upvotes" << std::endl << std::endl;
                }

            // Browse by downvotes
            } else if (second_choice == 3) {
                // Comb sort
                if (third_choice == 1) {
                    combSorted = true;
                    combsort_downvotes(byDownvotes);

                    std::cout << "First 25 results: " << std::endl;
                    for (int i = 0; i < 25; i++) {
                        std::cout << i + 1 << ") ↓" << std::get<0>(byDownvotes[i]) << " " << std::get<1>(byDownvotes[i]) << " - " << std::get<2>(byDownvotes[i]) << std::endl;
                    }

                // Merge sort
                } else if (third_choice == 2) {
                    mergeSorted = true;
                    std::cout << "to do - merge sort downvotes" << std::endl << std::endl;
                }

            }

            // Get user's next choice
            commandInstructions();
            first_choice = getInput(0, 2);
        }
    }

    // Exit message
    std::cout << "Thank you for using Slang Translator! :)" << std::endl;
    if (combSorted) {
        std::cout << "Comb Sort execution time: " << std::endl;
    }
    if (mergeSorted) {
        std::cout << "Merge Sort execution time: " << std::endl;
    }

    return 0;
}