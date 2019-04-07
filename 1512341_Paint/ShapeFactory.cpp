#include "stdafx.h"
#include "ShapeFactory.h"


ShapeFactory::ShapeFactory()
{
}


ShapeFactory::~ShapeFactory()
{
}

Shape* ShapeFactory::createShape(eShape eshape,POINT A,POINT B)
{
	switch (eshape)
	{
		case LINE: 
			return new Line(A, B);
		case RECTANGLE: 
			return new CRectangle(A, B);
		case ELLIPSE:
			return new CEllipse(A, B);
	default:
		break;
	}
}
