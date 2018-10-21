#include <iostream>
#include <fstream>

void writeln(std::ostream &os, const std::string &str) {
    os << str << std::endl;
}

int main()
{
    std::ofstream outfile("output.txt", std::ios_base::trunc);

    for(int i = 0; i < 1000000; ++i) {
        writeln(outfile, "Hello World");
    }
}