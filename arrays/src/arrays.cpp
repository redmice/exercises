// https://www.interviewcake.com/question/cpp/stock-price

#include <iostream>
#include <vector>

using namespace std;

//Suppose we could access yesterday's stock prices as a vector, where:
//
//The indices are the time in minutes past trade opening time, which was 9:30am local time.
//The values are the price in dollars of Apple stock at that time.
//So if the stock cost $500 at 10:30am, stockPricesYesterday[60] = 500.
//
//Write an efficient function that takes stockPricesYesterday and returns the best profit I could have made from 1 purchase and 1 sale of 1 Apple stock yesterday.
int getMaxProfit (const vector<int>& prices)
{
	size_t len = prices.size();
	if (len < 2) {
		throw invalid_argument("Getting a profit requires at least 2 prices");
	}

    int maxProfit = prices[1] - prices[0];
    int minValue = prices[0];

    for (auto i=1; i < len; i++){
    		int potentialProfit = prices[i] - minValue;
    		maxProfit = max(maxProfit, potentialProfit);
    		minValue = min(minValue, prices[i]);
    }
    return maxProfit;
}

//You have a vector of integers, and for each index you want to find the product of every integer except the integer at that index.
//Write a function getProductsOfAllIntsExceptAtIndex() that takes a vector of integers and returns a vector of the products.
vector<int> getProductsOfAllIntsExceptAtIndex(const vector<int>& inputNumbers){

    size_t len = inputNumbers.size();

	vector<int> products(len);
    switch (len){
        case 0: break;
        case 1: products[0] = 0;
                break;
        default: products[0] = 1;
                 for (auto i = 0; i < inputNumbers.size() - 1; i++) {
                     products[i + 1] = inputNumbers[i] * products[i];
                 }

                 int acc = 1;

                 for (auto i = inputNumbers.size() - 1; i > 0; i--) {
                    acc = acc * inputNumbers[i];
                    products[i - 1] = products[i - 1] * acc;
                 }
                 break;
    }
	return products;
}

//Given a vector of integers, find the highest product you can get from three of the integers.
//The input vectorOfInts will always have at least three integers.

int getHighestProductOfThree (const vector<int>& vectorOfInts) {

    vector<int> maxInts(3);

    for (auto i = 0; i < 3; i++) {
        maxInts[i] = vectorOfInts[i];
    }
    for (auto i = 3; i < vectorOfInts.size(); i++) {
        int newPotentialMax = vectorOfInts[i];
        for (auto j = 0; j < 3; j++){
            if (maxInts[j] < newPotentialMax) {
                int tmp = maxInts[j];
                maxInts[j] = newPotentialMax;
                newPotentialMax = tmp;
            }
        }
        int result = 1;
        for (auto i = 0; i < 3; i++) {
            result = result * maxInts[i];
        }
        return result;
    }
}

bool isUnique (string  str) {
    int alphabetSize = 256;
    if (str.length() > alphabetSize) {
        return true;
    }

    vector<bool> charset(alphabetSize);

    for (char c : str) {
        if (charset[c] == true) {
            return false;
        }
        else {
            charset[c] = true;
        }
    }
    return true;
}

bool isPermutation (string str1, string str2) {

    if (str1.length() != str2.length()) {
        return false;
    }
    sort (str1.begin(), str1.end());
    sort (str2.begin(), str2.end());


    return str1.compare(str2);
}

string URLfy (string str, int trueSize) {
    int numSpaces = 0;
    for (auto i = 0; i < trueSize; i++){
        if (str[i] == ' ') {
            ++numSpaces;
        }
    }
    int newSize = trueSize + numSpaces * 2;

//    if (str.length() > trueSize)
//        str[trueSize] = 0;

    int index = newSize-1;
    for ( auto i=trueSize-1; i>=0; i--) {
        if (str[i] == ' ') {
            str[index] = '0';
            str[index-1] = '2';
            str[index-2] = '%';
            index = index - 3;
        }
        else {
            str[index] = str[i];
            --index;
        }
    }
    return str;
}

int getIndex(char);
bool maxOneOdd(vector<bool> const&);

bool isPermutationOfPalindrome (string const& str) {
    int alphabetSize = 26;
    vector<bool> flags(alphabetSize);
    for (char c : str) {
        if (c != ' ') {
            int index = getIndex(c);
            flags[index] = flags[index] ? false : true;
        }
    }
    return maxOneOdd(flags);
}

int getIndex(char c) {
    return tolower(c) - 'a';
}

bool maxOneOdd(vector<bool> const& flags) {
    int count = 0;
    for (bool b : flags) {
        if (b)
            count++;
    }
    return (count<2)?true:false;
}

bool rotateMatrix (std::vector<vector<int32_t>> &matrix) {

    int n = matrix.size();
    if ((n == 0) || (n != matrix[0].size())) {
        return false;
    }
    int numLayers = n / 2;
    for (int layer=0; layer<numLayers; layer++) {
        int first = layer;
        int last = n - layer - 1;
        for (int j=first; j<last; j++) {
            int offset = j - first;
            int temp = matrix[first][j];
            matrix[first][j] = matrix[last-offset][first];   // left to top
            matrix[last-offset][first] = matrix[last][last-offset]; //bottom to left
            matrix[last][last-offset] = matrix[first+offset][last]; //right to bottom
            matrix[first+offset][last] = temp;   //top to right
        }
    }
    return true;
}
void fillWithZeroes (std::vector<vector<int>> & matrix) {
    struct coordinates {
        int x;
        int y;
        coordinates(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}
    };

    vector <coordinates> coordinateList;
    int width = matrix[0].size();
    int height = matrix[0].size();
    for (auto i=0; i<height; i++){
        for (auto j=0; j<width; j++){
            if (matrix[i][j] == 0){
                coordinateList.push_back(coordinates(i, j));
            }
        }
    }
    for (auto c : coordinateList){
        for (auto i = 0; i<width; i++){
            matrix[c.x][i] = 0;
        }
        for (auto i = 0; i<height; i++){
            matrix[i][c.y] = 0;
        }
    }
}




int main ()
{


    vector<vector<int32_t>> matrixZero = {{1, 2, 3, 4, 5}, {1, 2, 0, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    cout << " ==== fillWithZeroes === " << "\n";
    fillWithZeroes(matrixZero);
    for (auto i=0; i<matrixZero.size(); i++) {
        for (auto j=0; j<matrixZero.size(); j++){
            cout << matrixZero[i][j] << ", ";
        }
        cout << "\n";
    }
    cout << "\n";

    vector<vector<int32_t>> matrix = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    cout << " ==== rotateMatrix === " << "\n";
    cout << rotateMatrix(matrix) << "\n";
    for (auto i=0; i<matrix.size(); i++) {
        for (auto j=0; j<matrix.size(); j++){
            cout << matrix[i][j] << ", ";
        }
        cout << "\n";
    }
    cout << "\n";
    cout << " ==== isPermutationOfPalindrome === " << "\n";
    cout << isPermutationOfPalindrome("Tadsct coa") << "\n";

    cout << " ==== URLfy === " << "\n";
    cout << URLfy("My nombre es javier                ", 19) << "\n";

    vector<int> n1 = {10, 7, 5, 8, 11, 9, 20}; // Expected 15
	vector<int> n2 = {10, 7, 5, 3, 1};		  // Expected -2
	vector<int> n3 = {0, 0};						  // Expected exception

    cout << " ==== Maximize profit === " << "\n";
    cout << getMaxProfit (n1) << "\n";
    cout << getMaxProfit (n2) << "\n";
    cout << getMaxProfit (n3) << "\n";

    cout << " ==== Products of all inst except at index === " << "\n";
	vector <int> p1 = {1, 7, 3, 4}; // Expected [84, 12, 28, 21]]
    vector <int> p2 = {7}; // Expected [0]
    vector <int> p3 = {};
    vector <int> p4 = {0, 4, 2, 3};

	vector <int> output = getProductsOfAllIntsExceptAtIndex(p4);
	cout << "[";
	for (auto i = 0; i < output.size(); i++) {
		cout << output[i];
		if (i < output.size() -1) {
			cout << ", ";
		}
	}
    cout << "]" << "\n";

    cout << " ==== Max product of three === " << "\n";
    vector <int> mp1 = {1, 7, 3, 4}; // Expected 84
    vector <int> mp2 = {1, 7, 0, 4}; // Expected 28
    vector <int> mp3 = {-10,-10,1,3,2}; // Expected 300
    cout << getHighestProductOfThree(mp3) << "\n";

    cout << " ==== isUnique === " << "\n";
    cout << isUnique("esta cadena no es unica") << "\n";
    cout << isUnique("abcdefghijklmno") << "\n";

    cout << " ==== isPermutation === " << "\n";
    cout << isPermutation("esta", "tase") << "\n";
    cout << isPermutation("abcdefghijklmno", "abcdefghidklmno") << "\n";

    return 0;
}


/*
 * A greedy algorithm iterates through the problem space taking the optimal solution "so far," until it reaches the end.
 * The greedy approach is only optimal if the problem has "optimal substructure," which means stitching together optimal solutions to subproblems yields an optimal solution.
 *
 * "Suppose we could come up with the answer in one pass through the input, by simply updating the 'best answer so far' as we went. What additional values would we need to keep
 * updated as we looked at each item in our set, in order to be able to update the 'best answer so far' in constant time?"
 */
