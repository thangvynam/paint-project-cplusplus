#pragma once
#include "Line.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include <vector>
using namespace std;
class ShapePrototype
{
private:
	POINT A, B; 
	static vector<Shape*> prototypes;
public:
	ShapePrototype();
	ShapePrototype(POINT,POINT);
	~ShapePrototype();
	Shape* ShapePrototype::make_stooge(int idex)
	{
		return prototypes.at(idex)->Clone();
	}
};

