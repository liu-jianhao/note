// 面试题48：最长不含重复字符的子字符串
// 题目：请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子
// 字符串的长度。假设字符串中只包含从'a'到'z'的字符。

#include <string>
#include <iostream>
#include <vector>

// 方法一：蛮力法
bool hasDuplication(const std::string& str);

int longestSubstringWithoutDuplication_1(const std::string& str)
{
    if(str.empty())
    {
        return 0;
    }

    int longest = 0;
    for(unsigned int start = 0; start < str.size(); ++start)
    {
        for(unsigned int end = start; end < str.size(); ++end)
        {
            int count = end - start + 1;
            const std::string substring = str.substr(start, count);

            if(!hasDuplication(substring))
            {
                if(count > longest)
                {
                    longest = count;
                }
                
            }
            else
            {
                break;
            }
        }
    }

    return longest;
}

bool hasDuplication(const std::string& str)
{
    std::vector<int> position(26, -1);

    for(char s : str)
    {
        if(position[s-'a'] >= 0)
        {
            return true;
        }

        position[s-'a'] = s-'a';
    }

    return false;
}

// 方法一：动态规划
int longestSubstringWithoutDuplication_2(const std::string& str)
{
    if(str.empty())
    {
        return 0;
    }

    std::vector<int> position(26, -1);
    int currentLength = 0;
    int longest = 0;

    for(unsigned int i = 0; i < str.size(); ++i)
    {
        int prevIndex = position[str[i]-'a'];
        if(prevIndex < 0 || i - prevIndex > currentLength)
        {
            ++currentLength;
        }
        else
        {
            currentLength = i - prevIndex;
        }

        if(currentLength > longest)
        {
            longest = currentLength;
        }

        position[str[i]-'a'] = i;
    }

    return longest;
}

// ====================测试代码====================
void testSolution1(const std::string& input, int expected)
{
    int output = longestSubstringWithoutDuplication_1(input);
    if(output == expected)
        std::cout << "Solution 1 passed, with input: " << input << std::endl;
    else
        std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}

void testSolution2(const std::string& input, int expected)
{
    int output = longestSubstringWithoutDuplication_2(input);
    if(output == expected)
        std::cout << "Solution 2 passed, with input: " << input << std::endl;
    else
        std::cout << "Solution 2 FAILED, with input: " << input << std::endl;
}

void test(const std::string& input, int expected)
{
    testSolution1(input, expected);
    testSolution2(input, expected);
}

void test1()
{
    const std::string input = "abcacfrar";
    int expected = 4;
    test(input, expected);
}

void test2()
{
    const std::string input = "acfrarabc";
    int expected = 4;
    test(input, expected);
}

void test3()
{
    const std::string input = "arabcacfr";
    int expected = 4;
    test(input, expected);
}

void test4()
{
    const std::string input = "aaaa";
    int expected = 1;
    test(input, expected);
}

void test5()
{
    const std::string input = "abcdefg";
    int expected = 7;
    test(input, expected);
}

void test6()
{
    const std::string input = "aaabbbccc";
    int expected = 2;
    test(input, expected);
}

void test7()
{
    const std::string input = "abcdcba";
    int expected = 4;
    test(input, expected);
}

void test8()
{
    const std::string input = "abcdaef";
    int expected = 6;
    test(input, expected);
}

void test9()
{
    const std::string input = "a";
    int expected = 1;
    test(input, expected);
}

void test10()
{
    const std::string input = "";
    int expected = 0;
    test(input, expected);
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();

    return 0;
}