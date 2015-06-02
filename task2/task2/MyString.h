#pragma once
class CMyString final
{
public:
	class iterator
	{
	public:
		typedef iterator self_type;
		typedef char value_type;
		typedef char& reference;
		typedef char* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		iterator(pointer ptr);
		self_type& operator++();
		self_type operator++(int junk);
		self_type& operator--();
		self_type operator--(int junk);
		self_type operator+(size_t num);
		friend self_type operator+(size_t num, const self_type &it);
		reference operator*() const;
		pointer operator->() const;
		difference_type operator-(self_type it) const;
		reference operator[](size_t index) const;
		bool operator==(const self_type& rhs) const;
		bool operator!=(const self_type& rhs) const;
	private:
		pointer ptr_;
	};

	class const_iterator
	{
	public:
		typedef const_iterator self_type;
		typedef char value_type;
		typedef const char& reference;
		typedef const char* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;

		const_iterator(pointer ptr);
		self_type& operator++();
		self_type operator++(int junk);
		self_type& operator--();
		self_type operator--(int junk);
		self_type operator+(size_t num);
		friend self_type operator+(size_t num, const self_type &it);
		reference operator*() const;
		pointer operator->() const;
		difference_type operator-(self_type it) const;
		reference operator[](size_t index) const;
		bool operator==(const self_type& rhs) const;
		bool operator!=(const self_type& rhs) const;
	private:
		pointer ptr_;
	};

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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

	iterator begin();
	iterator end();
	
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
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