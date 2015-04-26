#pragma once
class CMyString final
{
public:
	CMyString();
	CMyString(const char *pString, unsigned length = UINT_MAX);
	CMyString(const CMyString &other);
	CMyString(CMyString &&other);
	CMyString(const std::string &stlString);

	~CMyString();

	unsigned GetLength() const;
	const char* GetStringData() const;
	const CMyString SubString(unsigned start, unsigned length = UINT_MAX) const;

	void Clear();

	CMyString& operator=(const CMyString &str);
	CMyString& operator=(CMyString &&str);

	CMyString& operator+=(const CMyString &str);
	
	char operator[](size_t index) const;
	char& operator[](size_t index);

private:
	void AllocNewMemory(size_t newSize);
	void ReallocMemory(size_t newSize);
	char* m_string;
	unsigned m_length;
	size_t m_curBufferSize;
};

const CMyString operator+(const CMyString &str1, const CMyString &str2);

bool operator==(const CMyString &str1, const CMyString &str2);
bool operator!=(const CMyString &str1, const CMyString &str2);

bool operator<(const CMyString &str1, const CMyString &str2);
bool operator<=(const CMyString &str1, const CMyString &str2);
bool operator>(const CMyString &str1, const CMyString &str2);
bool operator>=(const CMyString &str1, const CMyString &str2);

std::istream& operator>>(std::istream &stream, CMyString &str);
std::ostream& operator<<(std::ostream &stream, const CMyString &str);