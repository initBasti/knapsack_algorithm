#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>

using Items = std::vector<std::pair<unsigned int, unsigned int>>;
using Matrix = std::vector<std::vector<unsigned int>>;

int knapsack(unsigned int maxWeight, Items items)
{
        Matrix subsacks(items.size(), std::vector<unsigned int>(maxWeight, 0));
        Matrix keep(items.size(), std::vector<unsigned int>(maxWeight, 0));

        for (auto item = 0; item < static_cast<int>(items.size()); item++) {
                unsigned int itemWeight = items[item].first;
                unsigned int itemValue = items[item].second;

                for (unsigned int weight = 1; weight <= maxWeight; weight++) {
                        int weightIndex = weight - 1;
                        if (item == 0) {
                                if (itemWeight > weight) {
                                        subsacks[item][weightIndex] = 0;
                                        keep[item][weightIndex] = 0;
                                } else {
                                        subsacks[item][weightIndex] = itemValue;
                                        keep[item][weightIndex] = 1;
                                }
                                continue;
                        }
                        if (itemWeight > weight) {
                                subsacks[item][weightIndex] =
                                        subsacks[item-1][weightIndex];
                                keep[item][weightIndex] = 0;
                                continue;
                        } else if (itemWeight == weight) {
                                if (subsacks[item-1][weightIndex] > itemValue) {
                                        subsacks[item][weightIndex] =
                                                subsacks[item-1][weightIndex];
                                        keep[item][weightIndex] = 0;
                                } else {
                                        subsacks[item][weightIndex] = itemValue;
                                        keep[item][weightIndex] = 1;
                                }
                                continue;
                        }
                        int restWeightIndex = weight - itemWeight - 1;
                        unsigned int total_weight_value =
                                itemValue + subsacks[item-1][restWeightIndex];
                        if (subsacks[item-1][weightIndex] > total_weight_value) {
                                subsacks[item][weightIndex] =
                                        subsacks[item-1][weightIndex];
                                keep[item][weightIndex] = 0;
                        } else {
                                subsacks[item][weightIndex] =
                                        total_weight_value;
                                keep[item][weightIndex] = 1;
                        }
                }
        }

        const char* debug = std::getenv("KNAPSACK_DEBUG");
        if (debug) {
                std::cout << std::endl << "Sub-problems" << std::endl;
                for (int i = 0 ; i < static_cast<int>(subsacks.size()); i++) {
                        for (int j = 0;
                             j < static_cast<int>(subsacks[i].size()); j++) {
                                std::cout << "[" << subsacks[i][j] << "]";
                        }
                        std::cout << std::endl;
                }
                std::cout << std::endl << "Keep table" << std::endl;
                for (int i = 0 ; i < static_cast<int>(keep.size()); i++) {
                        for (int j = 0;
                             j < static_cast<int>(keep[i].size()); j++) {
                                std::cout << "[" << keep[i][j] << "]";
                        }
                        std::cout << std::endl;
                }
                std::cout << std::endl;
        }
        int startWeightIndex = maxWeight - 1;
        std::string useItems;
        for (int i = static_cast<int>(items.size())-1; i >= 0; i--) {
                if (keep[i][startWeightIndex] == 0)
                        continue;
                if (useItems.size() != 0)
                        useItems += "," + std::to_string(i+1);
                else
                        useItems += std::to_string(i+1);
                startWeightIndex -= items[i].first;
        }
        std::cout << "Use item/s: " << useItems << std::endl;
        return subsacks[static_cast<int>(items.size())-1][maxWeight-1];
}

int main(int argc, char *argv[])
{
        if (argc < 3) {
                std::cout << "Usage: {executable} {maximum weight} "
                          << "{item1-weight} {item1-value} "
                          << "{item2-weight} .." << std::endl;
                return 1;
        }
        if (argc % 2 != 0) {
                std::cerr << "Invalid input, provide full pairs with weight "
                          << "and value" << std::endl;
        }
        unsigned int maxWeight = std::stoi(argv[1]);
        Items items;

        int i = 2;
        while (i < argc) {
                int weight = std::stoi(argv[i]);
                int value = std::stoi(argv[i+1]);
                items.push_back(std::make_pair(weight, value));
                i += 2;
        }

        for (auto item = 0; item < static_cast<int>(items.size()); item++) {
                std::cout << item+1 << ". Item weight " << items[item].first
                          << ", Item value " << items[item].second << std::endl;
        }

        int total = knapsack(maxWeight, items);
        std::cout << "Maximum value = " << total << std::endl;

        return 0;
}
