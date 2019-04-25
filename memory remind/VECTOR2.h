#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x, int y);
	~VECTOR2();
	int x;
	int y;

	// ������Z�q
	VECTOR2& operator = (const VECTOR2& vec);

	// �Y�������Z�q
	int& operator[] (int i);

	// ��r���Z�q ��r���Z���ʂ͐^�U�ŋA��̂�bool
	bool operator == (const VECTOR2& vec) const;		// �ǂݍ��ݵ�ذ�̏ꍇ�ʹװ���o��̂�const��t����
	bool operator >= (const VECTOR2& vec) const;
	bool operator  < (const VECTOR2& vec) const;
														// !=�ɂȂ��Ă�������
	bool operator != (const VECTOR2& vec) const;

	// �P�����Z�q
	VECTOR2& operator +=(const VECTOR2& vec);
	VECTOR2& operator -=(const VECTOR2& vec);
	VECTOR2& operator *=(int k);
	VECTOR2& operator /=(int k);

	// ���������ɕ�����������
	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
};

// �޸�ق̉��Z
//VECTOR2 + int
// operator�̌�ɏ������������e������
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

