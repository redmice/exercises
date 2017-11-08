#include <iostream>
#include <vector>
#include <queue>

void mergeSort (std::vector<int>& v);
void mergeSort (std::vector<int>& v, int low, int high);
void merge (std::vector<int>& v, int low, int middle, int high);

void mergeSort (std::vector<int>& v) {
    mergeSort (v, 0, v.size()-1);
}

void mergeSort (std::vector<int>& v, int low, int high) {
    if (low < high) {
        int middle = (low + high) / 2;
        mergeSort (v, low, middle);
        mergeSort (v, middle+1, high);
        merge (v, low, middle, high);
    }
}

void merge (std::vector<int>& v, int low, int middle, int high) {
    std::queue<int> leftQ;
    std::queue<int> rightQ;
    for (int i=low; i<=middle; i++){
        leftQ.push(v[i]);
    }
    for (int i=middle+1; i<=high; i++){
        rightQ.push(v[i]);
    }
    int index = low;
    while ((!leftQ.empty()) && (!rightQ.empty())){
        if (leftQ.front() <= rightQ.front()) {
            v[index++] = leftQ.front();
            leftQ.pop();
        }
        else {
            v[index++] = rightQ.front();
            rightQ.pop();
        }
    }
    while (!leftQ.empty()) {
        v[index++] = leftQ.front();
        leftQ.pop();
    }
}

int main() {
    std::vector<std::vector<int> > testVectors = {{},
                                                 {4, 6, 1, 8, 3, 2, 5},
                                                 {1, 2, 3, 4, 5, 6, 7},
                                                 {7, 6, 5, 4, 3, 2, 1}};
    for (auto& v : testVectors) {
        mergeSort(v);
        for (auto i : v) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
