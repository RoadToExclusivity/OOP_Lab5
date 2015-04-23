#include "stdafx.h"
#include "../task1/Complex.h"

using namespace std;

const double EPS = 1e-10;

struct ComplexFixture
{
	CComplex defaultComplex;
};

BOOST_FIXTURE_TEST_SUITE(ComplexTest, ComplexFixture)

BOOST_AUTO_TEST_CASE(IsEqualToZeroByDefault)
{
	BOOST_CHECK_EQUAL(defaultComplex.Re(), 0);
	BOOST_CHECK_EQUAL(defaultComplex.Im(), 0);
}

BOOST_AUTO_TEST_CASE(CanBeConstructedFromDoubles)
{
	{
		const CComplex complex(3.4);
		BOOST_CHECK_CLOSE(complex.Re(), 3.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 0, EPS);
	}
	{
		const CComplex complex(1.2, 7.6);
		BOOST_CHECK_CLOSE(complex.Re(), 1.2, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 7.6, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestMagnitude)
{
	{
		const CComplex complex(3, 4);
		BOOST_CHECK_CLOSE(complex.GetMagnitude(), 5, EPS);
	}
	{
		const CComplex complex(1.2, -7.6);
		BOOST_CHECK_CLOSE(complex.GetMagnitude(), sqrt(1.2 * 1.2 + 7.6 * 7.6), EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestArgument)
{
	{
		const CComplex complex(3, 4);
		BOOST_CHECK_CLOSE(complex.GetArgument(), atan2(4.0, 3.0), EPS);
	}
	{
		const CComplex complex(2, 0);
		BOOST_CHECK_CLOSE(complex.GetArgument(), 0, EPS);
	}
	{
		const CComplex complex(0, 0);
		BOOST_CHECK_CLOSE(complex.GetArgument(), 0, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestBinaryPlus)
{
	{
		const CComplex complex1(2, 5), complex2(2.4, 5.2);
		const CComplex complex = complex1 + complex2;
		BOOST_CHECK_CLOSE(complex.Re(), 4.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 10.2, EPS);
	}
	{
		const CComplex complex1(2, 5);
		const CComplex complex = complex1 + 3;
		BOOST_CHECK_CLOSE(complex.Re(), 5, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5, EPS);
	}
	{
		const CComplex complex1(2, 5);
		const CComplex complex = 3.4 + complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 5.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestUnaryPlus)
{
	{
		const CComplex complex1(2, 5);
		const CComplex complex = +complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 2, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5, EPS);
	}
	{
		const CComplex complex1(2.4, 5.2);
		const CComplex complex = complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 2.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5.2, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestAssigningPlus)
{
	{
		CComplex complex(2, 5);
		const CComplex complex1(2.4, 5.2);
		complex += complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 4.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 10.2, EPS);
	}
	{
		CComplex complex(2, 5);
		complex += 3;
		BOOST_CHECK_CLOSE(complex.Re(), 5, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestBinaryMinus)
{
	{
		const CComplex complex1(2, 5), complex2(2.4, 5.2);
		const CComplex complex = complex1 - complex2;
		BOOST_CHECK_CLOSE(complex.Re(), -0.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -0.2, EPS);
	}
	{
		const CComplex complex1(2, 5);
		const CComplex complex = complex1 - 3;
		BOOST_CHECK_CLOSE(complex.Re(), -1, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5, EPS);
	}
	{
		const CComplex complex1(2, 5);
		const CComplex complex = 3.4 - complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 1.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -5, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestUnaryMinus)
{
	{
		const CComplex complex1(2, 5);
		const CComplex complex = -complex1;
		BOOST_CHECK_CLOSE(complex.Re(), -2, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -5, EPS);
	}
	{
		const CComplex complex1(2.4, -5.2);
		const CComplex complex = -complex1;
		BOOST_CHECK_CLOSE(complex.Re(), -2.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5.2, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestAssigningMinus)
{
	{
		CComplex complex(2, 5);
		const CComplex complex1(2.4, 5.2);
		complex -= complex1;
		BOOST_CHECK_CLOSE(complex.Re(), -0.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -0.2, EPS);
	}
	{
		CComplex complex(2, 5);
		complex -= 2.3;
		BOOST_CHECK_CLOSE(complex.Re(), -0.3, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 5, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestMultiply)
{
	{
		const CComplex complex1(1, 2), complex2(2, 3);
		const CComplex complex = complex1 * complex2;
		BOOST_CHECK_CLOSE(complex.Re(), -4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 7, EPS);
	}
	{
		const CComplex complex1(1.8, -2.3);
		const CComplex complex = complex1 * 3;
		BOOST_CHECK_CLOSE(complex.Re(), 5.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -6.9, EPS);
	}
	{
		const CComplex complex1(1.8, -2.3);
		const CComplex complex = 3.4 * complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 6.12, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -7.82, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestAssigningMultiply)
{
	{
		CComplex complex(1, 2);
		const CComplex complex1(2, 3);
		complex *= complex1;
		BOOST_CHECK_CLOSE(complex.Re(), -4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 7, EPS);
	}
	{
		CComplex complex(1.8, -2.3);
		complex *= 3;
		BOOST_CHECK_CLOSE(complex.Re(), 5.4, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -6.9, EPS);
	}
	{
		CComplex complex(3, -4);
		complex *= complex;
		BOOST_CHECK_CLOSE(complex.Re(), -7, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -24, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestDivision)
{
	{
		const CComplex complex1(1, 2), complex2(2, 3);
		const CComplex complex = complex1 / complex2;
		BOOST_CHECK_CLOSE(complex.Re(), 8.0 / 13, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 1.0/ 13, EPS);
	}
	{
		const CComplex complex1(1.8, -2.3);
		const CComplex complex = complex1 / 3;
		BOOST_CHECK_CLOSE(complex.Re(), 0.6, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -23.0 / 30, EPS);
	}
	{
		const CComplex complex1(1.8, -2.3);
		const CComplex complex = 3.4 / complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 612.0 / 853, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 782.0 / 853, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestAssigningDivision)
{
	{
		CComplex complex(1, 2);
		const CComplex complex1(2, 3);
		complex /= complex1;
		BOOST_CHECK_CLOSE(complex.Re(), 8.0 / 13, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 1.0 / 13, EPS);
	}
	{
		CComplex complex(1.8, -2.3);
		complex /= 3;
		BOOST_CHECK_CLOSE(complex.Re(), 0.6, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -23.0 / 30, EPS);
	}
	{
		CComplex complex(1.8, -2.3);
		complex /= complex;
		BOOST_CHECK_CLOSE(complex.Re(), 1, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 0, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestEquality)
{
	{
		const CComplex complex1(2, 5), complex2(2.4, 5.2);
		BOOST_CHECK_EQUAL(complex1 == complex2, false);
		BOOST_CHECK_EQUAL(complex1 != complex2, true);
	}
	{
		const CComplex complex1(2.1, 5.2), complex2(2.1, 5.2);
		BOOST_CHECK_EQUAL(complex1 == complex2, true);
		BOOST_CHECK_EQUAL(complex1 != complex2, false);
	}
	{
		const CComplex complex(2, 0);
		BOOST_CHECK_EQUAL(complex == 2, true);
		BOOST_CHECK_EQUAL(complex != 2, false);
	}
	{
		const CComplex complex(2, -4.2);
		BOOST_CHECK_EQUAL(2 == complex, false);
		BOOST_CHECK_EQUAL(2 != complex, true);
	}
}

BOOST_AUTO_TEST_CASE(TestInputComplex)
{
	{
		string s = "1.2+2.8i";
		CComplex complex;
		istringstream iss(s);
		iss >> complex;
		BOOST_CHECK_CLOSE(complex.Re(), 1.2, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 2.8, EPS);
	}
	{
		string s = "-2.2-24i";
		CComplex complex;
		istringstream iss(s);
		iss >> complex;
		BOOST_CHECK_CLOSE(complex.Re(), -2.2, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), -24, EPS);
	}
	{
		string s = "1.2+2.8";
		CComplex complex;
		istringstream iss(s);
		iss >> complex;
		BOOST_CHECK_CLOSE(complex.Re(), 0, EPS);
		BOOST_CHECK_CLOSE(complex.Im(), 0, EPS);
	}
}

BOOST_AUTO_TEST_CASE(TestOutputComplex)
{
	{
		const CComplex complex(1.2, -2.8);
		ostringstream oss;
		oss << complex;
		string s = oss.str();
		BOOST_CHECK_EQUAL(s, "1.2-2.8i");
	}
	{
		const CComplex complex(1.2, +2);
		ostringstream oss;
		oss << complex;
		string s = oss.str();
		BOOST_CHECK_EQUAL(s, "1.2+2i");
	}
	{
		const CComplex complex(1);
		ostringstream oss;
		oss << complex;
		string s = oss.str();
		BOOST_CHECK_EQUAL(s, "1+0i");
	}
}

BOOST_AUTO_TEST_SUITE_END()