#include <iostream>
#include <vector>
#include <string>

std::vector<char> strIntersect(std::string const&s1, std::string const&s2);

std::vector<char> strIntersect(std::string const&s1, std::string const&s2){
    std::vector<bool> presents(256, false);  //Assuming ASCII
    std::vector<char> intersection;

    for (auto c : s1) {
        presents[c] = true;
    }
    for (auto c : s2) {
        if (presents[c]){
            intersection.push_back(c);
            presents[c] = false;
        }
    }
    return intersection;
}


int main() {
    std::vector<char> result; 
    std::string s1 = "El perro de San Roque no tiene rabo, porque Ramon Rodriguez se lo ha cortado";
    std::string s2 = "Saint Roque's dog has no tail, because Ramon Rodriguez chopped it off";

    //Expected: "S a i n t   R o q u e s d g h l , b c m r z p"

    result = strIntersect(s1, s2);
    for (auto c : result) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}
