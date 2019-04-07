#pragma once
#include "Shape.h"
class Line :public virtual Shape
{
public:
	Line();
	Line(POINT,POINT);
	~Line();
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

