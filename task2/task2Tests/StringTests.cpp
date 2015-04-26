#include "stdafx.h"
#include "../task2/MyString.h"

using namespace std;

struct StringFixture
{
	CMyString defaultString;
};

BOOST_FIXTURE_TEST_SUITE(StringTests, StringFixture)

BOOST_AUTO_TEST_CASE(IsDefaultStringEmpty)
{
	BOOST_CHECK_EQUAL(defaultString.GetStringData(), "");
	BOOST_CHECK_EQUAL(defaultString.GetLength(), 0);
}

BOOST_AUTO_TEST_CASE(SimpleStringInitializeTests)
{
	{
		const char testStr[] = " test ";
		CMyString str(testStr);
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), testStr), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), strlen(testStr));
	}
	{
		string testStr = " test ";
		CMyString str(testStr);
		BOOST_CHECK_EQUAL(str, testStr);
		BOOST_CHECK_EQUAL(str.GetLength(), testStr.length());
	}
	{
		const char testStr[] = " test string ";
		CMyString str(testStr, 5);
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), " test"), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), strlen(" test"));
	}
	{
		CMyString testStr("SOME STRING ");
		CMyString str(testStr);
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), testStr.GetStringData()), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), testStr.GetLength());
	}
	{
		CMyString testStr1("SOME STRING "), testStr2("NEW STRING");
		CMyString str(testStr1 + testStr2);
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), "SOME STRING NEW STRING"), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), testStr1.GetLength() + testStr2.GetLength());
	}
}

BOOST_AUTO_TEST_CASE(StringAssigning)
{
	{
		const char testStr[] = " test ";
		CMyString str("");
		str = testStr;
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), testStr), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), strlen(testStr));
	}
	{
		string testStr = " test ";
		CMyString str("other string");
		str = testStr;
		BOOST_CHECK_EQUAL(str, testStr);
		BOOST_CHECK_EQUAL(str.GetLength(), testStr.length());
	}
	{
		const char testStr[] = " test string ";
		CMyString str("other string" , 5);
		str = testStr;
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), testStr), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), strlen(testStr));
	}
	{
		CMyString testStr("SOME STRING ");
		CMyString str("");
		str = testStr;
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), testStr.GetStringData()), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), testStr.GetLength());
	}
	{
		CMyString testStr1("SOME STRING "), testStr2("NEW TEMP STRING");
		CMyString str("");
		str = testStr1 + testStr2;
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), "SOME STRING NEW TEMP STRING"), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), testStr1.GetLength() + testStr2.GetLength());
	}
}

BOOST_AUTO_TEST_CASE(StringClear)
{
	{
		const char testStr[] = " test ";
		CMyString str(testStr);
		str.Clear();
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), ""), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), 0);
	}
}

BOOST_AUTO_TEST_CASE(SubstringTestWithZeros)
{
	{
		CMyString str("string for substrings  ");
		CMyString sub(str.SubString(0, 6));
		BOOST_CHECK_EQUAL(strcmp(sub.GetStringData(), "string"), 0);
		BOOST_CHECK_EQUAL(sub.GetLength(), strlen("string"));
	}
	{
		CMyString str("string for substrings  ");
		CMyString sub(str.SubString(7, 3));
		BOOST_CHECK_EQUAL(strcmp(sub.GetStringData(), "for"), 0);
		BOOST_CHECK_EQUAL(sub.GetLength(), strlen("for"));
	}
	{
		CMyString str("string for substrings  ");
		CMyString sub = str.SubString(150, 6);
		BOOST_CHECK_EQUAL(strcmp(sub.GetStringData(), ""), 0);
		BOOST_CHECK_EQUAL(sub.GetLength(), 0);
	}
	{
		CMyString str("strin\0g for substrings \0", 24);
		CMyString sub = str.SubString(1, 6);
		BOOST_CHECK_EQUAL(str.GetLength(), 24);
		BOOST_CHECK_EQUAL(memcmp(sub.GetStringData(), "trin\0g", 6), 0);
		BOOST_CHECK_EQUAL(sub.GetLength(), 6);
	}
}

BOOST_AUTO_TEST_CASE(IndexTests)
{
	{
		CMyString str("index");
		BOOST_CHECK_EQUAL(str[1], 'n');
		BOOST_CHECK_EQUAL(str[3], 'e');
	}
	{
		CMyString str("index");
		str[1] = 'e';
		BOOST_CHECK_EQUAL(str[1], 'e');
		str[3] = 'n';
		BOOST_CHECK_EQUAL(str[3], 'n');
	}
}

BOOST_AUTO_TEST_CASE(CompareOperators)
{
	{
		CMyString str1("string"), str2("string ");
		BOOST_CHECK_EQUAL(str1 == str2, false);
		BOOST_CHECK_EQUAL(str1 != str2, true);
		BOOST_CHECK_EQUAL(str1 > str2, false);
		BOOST_CHECK_EQUAL(str1 < str2, true);
		BOOST_CHECK_EQUAL(str1 >= str2, false);
		BOOST_CHECK_EQUAL(str1 <= str2, true);
	}
	{
		CMyString str1("string"), str2("string");
		BOOST_CHECK_EQUAL(str1 == str2, true);
		BOOST_CHECK_EQUAL(str1 != str2, false);
		BOOST_CHECK_EQUAL(str1 > str2, false);
		BOOST_CHECK_EQUAL(str1 < str2, false);
		BOOST_CHECK_EQUAL(str1 >= str2, true);
		BOOST_CHECK_EQUAL(str1 <= str2, true);
	}
	{
		CMyString str1("string"), str2("strina");
		BOOST_CHECK_EQUAL(str1 == str2, false);
		BOOST_CHECK_EQUAL(str1 != str2, true);
		BOOST_CHECK_EQUAL(str1 > str2, true);
		BOOST_CHECK_EQUAL(str1 < str2, false);
		BOOST_CHECK_EQUAL(str1 >= str2, true);
		BOOST_CHECK_EQUAL(str1 <= str2, false);
	}
}

BOOST_AUTO_TEST_CASE(PlusTests)
{
	{
		CMyString str1("string"), str2("2");
		CMyString str(str1 + str2);
		BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), "string2"), 0);
		BOOST_CHECK_EQUAL(str.GetLength(), strlen("string2"));
	}
	{
		CMyString str1("string"), str2("2");
		str1 += str2;
		BOOST_CHECK_EQUAL(strcmp(str1.GetStringData(), "string2"), 0);
		BOOST_CHECK_EQUAL(str1.GetLength(), strlen("string2"));
	}
	{
		CMyString str1("string");
		str1 += "2";
		BOOST_CHECK_EQUAL(strcmp(str1.GetStringData(), "string2"), 0);
		BOOST_CHECK_EQUAL(str1.GetLength(), strlen("string2"));
	}
}

BOOST_AUTO_TEST_SUITE_END()