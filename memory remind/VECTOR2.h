#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x, int y);
	~VECTOR2();
	int x;
	int y;

	// ‘ã“ü‰‰ŽZŽq
	VECTOR2& operator = (const VECTOR2& vec);

	// “Y‚¦Žš‰‰ŽZŽq
	int& operator[] (int i);

	// ”äŠr‰‰ŽZŽq ”äŠr‰‰ŽZŒ‹‰Ê‚Í^‹U‚Å‹A‚é‚Ì‚Åbool
	bool operator == (const VECTOR2& vec) const;		// “Ç‚Ýž‚ÝµÝØ°‚Ìê‡‚Í´×°‚ªo‚é‚Ì‚Åconst‚ð•t‚¯‚é
	bool operator >= (const VECTOR2& vec) const;
	bool operator  < (const VECTOR2& vec) const;
														// !=‚É‚È‚Á‚Ä‚é‚â‚Â‚ð‘‚­
	bool operator != (const VECTOR2& vec) const;

	// ’P€‰‰ŽZŽq
	VECTOR2& operator +=(const VECTOR2& vec);
	VECTOR2& operator -=(const VECTOR2& vec);
	VECTOR2& operator *=(int k);
	VECTOR2& operator /=(int k);

	// •„†–³‚µ‚É•„†‚ð‰Á‚¦‚é
	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
};

// ÍÞ¸ÄÙ‚Ì‰‰ŽZ
//VECTOR2 + int
// operator‚ÌŒã‚Éˆ—‚µ‚½‚¢“à—e‚ð‘‚­
VECTOR2 operator+(const VECTOR2 &u, int v);
// VECTOR2 - int
VECTOR2 operator-(const VECTOR2 &u, int v);
// VECTOR2 + VECTOR2
VECTOR2 operator+(const VECTOR2 &u, const VECTOR2 &v);
// VECTOR2 - VECTOR2
VECTOR2 operator-(const VECTOR2 &u, const VECTOR2 &v);
// VECTOR2 * int
VECTOR2 operator*(const VECTOR2 &u, int v);
// VECTOR2 / int
VECTOR2 operator/(const VECTOR2 &u, int v);
// VECTOR2  % int
VECTOR2 operator%(const VECTOR2 &u, int v);
// int * VECTOR2
VECTOR2 operator*(int v, const VECTOR2 &u);
// VECTOR2  % int
VECTOR2 operator%(int u, const VECTOR2 &v);
// VECTOR2 % VECTOR2
VECTOR2 operator%(const VECTOR2 &u, const VECTOR2 &v);
// VECTOR2 / VECTOR2
VECTOR2 operator/(const VECTOR2 &u, const VECTOR2 &v);
// VECTOR2 * VECTOR2
VECTOR2 operator*(const VECTOR2 &u, const VECTOR2 &v);

