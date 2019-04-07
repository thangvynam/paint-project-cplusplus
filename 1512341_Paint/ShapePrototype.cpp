#include "stdafx.h"
#include "ShapePrototype.h"

vector<Shape*> ShapePrototype::prototypes;
ShapePrototype::ShapePrototype()
{
	
}
ShapePrototype::ShapePrototype(POINT A, POINT B)
{
	prototypes.push_back(new Line(A, B));
	prototypes.push_back(new CRectangle(A, B));
	prototypes.push_back(new CEllipse(A, B));
}
ShapePrototype::~ShapePrototype()
{
}
