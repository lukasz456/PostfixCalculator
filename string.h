#pragma once
#include <iostream>

namespace stos
{
	class string
	{
	public:
		// Constructors
		string();
		string(const char* str);
		string(const char* str, size_t length);
		string(const string& str);

		// Operators
		string& operator=(const string& str);
		string operator+(const string& str) const;
		bool operator==(const string& str) const;
		bool operator!=(const string& str) const;
		string& operator+=(const string& str);
		const char& operator[](int index) const;

		// Destructor
		~string();

		// Friend functions
		friend std::istream& getline(std::istream& is, string& str);
		friend std::ostream& operator<<(std::ostream& os, const string& str);

		// Functions
		size_t size() const;
		const char* c_str() const; // return buffer
		string substr(size_t start, size_t size) const;

	private:
		char* m_buffer;
		size_t m_size;
	};

	string to_string(int value);
	int stoi(const string& str);

}
