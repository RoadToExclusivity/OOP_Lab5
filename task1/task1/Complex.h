#pragma once
class CComplex
{
public:
	CComplex(double real = 0, double image = 0);
	~CComplex();

	double Re() const;
	double Im() const;
	double GetMagnitude() const;
	double GetArgument() const;

	CComplex const operator + () const;
	CComplex const operator - () const;

	CComplex& operator += (const CComplex &num);
	CComplex& operator -= (const CComplex &num);
	CComplex& operator *= (const CComplex &num);
	CComplex& operator /= (const CComplex &num);

private:
	double m_real;
	double m_image;

};

CComplex const operator + (const CComplex &num1, const CComplex &num2);
CComplex const operator - (const CComplex &num1, const CComplex &num2);
CComplex const operator * (const CComplex &num1, const CComplex &num2);
CComplex const operator / (const CComplex &num1, const CComplex &num2);

bool operator == (const CComplex &num1, const CComplex &num2);
bool operator != (const CComplex &num1, const CComplex &num2);

std::ostream& operator << (std::ostream& stream, const CComplex &num);
std::istream& operator >> (std::istream& stream, CComplex &num);