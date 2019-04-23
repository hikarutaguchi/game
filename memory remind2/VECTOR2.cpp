#include "VECTOR2.h"


VECTOR2::VECTOR2()
{
	x = 0;
	y = 0;
}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;
	this->y = y;
}


VECTOR2::~VECTOR2()
{

}

VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
	this->x = vec.x;	//(*this).x
	this->y = vec.y;
	return (*this);
}

int & VECTOR2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

VECTOR2 & VECTOR2::operator/=(int k)
{
	//0Ç≈äÑÇÁÇ»Ç¢èàóùÇÇµÇƒÇ‡ó«Ç¢
	this->x /= k;
	this->y /= k;
	return (*this);
}

VECTOR2 VECTOR2::operator+() const
{
	return (*this);
}

VECTOR2 VECTOR2::operator-() const
{
	return VECTOR2(-this->x, -this->y);
}

VECTOR2 operator+(const VECTOR2 & u, int y)
{
	VECTOR2 vec;
	vec.x = u.x + y;
	vec.y = u.y + y;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & u, int y)
{
	VECTOR2 vec;
	vec.x = u.x - y;
	vec.y = u.y - y;
	return vec;
}

VECTOR2 operator+(const VECTOR2 & u, const VECTOR2 & k)
{
	VECTOR2 vec;
	vec.x = u.x + k.x;
	vec.y = u.y + k.y;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & u, const VECTOR2 & k)
{
	VECTOR2 vec;
	vec.x = u.x - k.x;
	vec.y = u.y - k.y;
	return vec;
}

VECTOR2 operator*(const VECTOR2 & u, int y)
{
	VECTOR2 vec;
	vec.x = u.x * y;
	vec.y = u.y * y;
	return vec;
}

VECTOR2 operator*(int y, const VECTOR2 & u)
{
	VECTOR2 vec;
	vec.x = y * u.x;
	vec.y = y * u.y;
	return vec;
}

VECTOR2 operator+(int y, const VECTOR2 & u)
{
	VECTOR2 vec;
	vec.x = y + u.x;
	vec.y = y + u.y;
	return vec;
}

VECTOR2 operator/(const VECTOR2 & u, int y)
{
	//0Ç≈äÑÇÁÇ»Ç¢èàóùÇÇµÇƒÇ‡ó«Ç¢
	VECTOR2 vec;
	vec.x = u.x / y;
	vec.y = u.y / y;
	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, int y)
{
	VECTOR2 vec;
	vec.x = u.x % y;
	vec.y = u.y % y;
	return vec;
}

VECTOR2 operator/(const VECTOR2 & u, const VECTOR2 & k)
{
	VECTOR2 vec;
	vec.x = u.x / k.x;
	vec.y = u.y / k.y;
	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, const VECTOR2 & k)
{
	VECTOR2 vec;
	vec.x = u.x % k.x;
	vec.y = u.y % k.y;
	return vec;
}
