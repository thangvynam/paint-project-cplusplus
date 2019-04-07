#pragma once
#include "Shape.h"

class CEllipse :public virtual Shape
{
public:
	CEllipse();
	CEllipse(POINT, POINT);
	~CEllipse();
	void Draw(HDC);
	Shape * Clone();
	void setA(POINT A)
	{
		this->A = A;
	}
	void setB(POINT B)
	{
		this->B = B;
	}
};