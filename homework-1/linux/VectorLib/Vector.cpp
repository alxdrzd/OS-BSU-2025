#include "Vector.h"
#include <cmath>

Vector::Vector() : x_(Number()), y_(Number()) { }

Vector::Vector(const Number& x, const Number& y) : x_(x), y_(y) { }

Vector::Vector(const Vector& other) : x_(other.x_), y_(other.y_) { }

Vector::~Vector() = default;

Vector Vector::operator-() const
{
	return Vector(-this->x_, -this->y_);
}

const Vector Vector::ZERO_ZERO(Number(0.0), Number(0.0));
const Vector Vector::ONE_ONE(Number(1.0), Number(1.0));

Vector Vector::operator+(const Vector& other) const
{
	return Vector(this->x_ + other.x_, this->y_ + other.y_);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(this->x_ - other.x_, this->y_ - other.y_);
}

Vector Vector::operator*(const Number& alpha) const
{
	return Vector(this->x_ * alpha, this->y_ * alpha);
}

Vector Vector::operator/(const Number& alpha) const
{
	if (alpha == Number::ZERO) {
		throw std::runtime_error("Division by zero is prohibited!");
	}
	return Vector(this->x_ / alpha, this->y_ / alpha);
}

bool Vector::operator==(const Vector& other) const {
	return (x_ == other.x_) && (y_ == other.y_);
}

bool Vector::operator!=(const Vector& other) const {
	return !(*this == other);
}

Number Vector::getPolarAngle() const
{
	if (x_ == Number::ZERO && y_ == Number::ZERO) {
		return Number::ZERO;
	}
	return Number(std::atan2(y_.getValue(), x_.getValue()));
}

Number Vector::getPolarRadius() const
{
	return Number(std::sqrt(this->x_.getValue() * this->x_.getValue() +
		this->y_.getValue() * this->y_.getValue()));
}

Number Vector::getX() const
{
	return this->x_;  
}

Number Vector::getY() const
{
	return this->y_;  
}

