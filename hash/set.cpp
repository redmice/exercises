#include <iostream>
#include <unordered_set>
#include <string>
#include <list>

int main () {
    std::list<std::string> myList = {"uno", "dos", "tres", "uno", "dos", "red", "red", "yellow"};
    std::unordered_set<std::string> mySet;
    std::pair<std::unordered_set<std::string>::iterator, bool> result;


    std::cout << " --- Before --- " << std::endl;
    for (auto &s : myList){
        std::cout << s << " ";
    }
    std::cout << std::endl;

    for (std::list<std::string>::const_iterator it = myList.begin(); it != myList.end(); ++it){
        result = mySet.insert(*it);
        if (!result.second){
            if ( *(result.first) == *it ){ //check for collisions
                myList.erase(it);
            }
        }
    }

    std::cout << " --- After --- " << std::endl;
    for (auto &s : myList){
        std::cout << s << " ";
    }
    std::cout << std::endl;
    
}
    
