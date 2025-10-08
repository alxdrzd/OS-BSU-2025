#pragma once

#include "../NumberLib/Number.h"
#include <ostream>

class Vector{
private:
	Number x_;
	Number y_;
public:
	Vector();
	Vector(const Number&, const Number&);
	Vector(const Vector&);
	~Vector();

	Vector operator-() const;

	Vector operator+(const Vector&) const;
	Vector operator-(const Vector&) const;
	Vector operator*(const Number&) const;
	Vector operator/(const Number&) const;

	bool operator==(const Vector& other) const;
	bool operator!=(const Vector& other) const;

	Number getPolarAngle() const;
	Number getPolarRadius() const;

	Number getX() const;
	Number getY() const;

	static const Vector ZERO_ZERO;
	static const Vector ONE_ONE;

	friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
		os << "Vector(" << vec.x_ << ", " << vec.y_ << ")";
		return os;
	}
};
