#include <iostream>
#include <string>
#include <regex>

bool containOnlyLetters(std::string const&str)
{
    return std::regex_match(str,std::regex("^[A-Za-z]+$"));
}
bool containOnlyDigits(std::string const&str)
{
    return std::regex_match(str,std::regex("^[0-9]+$"));
}
int main()
{
    std::string str{"String"};
   str.data();
    std::string str1{"String1"};
    std::cout<<std::boolalpha << containOnlyLetters(str)<<std::endl;
    std::cout<<std::boolalpha << containOnlyLetters(str1)<<std::endl;
    std::cout<<std::boolalpha << containOnlyDigits("123567")<<std::endl;
    return 0;
}
