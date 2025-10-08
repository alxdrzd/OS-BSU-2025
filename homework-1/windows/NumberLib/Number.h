#pragma once
#include <ostream>
#include <stdexcept>
#include <cmath>

class Number {
public:
	Number();
	Number(double);
	Number(const Number&);
	~Number();

	Number& operator=(const Number&);

	Number operator-() const;
	Number operator+() const;

	Number operator+(const Number&) const;
	Number operator-(const Number&) const;
	Number operator*(const Number&) const;
	Number operator/(const Number&) const;
	
	Number& operator+=(const Number&);
	Number& operator-=(const Number&);
	Number& operator*=(const Number&);
	Number& operator/=(const Number&);

	bool operator==(const Number&) const;
	bool operator!=(const Number&) const;
	bool operator<(const Number&) const;
	bool operator>(const Number&) const;
	bool operator<=(const Number&) const;
	bool operator>=(const Number&) const;

	static const Number ZERO;
	static const Number ONE;

	

	double getValue() const;

private:
	double value_;
};

Number createNumber(double value);

std::ostream& operator<<(std::ostream&, const Number&);