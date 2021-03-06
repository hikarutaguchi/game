#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x, int y);
	~VECTOR2();
	int x;
	int y;

	// 代入演算子
	VECTOR2& operator = (const VECTOR2& vec);

	// 添え字演算子
	int& operator[] (int i);

	// 比較演算子 比較演算結果は真偽で帰るのでbool
	bool operator == (const VECTOR2& vec) const;		// 読み込みｵﾝﾘｰの場合はｴﾗｰが出るのでconstを付ける
	bool operator >= (const VECTOR2& vec) const;
	bool operator  < (const VECTOR2& vec) const;
														// !=になってるやつを書く
	bool operator != (const VECTOR2& vec) const;

	// 単項演算子
	VECTOR2& operator +=(const VECTOR2& vec);
	VECTOR2& operator -=(const VECTOR2& vec);
	VECTOR2& operator *=(int k);
	VECTOR2& operator /=(int k);

	// 符号無しに符号を加える
	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
};

// ﾍﾞｸﾄﾙの演算
//VECTOR2 + int
// operatorの後に処理したい内容を書く
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

