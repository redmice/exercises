#include <iostream>
#include <vector>


/*
 * Merge sort -
 * Time complexity O(n log(n)) avg. and worst case.
 * Space complexity O(n)
 *
 * Pseudo-code
 *
 * MergeSort(arr[], l,  r)
 * If r > l
 *      1. Find the middle point to divide the array into two halves:
 *              middle m = (l+r)/2
 *      2. Call mergeSort for first half:
 *              Call mergeSort(arr, l, m)
 *      3. Call mergeSort for second half:
 *              Call mergeSort(arr, m+1, r)
 *      4. Merge the two halves sorted in step 2 and 3:
 *              Call merge(arr, l, m, r)
 */

void merge (std::vector<int> &input,  size_t  first,  size_t  middle,  size_t  last);
void mergeSort(std::vector<int> &input, size_t  first, size_t last);
void mergeSort(std::vector<int> &input);

void mergeSort(std::vector<int> &input) {
    mergeSort(input, 0, input.size()-1);
}

void mergeSort(std::vector<int> &input,  size_t  first,  size_t  last) {
    if (first < last) {
        int middle = (first + last) / 2;
        mergeSort (input, first, middle);
        mergeSort (input, middle+1, last);
        merge (input, first, middle, last);
    }
}

void merge (std::vector<int> &input, size_t  first,  size_t  middle,  size_t  last) {
    std::vector<int> helper = input;

//    for (auto i = first; i <= last; i++){	// 1. Create a copy of input
//        helper[i] = input[i];
//    }
    int current = first;  //Current position in the input vector
    int leftIndex = first;
    int rightIndex = middle + 1;

    while ((leftIndex <= middle) && (rightIndex <= last)) {
        if (helper[leftIndex] <= helper[rightIndex]) {
            input[current] = helper[leftIndex];
            leftIndex++;
        } else {
            input[current] = helper[rightIndex];
            rightIndex++;
        }
        current++;
    }

   for (auto i = leftIndex; i <= middle; i++) {
        input[current++] = helper[i];
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
    int testSize = 10;
    std::vector<int> myVector(testSize);
    std::vector<int> testVector(testSize);

    srand (time(NULL));

    for (auto i=0; i<testSize; i++){
        myVector[i] = rand() % 90 + 1;
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