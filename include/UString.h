#ifndef USTRING_H
#define USTRING_H

#include <string>
#include <cstring>

class UString {
public:
    UString(unsigned char* string, int size);
    UString(int size, unsigned char initial);
    UString(int size);
    UString();

    ~UString();

    unsigned char* data();
    void append(unsigned char* string, int size);
    void append(char* string, int size);
    void append(UString string);
    void append(std::string string);
    void push(unsigned char character);
    void copyAt(std::string string, int index);
    void copyAt(UString string, int index);
    void copyAt(unsigned char* string, int index, int size);
    int size();
    void clear();
    std::string& toString();

    void operator+=(UString string);
    void operator+=(unsigned char character);
    unsigned char& operator[](int index);
    UString& operator=(UString string);
private:
    unsigned char* m_String;
    int m_Size;
    int m_Length;
};

#endif // USTRING_H