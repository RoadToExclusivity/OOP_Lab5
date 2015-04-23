#include "stdafx.h"
#include "Complex.h"

using namespace std;

CComplex::CComplex(double real, double image)
	:m_real(real), m_image(image)
{
}

CComplex::~CComplex()
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(m_real * m_real + m_image * m_image);
}

double CComplex::GetArgument() const
{
	if (fabs(m_real) < DBL_MIN && fabs(m_image) < DBL_MIN)
	{
		return 0;
	}

	return atan2(m_image, m_real);
}

CComplex const operator + (const CComplex &num1, const CComplex &num2)
{
	return CComplex(num1.Re() + num2.Re(), num1.Im() + num2.Im());
}

CComplex const operator - (const CComplex &num1, const CComplex &num2)
{
	return CComplex(num1.Re() - num2.Re(), num1.Im() - num2.Im());
}

CComplex const operator * (const CComplex &num1, const CComplex &num2)
{
	return CComplex(num1.Re() * num2.Re() - num1.Im() * num2.Im(), num1.Im() * num2.Re() + num1.Re() * num2.Im());
}

CComplex const operator / (const CComplex &num1, const CComplex &num2)
{
	double re = 1.0 * (num1.Re() * num2.Re() + num1.Im() * num2.Im()) / (pow(num2.Re(), 2) + pow(num2.Im(), 2));
	double im = 1.0 * (num1.Im() * num2.Re() - num1.Re() * num2.Im()) / (pow(num2.Re(), 2) + pow(num2.Im(), 2));
	return CComplex(re, im);
}

CComplex const CComplex::operator + () const
{
	return CComplex(m_real, m_image);
}

CComplex const CComplex::operator - () const
{
	return CComplex(-m_real, -m_image);
}

CComplex& CComplex::operator += (const CComplex &num)
{
	m_real += num.m_real;
	m_image += num.m_image;

	return *this;
}

CComplex& CComplex::operator -= (const CComplex &num)
{
	m_real -= num.m_real;
	m_image -= num.m_image;

	return *this;
}

CComplex& CComplex::operator *= (const CComplex &num)
{
	double prevReal1 = m_real, prevReal2 = num.m_real;
	m_real = m_real * num.m_real - m_image * num.m_image;
	m_image = m_image * prevReal2 + prevReal1 * num.m_image;

	return *this;
}

CComplex& CComplex::operator /= (const CComplex &num)
{
	double prevReal1 = m_real, prevReal2 = num.m_real;
	m_real = 1.0 * (m_real * num.m_real + m_image * num.m_image) / (pow(num.m_real, 2) + pow(num.m_image, 2));
	m_image = 1.0 * (m_image * prevReal2 - prevReal1 * num.m_image) / (pow(prevReal2, 2) + pow(num.m_image, 2));

	return *this;
}

bool operator == (const CComplex &num1, const CComplex &num2)
{
	return (fabs(num1.GetMagnitude() - num2.GetMagnitude()) < DBL_MIN);
}

bool operator != (const CComplex &num1, const CComplex &num2)
{
	return !(num1 == num2);
}


ostream& operator << (ostream& stream, const CComplex &num)
{
	stream << num.Re();
	if (num.Im() > 0 || (fabs(num.Im()) < DBL_MIN))
	{
		stream << "+";
	}
	stream << num.Im() << "i";

	return stream;
}

istream& operator >> (istream& stream, CComplex &num)
{
	streamoff pos = stream.tellg();

	double re = 0;
	double im = 0;
	if ((stream >> re >> im) && (stream.get() == 'i'))
	{
		num = CComplex(re, im);
		return stream;
	}
	
	stream.seekg(pos);
	stream.setstate(ios_base::failbit | stream.rdstate());

	return stream;
}