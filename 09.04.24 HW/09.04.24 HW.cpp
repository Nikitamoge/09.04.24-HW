#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
//
//using namespace std;
//
//class file {
//public:
//    void filep(const string& filename, const string& outputmame) {
//        ifstream inputfile(filename);
//        ofstream outputfile(outputmame);
//        string word;
//
//        while (inputfile >> word) {
//            if (word.size() >= 7) {
//                outputfile << word << ' ';
//            }
//        }
//
//        inputfile.close();
//        outputfile.close();
//    }
//};
//
//
//class filecopy {
//public:
//    void filec(const string& inputnametwo, const string& outputnametwo) {
//        ifstream inputfile(inputnametwo);
//        ofstream outputfile(outputnametwo);
//        string line;
//
//        while (getline(inputfile, line)) {
//            outputfile << line << endl;
//        }
//
//        inputfile.close();
//        outputfile.close();
//    }
//};
//
//int main() {
//    file f;
//    f.filep("file", "file");
//
//    filecopy fc;
//    fc.filec("file", "file2");
//}

class MyString
{
    char* str;
    static int count;
    int field = 69;
public:
    MyString()
    {
        str = new char[field];
        str[0] = '\0';
        count++;
    }
    MyString(const char* text)
    {
        str = new char[strlen(text) + 1];
        strcpy_s(str, strlen(text) + 1, text);
        count++;
    }

    MyString(const MyString& other)
    {
        str = new char[strlen(other.str) + 1];
        strcpy_s(str, strlen(other.str) + 1, other.str);
        count++;
    }

    MyString(MyString&& other)
    {
        str = other.str;
        other.str = nullptr;
        count++;
    }

    MyString& operator=(MyString&& other)
    {
        if (this != &other)
        {
            delete[] str;
            str = other.str;
            other.str = nullptr;
        }
        return *this;
    }

    MyString operator++()
    {
        int overload = strlen(str);
        char* temp = new char[overload + 2];
        strcpy_s(temp, overload + 2, str);
        temp[overload] = 'x';
        temp[overload + 1] = '\0';
        delete[] str;
        str = temp;
        return *this;
    }

    MyString operator--()
    {
        int overload = strlen(str);
        if (overload > 0)
        {
            char* temp = new char[overload];
            strncpy_s(temp, overload, str, overload - 1);
            temp[overload - 1] = '\0';
            delete[] str;
            str = temp;
        }
        return *this;
    }

    MyString operator++(int)
    {
        MyString postfixInc(*this);
        int overload = strlen(str);
        char* temp = new char[overload + 2];
        strcpy_s(temp, overload + 2, str);
        temp[overload] = 'x';
        temp[overload + 1] = '\0';
        delete[] str;
        str = temp;
        return postfixInc;
    }

    MyString operator--(int)
    {
        MyString postfixDic(*this);
        int overload = strlen(str);
        if (overload > 0)
        {
            char* temp = new char[overload];
            strncpy_s(temp, overload, str, overload - 1);
            temp[overload - 1] = '\0';
            delete[] str;
            str = temp;
        }
        return postfixDic;
    }

    friend MyString operator+(int n, const MyString& Str)
    {
        MyString result;
        delete[] result.str;
        result.str = new char[n + strlen(Str.str) + 1];
        for (int i = 0; i < n; ++i)
        {
            result.str[i] = 'x';
        }
        strcpy_s(result.str + n, strlen(Str.str) + 1, Str.str);
        return result;
    }

    MyString operator-(int n) const
    {
        MyString result(*this);
        int overload = strlen(result.str);
        if (n < overload)
        {
            char* temp = new char[overload - n + 1];
            strncpy_s(temp, overload - n + 1, result.str, overload - n);
            temp[overload - n] = '\0';
            delete[] result.str;
            result.str = temp;
        }
        else
        {
            delete[] result.str;
            result.str = new char[1];
            result.str[0] = '\0';
        }
        return result;
    }

    void input()
    {
        char buffer[256];
        cout << "Enter your string: ";
        cin.getline(buffer, 256);
        delete[] str;
        str = new char[strlen(buffer) + 1];
        strcpy_s(str, strlen(buffer) + 1, buffer);
    }


    void output() const
    {
        cout << "String: " << str << endl;
    }


    static int getCount()
    {
        return count;
    }


    ~MyString()
    {
        delete[] str;
        count--;
    }

    friend ostream& operator<<(ostream& os, const MyString& myStr)
    {
        os << "String: " << myStr.str;
        return os;
    }

    friend istream& operator>>(istream& is, MyString& myStr)
    {
        char buffer[256];
        is.getline(buffer, 256);
        delete[] myStr.str;
        myStr.str = new char[strlen(buffer) + 1];
        strcpy_s(myStr.str, strlen(buffer) + 1, buffer);

        return is;
    }
};

int MyString::count = 0;

int main()
{
    MyString str("Hello");
    MyString sum = 10 + str;
    sum.output();
}