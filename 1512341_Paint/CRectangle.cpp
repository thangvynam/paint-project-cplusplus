#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle()
{
}

CRectangle::CRectangle(POINT A,POINT B)
{
	this->A = A;
	this->B = B;

}
CRectangle::~CRectangle()
{
}
void CRectangle::Draw(HDC hdc)
{
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); //Trong suốt
	Rectangle(hdc, A.x, A.y,B.x, B.y);
}
Shape * CRectangle::Clone()
{
	return new CRectangle(*this);
}