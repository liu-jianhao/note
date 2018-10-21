#include <string>

int main()
{
    const char *names[] = { "bob", "fred" };
    std::string last_arg = names[3];
    return last_arg.size();
}