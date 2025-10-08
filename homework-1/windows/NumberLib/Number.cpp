#include "pch.h"
#include "Number.h"

const Number Number::ZERO(0.0);
const Number Number::ONE(1.0);

Number::Number() : value_(0) {}

Number::Number(double value) : value_(value) {}

Number::Number(const Number& other) : value_(other.value_) {}

Number::~Number() = default;

Number& Number::operator=(const Number& other) {
	if (this != &other) {
		value_ = other.value_;
	}
	return *this;
}

Number Number::operator-() const
{
	return Number(-value_);
}

Number Number::operator+() const
{
	return Number(value_);
}

Number Number::operator+(const Number& other) const
{
	return Number(value_ + other.value_);
}

Number Number::operator-(const Number& other) const
{
	return Number(value_ - other.value_);
}

Number Number::operator*(const Number& other) const
{
	return Number(value_ * other.value_);
}

Number Number::operator/(const Number& other) const
{
	if (other.value_ == 0.0) {
		throw std::runtime_error("Division by zero is prohibited!");
	}

	return Number(this->value_ / other.value_);
}

Number& Number::operator+=(const Number& other)
{
	this->value_ += other.value_;
	return *this;
}
Number& Number::operator-=(const Number& other)
{
	this->value_ -= other.value_;
	return *this;
}
Number& Number::operator*=(const Number& other)
{
	this->value_ *= other.value_;
	return *this;
}
Number& Number::operator/=(const Number& other)
{
	if (other.value_ == 0.0) {
		throw std::runtime_error("Division by zero is prohibited!");
	}
	this->value_ /= other.value_;
	return *this;
}

bool Number::operator==(const Number& other) const
{
	return std::abs(this->value_ - other.value_) <= 0.0001;
}

bool Number::operator!=(const Number& other) const
{
	return !(*this == other);
}

bool Number::operator<(const Number& other) const
{
	return this->value_ < other.value_;
}

bool Number::operator>(const Number& other) const
{
	return this->value_ > other.value_;
}

bool Number::operator<=(const Number& other) const
{
	return (this->value_ < other.value_) || (*this == other);
}

bool Number::operator>=(const Number& other) const
{
	return (this->value_ > other.value_) || (*this == other);
}

double Number::getValue() const
{
	return this->value_;
}

Number createNumber(double value)
{
	return Number(value);
}

std::ostream& operator<<(std::ostream& os, const Number& number)
{
	os << number.getValue();
	return os;
}
