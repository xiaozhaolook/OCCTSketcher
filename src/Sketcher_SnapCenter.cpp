#include "Sketcher_SnapCenter.h"

IMPLEMENT_STANDARD_RTTIEXT(Sketcher_SnapCenter, Sketcher_Snap)

/**
* \fn Sketcher_SnapCenter()
* \brief Constructs a Sketcher_SnapCenter
*/
Sketcher_SnapCenter::Sketcher_SnapCenter()
{
}

/**
* \fn ~Sketcher_SnapCenter()
* \brief Destructor
*/
Sketcher_SnapCenter::~Sketcher_SnapCenter()
{
}

/**
* \fn SelectEvent()
* \brief find center point of arc, circle
* \return void
*/
void Sketcher_SnapCenter::SelectEvent()
{
	findbestPnt2d = Standard_False;
	minDistance = minimumSnapDistance;

	for (Standard_Integer i = 1; i <= data->Length(); i++)
	{
		mySObject = Handle(Sketcher_Object)::DownCast(data->Value(i));
		myGeometryType = mySObject->GetGeometryType();
		switch (myGeometryType)
		{
		case PointSketcherObject:	break;
		case LineSketcherObject:	break;
		case CircleSketcherObject:
		case ArcSketcherObject: 	curGeom2d_Circle = Handle(Geom2d_Circle)::DownCast(mySObject->GetGeometry());
			ProjectOnCurve.Init(curPnt2d, curGeom2d_Circle);
			if (countProject())
			{
				bestPnt2d = curGeom2d_Circle->Location();
				curHilightedObj = mySObject->GetAIS_Object();
			}
			objectPnt2d = curGeom2d_Circle->Location();
			if (count())
			{
				bestPnt2d = objectPnt2d;
				curHilightedObj = mySObject->GetAIS_Object();
			}
			break;
		default:break;
		}
	}

	if (minDistance == minimumSnapDistance)
		bestPnt2d = curPnt2d;
	else   findbestPnt2d = Standard_True;

}

/**
* \fn GetSnapType()
* \brief get Snap type
* \return Sketcher_SnapType
*/
Sketcher_SnapType Sketcher_SnapCenter::GetSnapType()
{
	return SnapCenter;
}
