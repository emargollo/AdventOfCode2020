#pragma once

#include "pch.h"
#include "reader.h"
#include "days.h"

int sum_vector(std::vector<int> combination) {
    int sum = 0;
    for (int value : combination) {
        sum += value;
    }
    return sum;
}

int findCombination(std::vector<int> numbers, int target, int combinationTarget, std::vector<int> currentCombination) {
    int sum = sum_vector(currentCombination);

    if (sum > target) {
        return -1;
    }
    
    if (sum == target && currentCombination.size() == combinationTarget) {
        std::cout << "combination found: ";
        int mult = 1;
        for (int value : currentCombination) {
            mult *= value;
            std::cout << value << " ";
        }
        std::cout << std::endl;
        std::cout << "result: " << mult << std::endl;
        return mult;
    }

    for (int value : numbers) {
        std::vector<int> newCombination = currentCombination;
        newCombination.push_back(value);

        if (newCombination.size() > combinationTarget) {
            return -1;
        }

        std::vector<int> remaining(numbers);
        remaining.erase(remaining.begin());

        int result = findCombination(remaining, target, combinationTarget, newCombination);
        if (result > 0) return result;
    }
    return -1;
}

int day1()
{
    std::ifstream ifs("Day1Input.txt", std::ifstream::in);
    std::vector<int> input = read_ints(ifs);
    
    int test1 = findCombination(input, 2020, 2, std::vector<int>());
    int test2 = findCombination(input, 2020, 3, std::vector<int>());
    return 0;
}

/*
* Output:
* combination found: 833 1187
* result: 988771
* combination found: 1237 511 272
* result: 171933104
*/