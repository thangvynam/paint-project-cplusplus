#pragma once
#include<windows.h>
class Shape
{
protected:
	POINT A, B;
public:
	virtual void Draw(HDC) = 0;	
	virtual Shape* Clone() = 0;virtual void setA(POINT)=0;
	virtual void setB(POINT)=0;
};
