#include "UString.h"

UString::UString(unsigned char* string, int size) {
    m_Length = size * 1.5;
    m_String = new unsigned char[m_Length];
    memmove(m_String, string, size);
    m_Size = size;
}

UString::UString(char* string, int size)
{
    m_Length = size * 1.5;
    m_String = new unsigned char[m_Length];
    for (int i = 0; i < size; i++) {
        m_String[i] = static_cast<unsigned char>(string[i]);
    }
    m_Size = size;
}

UString::UString(int size, unsigned char initial) {
    m_Size = size;
    m_Length = size + size / 2;
    m_String = new unsigned char[m_Length] {initial};
}

UString::UString(int size) {
    m_Size = size;
    m_Length = size + size / 2;
    m_String = new unsigned char[size] {0};
}

UString::UString() {
    m_Size = 0;
    m_Length = 1;
    m_String = new unsigned char[1];
}

UString::~UString() {
    printf("UString: Deleting string: %s\n", m_String);
    delete[] m_String;
}

unsigned char* UString::data() {
    return m_String;
}

void UString::append(unsigned char* string, int size) {
    if (size < m_Length) {
        for (int i = 0; i < size; i++) {
            m_String[m_Size + i] = string[i];
            m_Size += size;
            return;
        }
    }
    m_Length = m_Size + size * 1.5;
    unsigned char* temp = new unsigned char[m_Length];
    for (int i = 0; i < m_Size; i++) {
        temp[i] = m_String[i];
    }
    for (int i = 0; i < size; i++) {
        temp[m_Size + i] = string[i];
    }
    delete[] m_String;
    m_String = temp;
    m_Size += size;
}

void UString::append(char* string, int size) {
    if (size < m_Length) {
        for (int i = 0; i < size; i++) {
            m_String[m_Size + i] = static_cast<unsigned char>(string[i]);
            m_Size += size;
            return;
        }
    }
    m_Length = m_Size + size * 1.5;
    unsigned char* temp = new unsigned char[m_Length];
    for (int i = 0; i < m_Size; i++) {
        temp[i] = m_String[i];
    }
    for (int i = 0; i < size; i++) {
        temp[m_Size + i] = static_cast<unsigned char>(string[i]);
    }
    delete[] m_String;
    m_String = temp;
    m_Size += size;
}

void UString::append(UString string) {
    append(string.data(), string.size());
}

void UString::append(std::string string) {
    append(string.data(), string.size());
}

void UString::push(unsigned char character) {
    if (m_Size < m_Length) {
        m_String[m_Size] = character;
        m_Size++;
        return;
    }
    m_Length = m_Size * 1.5;
    unsigned char* temp = new unsigned char[m_Length];
    for (int i = 0; i < m_Size; i++) {
        temp[i] = m_String[i];
    }
    temp[m_Size] = character;
    delete[] m_String;
    m_String = temp;
    m_Size++;
}

void UString::copyAt(unsigned char* string, int index, int size) {
    if (index + size < m_Length) {
        for (int i = 0; i < size; i++) {
            m_String[index + i] = string[i];
        }
        return;
    }
    m_Length = index + size + size / 2;
    unsigned char* temp = new unsigned char[m_Length];
    for (int i = 0; i < m_Size; i++) {
        temp[i] = m_String[i];
    }
    for (int i = 0; i < size; i++) {
        temp[index + i] = string[i];
    }
    delete[] m_String;
    m_String = temp;
    m_Size = index + size;
}

void UString::copyAt(UString string, int index) {
    copyAt(string.data(), index, string.size());
}

void UString::copyAt(std::string string, int index) {
    int size = string.size();
    if (index + size < m_Length) {
        for (int i = 0; i < size; i++) {
            m_String[index + i] = static_cast<unsigned char>(string[i]);
        }
        return;
    }
    m_Length = index + size + size / 2;
    unsigned char* temp = new unsigned char[m_Length];
    for (int i = 0; i < m_Size; i++) {
        temp[i] = m_String[i];
    }
    for (int i = 0; i < size; i++) {
        temp[index + i] = string[i];
    }
    delete[] m_String;
    m_String = temp;
    m_Size = index + size;
}

int UString::size() {
    return m_Size;
}

void UString::clear() {
    delete[] m_String;
    m_Size = 0;
    m_Length = 1;
    m_String = new unsigned char[1];
}

std::string& UString::toString() {
    std::string* result = new std::string();
    for (int i = 0; i < m_Size; i++) {
        result->push_back(static_cast<char>(m_String[i]));
    }
    return *result;
}

void UString::operator+=(UString string) {
    append(string);
}

void UString::operator+=(unsigned char character) {
    push(character);
}

unsigned char& UString::operator[](int index) {
    if (index >= 0 && index < m_Size) {
        return m_String[index];
    }
    return m_String[0];
}

UString& UString::operator=(UString string) {
    clear();
    append(string);
    return *this;
}