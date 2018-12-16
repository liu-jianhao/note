// 面试题20：表示数值的字符串
// 题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，
// 字符串“+100”、“5e2”、“-123”、“3.1416”及“-1E-16”都表示数值，但“12e”、
// “1a3.14”、“1.2.3”、“+-5”及“12e+5.4”都不是

class Solution {
public:
    bool isNumeric(char* string)
    {
        if(string == nullptr)
        {
            return false;
        }
        
        bool numeric = scanInteger(&string);
        
        if(*string == '.')
        {
            ++string;
            numeric = scanUnsignedInteger(&string) || numeric;
        }
        if(*string == 'e' || *string == 'E')
        {
            ++string;
            numeric = numeric && scanInteger(&string);
        }
        
        return numeric && *string == '\0';
    }

    bool scanInteger(char** string)
    {
        if(**string == '+' || **string == '-')
        {
            ++(*string);
        }
        return scanUnsignedInteger(string);
    }
    
    bool scanUnsignedInteger(char** string)
    {
        const char* before = *string;
        while(**string != '\0' && **string >= '0' && **string <= '9')
        {
            ++(*string);
        }
        return before < *string;
    }
};