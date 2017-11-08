#include <iostream>
#include <vector>
#include <utility>

void quickSort (std::vector<int>& v);
void quickSort (std::vector<int>& v, int low, int high);
int partition (std::vector<int>& v, int low, int high);

void quickSort (std::vector<int>& v) {
    quickSort (v, 0, v.size()-1);
}

void quickSort (std::vector<int>& v, int low, int high) {
    int p;
    if (low < high) {
        p = partition (v, low, high);
        quickSort (v, low, p-1);
        quickSort (v, p+1, high);
    }
}

int partition (std::vector<int>& v, int low, int high) {
    int firstHigh = low;
    int p = high;
    for (int i=low; i<high; i++){
        if (v[i] < v[p]){
            std::swap(v[i], v[firstHigh++]);
        }
    }
    std::swap(v[firstHigh], v[p]);
    return firstHigh;
}

int main() {
    std::vector<std::vector<int> > testVectors = {{},
                                                 {4, 6, 1, 8, 3, 2, 5},
                                                 {1, 2, 3, 4, 5, 6, 7},
                                                 {7, 6, 5, 4, 3, 2, 1}};
    for (auto& v : testVectors) {
        quickSort(v);
        for (auto i : v) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
