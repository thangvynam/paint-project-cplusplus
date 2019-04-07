#pragma once
#include "Line.h"
#include "CRectangle.h"
#include "CEllipse.h"

enum eShape
{
	LINE,
	RECTANGLE,
	ELLIPSE
};

class ShapeFactory
{
private:
	POINT A, B;
public:
	ShapeFactory();
	~ShapeFactory();
	static Shape* createShape(eShape,POINT,POINT);
};

