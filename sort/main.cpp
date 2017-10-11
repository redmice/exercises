#include <iostream>
#include <vector>


/*
 * Merge sort - O(n log(n)) avg. and worst case. Space O(n)
 */

void merge (std::vector<int> &input, std::vector<int> &helper,  size_t  first,  size_t  middle,  size_t  last);
void mergeSort(std::vector<int> &input, std::vector<int> &helper,  size_t  first, size_t last);
void mergeSort(std::vector<int> &input);

void mergeSort(std::vector<int> &input) {
    std::vector <int> helper(input.size());
    mergeSort(input, helper, 0, input.size()-1);
}

void mergeSort(std::vector<int> &input, std::vector<int> &helper,  size_t  first,  size_t  last) {
    if (first < last) {
        int middle = (first + last) / 2;
        mergeSort (input, helper, first, middle);
        mergeSort (input, helper, middle+1, last);
        merge (input, helper, first, middle, last);
    }
}

void merge (std::vector<int> &input, std::vector<int> &helper,  size_t  first,  size_t  middle,  size_t  last) {
    for (auto i = first; i <= last; i++){	// 1. Create a copy of input
        helper[i] = input[i];
    }
    int current = first;  //Current position in the input vector
    int leftIndex = first;
    int rightIndex = middle+1;

    while ((leftIndex <= middle) && (rightIndex <= last)){
        if (helper[leftIndex] <= helper[rightIndex]){
            input[current] = helper[leftIndex];
            leftIndex++;
        }
        else {
            input[current] = helper[rightIndex];
            rightIndex++;
        }
        current++;
    }
    int remainingLeft = middle - leftIndex;
    for (auto i=0; i <= remainingLeft; i++){
        input[current+i] = helper[leftIndex+i];
    }
}

/*
 * Quick sort -  O(n log(n)) avg. O(n2) worst case. Space O(log(n))
 */

void quickSort(std::vector<int> &input, int left, int right);
int partition (std::vector<int> &input, int left, int right);

void quickSort(std::vector<int> &input, int left, int right){
    if (left < right) {
        int index = partition(input, left, right);
        quickSort(input, left, index - 1);
        quickSort(input, index + 1, right);
    }
}

int partition (std::vector<int> &input, int left, int right){
    int pivot = input[(right + left) /2];
    while (left <= right) {
        while ((left <= right) && (input[left] < pivot))
            left++;
        while ((left <= right) &&( input[right] > pivot))
            right--;
        if (left <= right) {
            int tmp = input[left];
            input[left] = input[right];
            input[right] = tmp;
            left++;
            right--;
        }
    }
    return left;
}


int main() {
    int testSize = 50000;
    std::vector<int> myVector(testSize);// = {8,3,5,6,4,32,6,8,6,45,5,6,65};
    std::vector<int> testVector(testSize);

    srand (time(NULL));

    for (auto i=0; i<testSize; i++){
        myVector[i] = rand() % 1000 + 1;
    }

    // Copy over test vector
    testVector = myVector;

    std::cout << "Size: " << testVector.size() << "\n";

    std::cout << "=-=-=-=-= Merge sort =-=-=-=-=\n";
    mergeSort(testVector);
    for (auto i=0; i<testVector.size();i++){
        std::cout << testVector[i] << " ";
    }
    std::cout << "\n";

    // Copy over test vector
    testVector = myVector;

    std::cout << "=-=-=-=-= Quick sort =-=-=-=-=\n";
    quickSort(testVector, 0, testVector.size()-1);
    for (auto i=0; i<testVector.size();i++){
        std::cout << testVector[i] << " ";
    }
    std::cout << "\n";

    // Copy over test vector
    testVector = myVector;

    std::cout << "=-=-=-=-= std sort =-=-=-=-=\n";
    std::sort(testVector.begin(), testVector.end());
    for (auto i=0; i<testVector.size();i++){
        std::cout << testVector[i] << " ";
    }
    std::cout << "\n";

    return 0;
}