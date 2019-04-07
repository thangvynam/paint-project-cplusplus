#pragma once
#include "Shape.h"
class CRectangle :public virtual Shape
{
public:
	CRectangle();
	~CRectangle();
	CRectangle(POINT, POINT);
	void Draw(HDC);
	Shape* Clone();
	void setA(POINT A)
	{
		this->A = A;
	}
	void setB(POINT B)
	{
		this->B = B;
	}
};

