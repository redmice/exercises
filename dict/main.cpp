#include <iostream>
#include <unordered_map>
#include <sstream>

std::unordered_map<std::string, int> createDict(std::string & book) {
    std::transform(book.begin(), book.end(), book.begin(), [](unsigned char c){ return std::tolower(c);});
    std::istringstream sbook(book);
    std::unordered_map<std::string, int> dict;
    while (!sbook.eof()) {
        std::string word;
        std::getline(sbook, word, ' ');
        dict[word] += 1;
    }
    return dict;
}

int getFreq (std::unordered_map<std::string, int> dict, std::string word) {
    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c);});
    std::unordered_map<std::string, int>::const_iterator index = dict.find(word);
    if (index == dict.end())
        return 0;
    else
        return index->second;
}

int main() {
    std::string book = "El perro de san roque no Tiene rabo porque el rabo que tiene es peque";

    std::unordered_map<std::string, int> dict = createDict(book);
    std::cout << "Frequencia de rabo = " << getFreq(dict, "rabo") << std::endl;
    return 0;
}