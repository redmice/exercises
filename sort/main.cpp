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
 *      2. If (left < right)
 *          2.1 Call mergeSort for first half:
 *              Call mergeSort(arr, l, m)
 *          3.1 Call mergeSort for second half:
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
 * Quick sort -
 * TIme complexity: O(n log(n)) avg. O(n2) worst case.
 * Space complexity Space O(log(n))
 *
 * Sort can be done in place, keeping left and right indexes
 *
 * Pick an element, called a pivot, from the array. (e.g. element in de middle)
 *
 * Partitioning: reorder the array so that:
 *      all elements with values less than the pivot come before the pivot, while
 *      all elements with values greater than the pivot come after it (equal values can go either way).
 * After this partitioning, the pivot is in its final position. This is called the partition operation.
*  Recursively apply the above steps to the sub-array of elements with smaller values and
 * separately to the sub-array of elements with greater values.
 */

void quicksort (std::vector<int> &v);
void quicksort (std::vector<int> &v, int left, int right);
int partition (std::vector<int> &v, int left, int right);


void quicksort (std::vector<int> &v){
    quicksort (v, 0, v.size()-1);
}

void quicksort (std::vector<int> &v, int left, int right){
    int pivotIndex = partition(v, left, right);

    if ((pivotIndex-1) > left) {
        quicksort(v, left, pivotIndex - 1);
    }
    if (pivotIndex < right) {
        quicksort(v, pivotIndex, right);
    }
}

// return final position of the partitioned element
int partition (std::vector<int> &v, int left, int right){
    int pivot = v[(left + right) / 2];  //Element in the middle

    while (left <= right){
        while (v[left] < pivot){
            ++left;
        }
        while (v[right] > pivot) {
            --right;
        }
        if (left <= right){
            std::swap(v[left], v[right]);
            ++left;
            --right;
        }
    }
    return left;
}


int main() {
    int testSize = 800;
    std::vector<int> myVector(testSize);
    std::vector<int> testVector(testSize);
    std::vector<int> vector2 = {4, 6, 1, 8, 3, 2, 5};

    srand (time(NULL));

    for (auto i=0; i<testSize; i++){
        myVector[i] = rand() % 999 + 1;
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
    quicksort(testVector);
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