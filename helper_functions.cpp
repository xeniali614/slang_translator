//
// Created by joyce on 11/2/2025.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

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
    std::ifstream file("urbandict-word-defs.csv");
    //std::ifstream file("smaller-test-file.csv");
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

        while (std::getline(ss, cell, ',')) {
            rowCells.push_back(cell);
        }

        // Process the current row's cells
        fileRow curRow;
        try {
            curRow.id = std::stol(rowCells[0]);
            curRow.word = rowCells[1];
            curRow.upvotes = std::stoi(rowCells[2]);
            curRow.downvotes = std::stoi(rowCells[3]);
            curRow.author = rowCells[4];
            curRow.definition = rowCells[5];
            data.push_back(curRow);
        } catch (...) {
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
            std::cerr << "Invalid input. Please select 0, 1, or 2" << std::endl;
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