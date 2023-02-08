#include "Sketcher_SnapLineParallel.h"

IMPLEMENT_STANDARD_RTTIEXT(Sketcher_SnapLineParallel, Sketcher_SnapLine)

/**
* \fn Sketcher_SnapLineParallel()
* \brief Constructs a Sketcher_SnapLineParallel
*/
Sketcher_SnapLineParallel::Sketcher_SnapLineParallel()
{
	myParRelation = new AIS_ParallelRelation(FirstEdge, SecondEdge, myPlane);
}

/**
* \fn ~Sketcher_SnapLineParallel()
* \brief Destructor
*/
Sketcher_SnapLineParallel::~Sketcher_SnapLineParallel()
{
}

/**
* \fn SelectEvent()
* \brief construct line parallel to existing line
* \return void
*/
void Sketcher_SnapLineParallel::SelectEvent()
{
	SelectNearest();
	if (minDistance == minimumSnapDistance / 2)
	{
		nearestPnt2d = curPnt2d;
		curDir2d = gp_Dir2d(gp_Vec2d(curGeom2d_Point->Pnt2d(), curPnt2d));
		minAngle = MINANGLE;

		for (Standard_Integer i = 1; i <= data->Length(); i++)
		{
			mySObject = Handle(Sketcher_Object)::DownCast(data->Value(i));
			myGeometryType = mySObject->GetGeometryType();
			switch (myGeometryType)
			{
			case PointSketcherObject:	break;
			case LineSketcherObject:	curGeom2d_Line = Handle(Geom2d_Line)::DownCast(mySObject->GetGeometry());
				tempDir2d = curGeom2d_Line->Lin2d().Direction();
				checkparallel();
				break;
			case CircleSketcherObject:	break;
			case ArcSketcherObject: 	break;
			default:break;
			}
		}

		if (minAngle == MINANGLE)
			bestPnt2d = curPnt2d;
		else setEdges();

	}
	else
	{
		ProjectPoint();
		setEdges();
	}
}

/**
* \fn GetSnapType()
* \brief get Snap type
* \return Sketcher_SnapType
*/
Sketcher_SnapType Sketcher_SnapLineParallel::GetSnapType()
{
	return SnapParallel;
}

/**
* \fn DrawRelation()
* \brief draw relation
* \return void
*/
void Sketcher_SnapLineParallel::DrawRelation()
{
	myParRelation->SetFirstShape(FirstEdge);
	myParRelation->SetSecondShape(SecondEdge);
    if (firstDisplay) myContext->Display(myParRelation, 0, -1,1);
    else myContext->Redisplay(myParRelation,1);
}

/**
* \fn EraseRelation()
* \brief erase relation
* \return void
*/
void Sketcher_SnapLineParallel::EraseRelation()
{
    myContext->Remove(myParRelation,1);
}
