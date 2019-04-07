#include "stdafx.h"
#include "CEllipse.h"


CEllipse::CEllipse()
{
}

CEllipse::CEllipse(POINT A, POINT B)
{
	this->A = A;
	this->B = B;

}
CEllipse::~CEllipse()
{
}
void CEllipse::Draw(HDC hdc)
{

	/*HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
	SelectObject(hdc, hPen);

	if (bSetRop == true)
	SetROP2(hdc, R2_MERGEPENNOT);*/

	SelectObject(hdc, GetStockObject(NULL_BRUSH)); //Trong suốt
	Ellipse(hdc, A.x, A.y, B.x, B.y);


	/*ReleaseDC(hwnd, hdc);*/
}
Shape * CEllipse::Clone()
{
	return new CEllipse(*this);
}
