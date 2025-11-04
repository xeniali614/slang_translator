//
// Created by joyce on 11/2/2025.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <tuple>
#include <cmath>

struct fileRow {
    long int id;
    std::string word;
    int upvotes;
    int downvotes;
    std::string author;
    std::string definition;
};

std::vector<fileRow> processFile() {
    // Open file
    //std::ifstream file("urbandict-word-defs.csv");
    std::ifstream file("smaller-test-file.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return {};
    }

    // Skip header line
    std::string line;
    std::getline(file, line);

    // Parse file data
    std::vector<fileRow> data;
    while (std::getline(file, line)) {
        // Declarations
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> rowCells;

        // Remove delimiters and push into a vector
        for (int i = 0; i < 5; i++) {
            std::getline(ss, cell, ',');
            rowCells.push_back(cell);
        }
        std::string skip;
        getline(ss, skip, '"');
        getline(ss, cell, '"');
        rowCells.push_back(cell);

        // Skip if data is missing a field
        if (rowCells.size() < 6) {
            continue;
        }

        // Process the current row's cells
        try {
            fileRow curRow;
            curRow.id = std::stol(rowCells[0]);
            curRow.word = rowCells[1];
            curRow.upvotes = std::stoi(rowCells[2]);
            curRow.downvotes = std::stoi(rowCells[3]);
            curRow.author = rowCells[4];
            curRow.definition = rowCells[5];

            // Remove whitespace from the beginning and end of strings
            size_t first = curRow.word.find_first_not_of(" \t\n\r\f\v");
            if (std::string::npos == first) {
                curRow.word = "";
            }
            size_t last = curRow.word.find_last_not_of(" \t\n\r\f\v");
            curRow.word=curRow.word.substr(first, (last - first + 1));

            first = curRow.definition.find_first_not_of(" \t\n\r\f\v");
            if (std::string::npos == first) {
                curRow.definition = "";
            }
            last = curRow.definition.find_last_not_of(" \t\n\r\f\v");
            curRow.definition=curRow.definition.substr(first, (last - first + 1));

            // Throw away data that isn't alphanumeric or whitespace
            bool valid = true;
            for (char c : curRow.word) {
                if (!std::isalnum(c) && !std::isspace(c)) {
                    valid = false;
                    break;
                }
            }

            // Throw away data without a valid number of upvotes or downvotes
            if (curRow.upvotes < 0 || curRow.downvotes < 0) {
                valid = false;
            }

            // Throw away data without a word or definition
            if (curRow.word.empty() || curRow.definition.empty()) {
                valid = false;
            }

            if (!valid) {
                continue;
            }

            data.push_back(curRow);
        } catch (const std::exception& e) {
            continue;
        }
    }

    file.close();
    return data;
}

void commandInstructions() {
    std::cout << "Please choose from the following: " << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Search slang" << std::endl;
    std::cout << "2. Browse" << std::endl;
}

int getInput(int min, int max) {
    while (true) {
        // Get user input
        std::string curInput;
        std::getline(std::cin, curInput);

        // Safely process user input
        int choice = -1;
        try {
            choice = std::stoi(curInput);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid input. Please select a number between " << min << " and " << max << std::endl;
            continue;
        }
        if (choice < min || choice > max) {
            std::cerr << "Invalid input. Please select a number between " << min << " and " << max << std::endl;
            continue;
        }
        return choice;
    }
}

void sortInstructions() {
    std::cout << "Please select a sort method: " << std::endl;
    std::cout << "1. Comb Sort" << std::endl;
    std::cout << "2. Merge Sort" << std::endl;
}

void displaySearched25_upvotes(int i, std::vector<std::tuple<int, std::string, std::string>>& byUpvotes) {
    if (i == 0) {
        std::cout << "No more results :/" << std::endl;
    }else if (i < 25) {
        int count = 1;
        while (!byUpvotes.empty()) {
            std::cout << count << ") " << "Upvotes: " << std::get<0>(byUpvotes[0]) << " | " << std::get<1>(byUpvotes[0]) << " - \"" <<std::get<2>(byUpvotes[0]) << "\"" << std::endl;
            byUpvotes.erase(byUpvotes.begin());
            count++;
        }
    }else {
        int count = 1;
        //if there are more than 25 entries make pages
        int page_number = 1;
        int g = 0;
        //number of pages, get decimal val
        int num_pages = ceil(i/25.00);
        while (true) {
            std::cout << "\n--- Page " << page_number << " of " << num_pages << " ---" << std::endl;
            int end_index = std::min(g + 25, i);
            for (int j = g; j < end_index; j++) {
                std::cout << (j + 1) << ") " << "Upvotes: " << std::get<0>(byUpvotes[j]) << " | " << std::get<1>(byUpvotes[j]) << " - \"" << std::get<2>(byUpvotes[j]) << "\"" << std::endl;
            }
            std::cout  << std::endl;
            std::string input;
            std::cout << "0. Return to menu" << std::endl;
            std::cout << "1. Previous page" << std::endl;
            std::cout << "2. Next page" << std::endl;
            std::getline(std::cin, input);
            if (input == "0") {
                break;
            }else if (input == "1") {
                if (page_number == 1) {
                    std::cout << "You are on the First Page" << std::endl;
                }else{
                    page_number--;
                    g-=25;
                }
            }else if (input == "2") {
                if (page_number == (num_pages)) {
                    std::cout << "You are on the Last Page" << std::endl;
                }else {
                    page_number++;
                    g+=25;
                }
            }
        }
    }
}
void displaySearched25_downvotes(int i, std::vector<std::tuple<int, std::string, std::string>>& byDownvotes) {
    if (i == 0) {
        std::cout << "No more results :/" << std::endl;
    }else if (i < 25) {
        int count = 1;
        while (!byDownvotes.empty()) {
            std::cout << count << ") " << "Downvotes: " << std::get<0>(byDownvotes[0]) << " | " << std::get<1>(byDownvotes[0]) << " - \"" <<std::get<2>(byDownvotes[0]) << "\"" << std::endl;
            byDownvotes.erase(byDownvotes.begin());
            count++;
        }
    }else {
        int count = 1;
        //if there are more than 25 entries make pages
        int page_number = 1;
        int g = 0;
        //number of pages, get decimal val
        int num_pages = ceil(i/25.00);
        while (true) {
            std::cout << "\n--- Page " << page_number << " of " << num_pages << " ---" << std::endl;
            int end_index = std::min(g + 25, i);
            for (int j = g; j < end_index; j++) {
                std::cout << (j + 1) << ") " << "Downvotes: " << std::get<0>(byDownvotes[j]) << " | " << std::get<1>(byDownvotes[j]) << " - \"" << std::get<2>(byDownvotes[j]) << "\"" << std::endl;
            }
            std::cout  << std::endl;
            std::string input;
            std::cout << "0. Return to menu" << std::endl;
            std::cout << "1. Previous page" << std::endl;
            std::cout << "2. Next page" << std::endl;
            std::getline(std::cin, input);
            if (input == "0") {
                break;
            }else if (input == "1") {
                if (page_number == 1) {
                    std::cout << "You are on the First Page" << std::endl;
                }else{
                    page_number--;
                    g-=25;
                }
            }else if (input == "2") {
                if (page_number == (num_pages)) {
                    std::cout << "You are on the Last Page" << std::endl;
                }else {
                    page_number++;
                    g+=25;
                }
            }
        }
    }
}
void displaySearched25_alphabet(int i, std::vector<std::pair<std::string, std::string>>& byAlphabet) {
    if (i == 0) {
        std::cout << "No more results :/" << std::endl;
    }else if (i < 25) {
        int count = 1;
        while (!byAlphabet.empty()) {
            std::cout << count << ") " << byAlphabet[0].first << " - \"" <<byAlphabet[0].second << "\"" << std::endl;
            byAlphabet.erase(byAlphabet.begin());
            count++;
        }
    }else {
        int count = 1;
        //if there are more than 25 entries make pages
        int page_number = 1;
        int g = 0;
        //number of pages, get decimal val
        int num_pages = ceil(i/25.00);
        while (true) {
            std::cout << "\n--- Page " << page_number << " of " << num_pages << " ---" << std::endl;
            int end_index = std::min(g + 25, i);
            for (int j = g; j < end_index; j++) {
                std::cout << (j + 1) << ") " << byAlphabet[j].first<< " - \"" << byAlphabet[j].second << "\"" << std::endl;
            }
            std::cout  << std::endl;
            std::string input;
            std::cout << "0. Return to menu" << std::endl;
            std::cout << "1. Previous page" << std::endl;
            std::cout << "2. Next page" << std::endl;
            std::getline(std::cin, input);
            if (input == "0") {
                break;
            }else if (input == "1") {
                if (page_number == 1) {
                    std::cout << "You are on the First Page" << std::endl;
                }else{
                    page_number--;
                    g-=25;
                }
            }else if (input == "2") {
                if (page_number == (num_pages)) {
                    std::cout << "You are on the Last Page" << std::endl;
                }else {
                    page_number++;
                    g+=25;
                }
            }
        }
    }
}