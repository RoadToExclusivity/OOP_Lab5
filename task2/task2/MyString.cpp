#include "stdafx.h"
#include "MyString.h"

using namespace std;

void CMyString::AllocNewMemory(size_t size)
{
	m_string = (char*)malloc(size);
	assert(m_string != nullptr);
}

void CMyString::ReallocMemory(size_t newSize)
{
	if (newSize > m_curBufferSize)
	{
		while (newSize > m_curBufferSize)
		{
			m_curBufferSize <<= 1;
		}
		char *newString = (char*)realloc(m_string, m_curBufferSize);
		assert(newString != nullptr);
		m_string = newString;
	}
}

CMyString::iterator::iterator(pointer ptr)
	:ptr_(ptr)
{
}

CMyString::iterator::self_type& CMyString::iterator::operator++()
{
	ptr_++; 
	return *this;
}

CMyString::iterator::self_type CMyString::iterator::operator++(int junk)
{
	self_type i = *this;
	ptr_++; 

	return i;
}

CMyString::iterator::self_type& CMyString::iterator::operator--()
{
	ptr_--;
	return *this;
}

CMyString::iterator::self_type CMyString::iterator::operator--(int junk)
{
	self_type i = *this;
	ptr_--;

	return i;
}

CMyString::iterator::value_type& CMyString::iterator::operator*() const
{ 
	return *ptr_; 
}

CMyString::iterator::value_type* CMyString::iterator::operator->() const
{ 
	return ptr_;
}

bool CMyString::iterator::operator==(const self_type& rhs) const
{ 
	return ptr_ == rhs.ptr_; 
}

bool CMyString::iterator::operator!=(const self_type& rhs) const
{ 
	return ptr_ != rhs.ptr_; 
}

CMyString::const_iterator::const_iterator(pointer ptr)
	:ptr_(ptr)
{
}

CMyString::const_iterator::self_type& CMyString::const_iterator::operator++()
{
	ptr_++;

	return *this;
}

CMyString::const_iterator::self_type CMyString::const_iterator::operator++(int junk)
{
	self_type i = *this;
	ptr_++;
	return i;
}

CMyString::const_iterator::self_type& CMyString::const_iterator::operator--()
{
	ptr_--;
	return *this;
}

CMyString::const_iterator::self_type CMyString::const_iterator::operator--(int junk)
{
	self_type i = *this;
	ptr_--;

	return i;
}

const CMyString::const_iterator::value_type& CMyString::const_iterator::operator*() const
{
	return *ptr_;
}

const CMyString::const_iterator::value_type* CMyString::const_iterator::operator->() const
{
	return ptr_;
}

bool CMyString::const_iterator::operator==(const self_type& rhs) const
{
	return ptr_ == rhs.ptr_;
}

bool CMyString::const_iterator::operator!=(const self_type& rhs) const
{
	return ptr_ != rhs.ptr_;
}

CMyString::CMyString()
	: m_length(0), m_string(nullptr), m_curBufferSize(1)
{
	AllocNewMemory(1);
	m_string[0] = '\0';
}

CMyString::CMyString(const char *pString, unsigned length)
	: m_string(nullptr)
{
	m_length = (length == UINT_MAX) ? strlen(pString) : length;
	m_curBufferSize = m_length + 1;
	AllocNewMemory(m_curBufferSize);
	memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(const string &stlString)
	:m_length(stlString.length()), m_string(nullptr), m_curBufferSize(stlString.length() + 1)
{
	AllocNewMemory(m_curBufferSize);
	memcpy(m_string, stlString.c_str(), m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(const CMyString &other)
	:m_length(other.GetLength()), m_curBufferSize(other.m_curBufferSize)
{
	AllocNewMemory(m_curBufferSize);
	memcpy(m_string, other.m_string, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(CMyString &&other)
	:m_string(other.m_string), m_length(other.m_length), m_curBufferSize(other.m_curBufferSize)
{
	other.m_length = 0;
	other.m_string = nullptr;
	other.m_curBufferSize = 1;
}

CMyString::~CMyString()
{
	if (m_string != nullptr)
	{
		free(m_string);
	}
}

unsigned CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_string;
}

const CMyString CMyString::SubString(unsigned start, unsigned length) const
{
	CMyString zeroString("");
	if (start >= m_length)
	{
		return zeroString;
	}

	if (length < m_length - start)
	{
		char *result = (char*)malloc(length + 1);
		copy(&m_string[start], &m_string[start + length], &result[0]);
		result[length] = '\0';
		
		CMyString subString(result, length);
		free(result);

		return subString;
	}

	return zeroString;
}

void CMyString::Clear()
{
	m_length = 0;
	m_curBufferSize = 1;
	ReallocMemory(1);
	m_string[0] = '\0';
}

CMyString& CMyString::operator = (const CMyString &str)
{
	if (addressof(str) != this)
	{
		CMyString tmpCopy(str);
		swap(m_string, tmpCopy.m_string);
		swap(m_length, tmpCopy.m_length);
		swap(m_curBufferSize, tmpCopy.m_curBufferSize);
	}

	return *this;
}

CMyString& CMyString::operator = (CMyString &&str)
{
	if (addressof(str) != this)
	{
		if (m_string != nullptr)
		{
			free(m_string);
		}
		m_string = str.m_string;
		m_length = str.m_length;
		m_curBufferSize = str.m_curBufferSize;
		
		str.m_string = nullptr;
		str.m_length = 0;
		str.m_curBufferSize = 0;
	}
	return *this;
}

CMyString& CMyString::operator += (const CMyString &str)
{
	ReallocMemory(m_length + str.m_length + 1);
	copy(&str.m_string[0], &str.m_string[str.m_length], &m_string[m_length]);
	m_length += str.m_length;
	m_string[m_length] = '\0';

	return *this;
}

char CMyString::operator[](size_t index) const
{
	assert(index < m_length);
	return m_string[index];
}

char& CMyString::operator[](size_t index)
{
	assert(index < m_length);
	return m_string[index];
}

const CMyString operator+(const CMyString &str1, const CMyString &str2)
{
	CMyString str(str1);
	str += str2;

	return str;
}

bool operator==(const CMyString &str1, const CMyString &str2)
{
	return ((str1.GetLength() == str2.GetLength()) && (memcmp(str1.GetStringData(), str2.GetStringData(), str1.GetLength()) == 0));
}

bool operator!=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 == str2);
}

bool operator<(const CMyString &str1, const CMyString &str2)
{
	int res = memcmp(str1.GetStringData(), str2.GetStringData(), min(str1.GetLength(), str2.GetLength()));
	if (res == 0)
	{
		return str1.GetLength() < str2.GetLength();
	}

	return res < 0;
}

bool operator<=(const CMyString &str1, const CMyString &str2)
{
	return (str1 < str2 || str1 == str2);
}

bool operator>(const CMyString &str1, const CMyString &str2)
{
	return !(str1 <= str2);
}

bool operator>=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 < str2);
}

std::istream& operator>>(std::istream &stream, CMyString &str)
{
	streamoff pos = stream.tellg();

	string inpString;
	if (stream >> inpString)
	{
		str = CMyString(inpString);
		return stream;
	}

	stream.seekg(pos);
	stream.setstate(ios_base::failbit | stream.rdstate());

	return stream;
}

std::ostream& operator<<(std::ostream &stream, const CMyString &str)
{
	/*unsigned len = str.GetLength();
	const char *s = str.GetStringData();
	for (unsigned i = 0; i < len; ++i)
	{
		stream << str.GetStringData();
	}*/
	stream << str.GetStringData();

	return stream;
}

CMyString::iterator CMyString::begin()
{
	return iterator(m_string);
}

CMyString::iterator CMyString::end()
{
	return iterator(m_string + m_length);
}

CMyString::const_iterator CMyString::begin() const
{
	return const_iterator(m_string);
}

CMyString::const_iterator CMyString::end() const
{
	return const_iterator(m_string + m_length);
}

CMyString::const_iterator CMyString::cbegin() const
{
	return const_iterator(m_string);
}

CMyString::const_iterator CMyString::cend() const
{
	return const_iterator(m_string + m_length);
}

CMyString::reverse_iterator CMyString::rbegin()
{
	return reverse_iterator(m_string + m_length);
}

CMyString::reverse_iterator CMyString::rend()
{
	return reverse_iterator(m_string);
}

CMyString::const_reverse_iterator CMyString::rbegin() const
{
	return const_reverse_iterator(m_string + m_length);
}

CMyString::const_reverse_iterator CMyString::rend() const
{
	return const_reverse_iterator(m_string);
}

CMyString::const_reverse_iterator CMyString::crbegin() const
{
	return const_reverse_iterator(m_string + m_length);
}

CMyString::const_reverse_iterator CMyString::crend() const
{
	return const_reverse_iterator(m_string);
}