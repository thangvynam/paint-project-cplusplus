#include "stdafx.h"
#include "Line.h"


Line::Line()
{
}


Line::~Line()
{
}
void Line::Draw(HDC hdc)
{
	MoveToEx(hdc, A.x, A.y, NULL);
	LineTo(hdc, B.x, B.y);
}
Line::Line(POINT A,POINT B)
{
	this->A = A;
	this->B = B;
}
Shape * Line::Clone()
{
	return new Line(*this);
}