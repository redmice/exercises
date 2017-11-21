#include <iostream>
#include <string>

long equalize(std::string &s1, std::string &s2){

    long len1 = s1.size();
    long len2 = s2.size();

    if (len1 < len2){
        for (auto i=0; i < len2-len1; i++){
            s1 = '0' + s1;
        }
        return len2;
    } else {
        for (auto i=0; i < len1-len2; i++){
            s2 = '-' + s2;
        }
        return len1;
    }
}
    
std::string sumBinary(std::string &s1, std::string &s2) {
    std::string result = "";
    unsigned carry = 0;
    long len;
    unsigned b1;
    unsigned b2;
    
    len = equalize(s1, s2);
    for (auto i=len-1; i>=0; i--){
        b1 = s1[i] - '0';
        b2 = s2[i] -'0';
        unsigned r = carry ^ b1  ^ b2;
        carry = (carry & b1) | (carry & b2) | (b1 & b2);
        result = (char)(r + '0') + result;
    }
    if (carry)
        result = char(carry + '0') + result;
    return result;
}

int main() {
    std::string n1 = "101";
    std::string n2 = "1101";

    std::cout << n1 << " + " << n2 << " = " << sumBinary(n1, n2) << std::endl;
}
