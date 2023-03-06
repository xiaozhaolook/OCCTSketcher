#include "Sketcher_CommandPoint.h"

IMPLEMENT_STANDARD_RTTIEXT(Sketcher_CommandPoint, Sketcher_Command)

/**
* \fn Sketcher_CommandPoint()
* \brief Constructs a Sketcher_CommandPoint
*/
Sketcher_CommandPoint::Sketcher_CommandPoint()
: Sketcher_Command("Point.")
{
	myPointAction = Nothing;
}


/**
* \fn ~Sketcher_CommandPoint()
* \brief destructor
*/
Sketcher_CommandPoint::~Sketcher_CommandPoint()
{
}

/**
* \fn Action()
* \brief turn command to active state
*/
void Sketcher_CommandPoint::Action()
{
	myPointAction = Input_Point;
}

/**
* \fn MouseInputEvent(const gp_Pnt2d& thePnt2d )
* \brief input event handler
* \return Standard_Boolean
* \param thePnt2d const gp_Pnt2d&
*/
Standard_Boolean Sketcher_CommandPoint::MouseInputEvent(const gp_Pnt2d& thePnt2d)
{
	curPnt2d = myAnalyserSnap->MouseInput(thePnt2d);
	switch (myPointAction)
	{
	case Nothing:	break;

	case Input_Point:
	{
		Handle(Geom2d_CartesianPoint) myGeom2d_Point = new Geom2d_CartesianPoint(curPnt2d);

		Handle(Geom_CartesianPoint) myGeom_Point = new Geom_CartesianPoint(ElCLib::To3d(curCoordinateSystem.Ax2(), curPnt2d));
		Handle(AIS_Point) myAIS_Point = new AIS_Point(myGeom_Point);
        myContext->Display(myAIS_Point,1);

		AddObject(myGeom2d_Point, myAIS_Point, PointSketcherObject);
	}
	break;
	default:break;
	}
	return Standard_False;
}


/**
* \fn MouseMoveEvent(const gp_Pnt2d& thePnt2d )
* \brief mouse move handler
* \return void
* \param thePnt2d const gp_Pnt2d&
*/
void Sketcher_CommandPoint::MouseMoveEvent(const gp_Pnt2d& thePnt2d)
{
	curPnt2d = myAnalyserSnap->MouseMove(thePnt2d);
}


/**
* \fn CancelEvent()
* \brief cancel event handler, stop entering object
* \return void
*/
void Sketcher_CommandPoint::CancelEvent()
{
	myPointAction = Nothing;
}


/**
* \fn GetTypeOfMethod()
* \brief get command Method
* \return Sketcher_ObjectTypeOfMethod
*/
Sketcher_ObjectTypeOfMethod Sketcher_CommandPoint::GetTypeOfMethod()
{
	return Point_Method;
}
