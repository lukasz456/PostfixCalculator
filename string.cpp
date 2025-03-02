#include <cstring>
#include "string.h"

namespace stos
{
    string::string() : m_size(0), m_buffer(nullptr) {
    }

    string::string(const char* str) : m_size(0) {
        m_size = strlen(str);
        m_buffer = new char[m_size + 1]; // create a new buffer
        memcpy(m_buffer, str, m_size); //destination, source, size 
        m_buffer[m_size] = '\0';
    }

    string::string(const char* str, size_t length) {
        m_size = length;
        m_buffer = new char[m_size + 1]; // +1 for the null terminator
        memcpy(m_buffer, str, m_size);
        m_buffer[m_size] = '\0'; // Null-terminate the string
    }

    string::string(const string& str)
    {
        m_size = str.m_size;
        m_buffer = new char[m_size + 1]; // create a new buffer
        memcpy(m_buffer, str.m_buffer, m_size); //destination, source, size 
        m_buffer[m_size] = '\0';
    }

    string::~string() {
        if (m_buffer)
        {
            delete[] m_buffer;
        }
    }

    string& string::operator=(const string& str) {
        if (this != &str) {
            delete[] m_buffer; // delete old buffer
            m_size = str.m_size;
            m_buffer = new char[m_size + 1]; // +1 for the null terminator
            memcpy(m_buffer, str.m_buffer, m_size);
            m_buffer[m_size] = '\0'; // Null-terminate the string
        }
        return *this;
    }

    string string::operator+(const string& str) const {
        string result;
        result.m_size = m_size + str.m_size;
        result.m_buffer = new char[result.m_size + 1];
        memcpy(result.m_buffer, m_buffer, m_size);
        memcpy(result.m_buffer + m_size, str.m_buffer, str.m_size);
        result.m_buffer[result.m_size] = '\0'; // Null-terminate the string
        return result;
    }

    bool string::operator==(const string& str) const {
        if (m_size != str.m_size) return false;
        return strcmp(m_buffer, str.m_buffer) == 0;
    }

    bool string::operator!=(const string& otherStr) const {
        return !(*this == otherStr);
    }

    std::ostream& operator<<(std::ostream& os, const string& s) {
        return os << s.m_buffer;
    }

    const char& string::operator[](int index) const {
        return m_buffer[index];
    }

    string& string::operator+=(const string& other) {
        char* newBuffer = new char[m_size + other.m_size + 1];

        // Copy first string
        std::memcpy(newBuffer, m_buffer, m_size);

        // Copy second string
        std::memcpy(newBuffer + m_size, other.m_buffer, other.m_size);

        // Null-terminate the new string
        newBuffer[m_size + other.m_size] = '\0';

        // Delete old buffer and update pointer and length
        delete[] m_buffer;
        m_buffer = newBuffer;
        m_size += other.m_size;

        return *this;
    }

    std::istream& getline(std::istream& is, string& str) {
        int bufferSize = 4096; // Initial buffer size
        char ch;
        int size = 0;
        char* buffer = new char[bufferSize]; // Allocate initial buffer

        while (is.get(ch) && ch != '\n') {
            // If buffer is full, resize it
            if (size >= bufferSize - 1) {
                char* newBuffer = new char[2 * bufferSize]; // Double the buffer size
                std::memcpy(newBuffer, buffer, size); // Copy existing content
                delete[] buffer; // Free the old buffer
                buffer = newBuffer;
                bufferSize *= 2; // Update buffer size
            }

            buffer[size++] = ch; // Add the new character
        }

        buffer[size] = '\0'; // Null-terminate the string
        str.m_buffer = buffer; // Assign buffer directly to string object
        str.m_size = size; // Assign the result to the stos_string object

        return is;
    }

    size_t string::size() const {
        return m_size;
    }

    const char* string::c_str() const {
        return m_buffer;
    }

    string string::substr(size_t start, size_t size) const {
        // Ensure start index is within bounds
        if (start < 0 || start >= m_size) {
            std::cerr << "Invalid start index.\n";
            return string("");
        }

        // Calculate the actual number of characters to copy
        size_t actualSize = (size < (m_size - start)) ? size : (m_size - start);

        // Create a new string object to store the substring
        char* substr_m_buffer = new char[actualSize + 1];
        for (int i = 0; i < actualSize; ++i) {
            substr_m_buffer[i] = m_buffer[start + i];
        }
        substr_m_buffer[actualSize] = '\0'; // Null-terminate the string

        return string(substr_m_buffer);
    }

    //-------------------------------------------------------------------------

    string to_string(int value) {
        // Maximum number of digits an int can have is 10 (for INT_MAX)
        const int maxDigits = 15;
        char temp[maxDigits + 1]; // +1 for null terminator
        std::snprintf(temp, maxDigits + 1, "%d", value); // Convert integer to string
        return string(temp);
    }

    int stoi(const string& str) {
        return std::strtol(str.c_str(), nullptr, 10);
    }
}
