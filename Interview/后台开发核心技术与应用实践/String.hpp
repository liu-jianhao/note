#include <cstring>
#include <cstdio>

class String
{
  public:
    String(const char *str = nullptr);
    String(const String &other);
    ~String();
    String &operator=(const String &other);
    String operator+(const String &other);
    bool operator==(const String &other);
    int size();
    void print();

  private:
    char *m_data;
};

String::String(const char *str)
{
    if (str == nullptr)
    {
        m_data = new char[1];
        m_data[0] = '\0';
    }
    else
    {
        int length = strlen(str);
        m_data = new char[length+1];
        strcpy(m_data, str);
    }
}

String::~String()
{
    if(m_data)
    {
        delete[] m_data;
        m_data = nullptr;
    }
}

String::String(const String &other)
{
    if(other.m_data == nullptr)
    {
        m_data = nullptr;
    }
    else
    {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }
}


String& String::operator=(const String &other)
{
    if(this != &other)
    {
        delete[] m_data;
        if(other.m_data == nullptr)
        {
            m_data = nullptr;
        }
        else
        {
            m_data = new char[strlen(other.m_data) + 1];
            strcpy(m_data, other.m_data);
        }
    }
    return *this;
}

String String::operator+(const String &other)
{
    String newString;
    if(other.m_data == nullptr)
    {
        newString = *this;
    }
    else if(m_data == nullptr)
    {
        newString = other;
    }
    else
    {
        newString.m_data = new char[strlen(m_data) + strlen(other.m_data) + 1];
        strcpy(newString.m_data, m_data);
        strcat(newString.m_data, other.m_data);
    }
    return newString;
}

bool String::operator==(const String &other)
{
    if(strlen(m_data) != strlen(other.m_data))
    {
        return false;
    }
    else
    {
        return strcmp(m_data, other.m_data) ? false : true;
    }
}

int String::size()
{
    return strlen(m_data);
}

void String::print()
{
    printf("%s", m_data);
}