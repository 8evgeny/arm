#include <iostream>
#include <boost/filesystem.hpp>
int main() {
    std::cout << boost::filesystem::current_path() << std::endl;
}
