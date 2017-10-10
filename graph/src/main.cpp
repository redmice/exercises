#include <iostream>
#include <vector>
#include <list>
#include "BinaryTree.h"

int main() {

    std::vector<int> data = {50, 20, 60, 10, 15, 70, 5, 15, 65, 80};
    BinTree *input = createMinimalBST_v2(data);

    std::vector<std::list<int>> output = sequences(input);
    std::string outputStr = "";

    for (auto l : output) {
        outputStr += "{";
        for (auto elem : l) {
            outputStr += std::to_string(elem);
            outputStr += ", ";
        }
        outputStr.erase(outputStr.length() - 2);
        outputStr += "}\n";
    }
    std::cout << outputStr ;

    return 0;
}