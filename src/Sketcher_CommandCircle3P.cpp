#include "Sketcher_CommandCircle3P.h"

IMPLEMENT_STANDARD_RTTIEXT(Sketcher_CommandCircle3P, Sketcher_Command)

/**
* \fn Sketcher_CommandCircle3P()
* \brief Constructs a Sketcher_CommandCircle3P
*/
Sketcher_CommandCircle3P::Sketcher_CommandCircle3P()
: Sketcher_Command("Circle3P."),
tempCirc(curCoordinateSystem.Ax2(), SKETCHER_RADIUS)
{
	myCircle3PAction = Nothing;

	tempGeom_Circle = new Geom_Circle(curCoordinateSystem.Ax2(), SKETCHER_RADIUS);
	myRubberCircle = new AIS_Circle(tempGeom_Circle);
	myRubberCircle->SetColor(Quantity_NOC_LIGHTPINK1);

	mySecondgp_Pnt2d = gp::Origin2d();
	third_Pnt = gp::Origin();
}


/**
* \fn ~Sketcher_CommandCircle3P()
* \brief destructor
*/
Sketcher_CommandCircle3P::~Sketcher_CommandCircle3P()
{
}

/**
* \fn Action()
* \brief turn command to active state
*/
void Sketcher_CommandCircle3P::Action()
{
	myCircle3PAction = Input_1CirclePoint;
	tempCirc.SetPosition(curCoordinateSystem.Ax2());
}


/**
* \fn MouseInputEvent(const gp_Pnt2d& thePnt2d )
* \brief input event handler
* \return Standard_Boolean
* \param thePnt2d const gp_Pnt2d&
*/
Standard_Boolean Sketcher_CommandCircle3P::MouseInputEvent(const gp_Pnt2d& thePnt2d)
{
	curPnt2d = myAnalyserSnap->MouseInput(thePnt2d);
	switch (myCircle3PAction)
	{
	case Nothing:	break;

	case Input_1CirclePoint:
		myFirstgp_Pnt2d = curPnt2d;
		myFirstPoint->SetPnt(ElCLib::To3d(curCoordinateSystem.Ax2(), curPnt2d));

		myRubberLine->SetPoints(myFirstPoint, myFirstPoint);
        myContext->Display(myRubberLine, 0, -1,1);

		myCircle3PAction = Input_2CirclePoint;
		break;

	case Input_2CirclePoint:
	{
		mySecondgp_Pnt2d = curPnt2d;
		mySecondPoint->SetPnt(ElCLib::To3d(curCoordinateSystem.Ax2(), curPnt2d));
		tempCirc.SetLocation(myFirstPoint->Pnt().Scaled(mySecondPoint->Pnt(), 0.5));
		tempCirc.SetRadius(myFirstgp_Pnt2d.Distance(curPnt2d) / 2);

		tempGeom_Circle->SetCirc(tempCirc);
		myRubberCircle->SetCircle(tempGeom_Circle);

        myContext->Remove(myRubberLine,1);
        myContext->Display(myRubberCircle, 0, -1,1);
        myContext->Redisplay(myRubberCircle,1);

		myCircle3PAction = Input_3CirclePoint;
	}
	break;
	case Input_3CirclePoint:
	{
		gce_MakeCirc2d tempMakeCirc2d(myFirstgp_Pnt2d, mySecondgp_Pnt2d, curPnt2d);
		if (tempMakeCirc2d.Status() == gce_Done)
		{
			Handle(Geom2d_Circle) myGeom2d_Circle = new Geom2d_Circle(tempMakeCirc2d.Value());

			Handle(Geom_Circle) Geom_Circle1 = new Geom_Circle(ElCLib::To3d(curCoordinateSystem.Ax2(), myGeom2d_Circle->Circ2d()));
			Handle(AIS_Circle) myAIS_Circle = new AIS_Circle(Geom_Circle1);
			AddObject(myGeom2d_Circle, myAIS_Circle, CircleSketcherObject);

            myContext->Remove(myRubberCircle,1);
            myContext->Display(myAIS_Circle,1);
			myCircle3PAction = Input_1CirclePoint;
		}
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
void Sketcher_CommandCircle3P::MouseMoveEvent(const gp_Pnt2d& thePnt2d)
{
	curPnt2d = myAnalyserSnap->MouseMove(thePnt2d);
	switch (myCircle3PAction)
	{
	case Nothing:break;

	case Input_1CirclePoint: break;

	case Input_2CirclePoint:
		mySecondPoint->SetPnt(ElCLib::To3d(curCoordinateSystem.Ax2(), curPnt2d));
		myRubberLine->SetPoints(myFirstPoint, mySecondPoint);
        myContext->Redisplay(myRubberLine,1);
		break;
	case Input_3CirclePoint:
	{
		third_Pnt = ElCLib::To3d(curCoordinateSystem.Ax2(), curPnt2d);
		gce_MakeCirc tempMakeCirc = gce_MakeCirc(myFirstPoint->Pnt(), mySecondPoint->Pnt(), third_Pnt);
		if (tempMakeCirc.Status() == gce_Done)
		{
			tempGeom_Circle->SetCirc(tempMakeCirc.Value());
			//				myRubberCircle->SetCircle(tempGeom_Circle);
            myContext->Redisplay(myRubberCircle,1);
		}
	}
	break;
	default:break;
	}
}


/**
* \fn CancelEvent()
* \brief cancel event handler, stop entering object
* \return void
*/
void Sketcher_CommandCircle3P::CancelEvent()
{
	switch (myCircle3PAction)
	{
	case Nothing:	break;

	case Input_1CirclePoint: break;

    case Input_2CirclePoint: myContext->Remove(myRubberLine,1);
		break;
    case Input_3CirclePoint: myContext->Remove(myRubberCircle,1);
		break;
	default: break;
	}
	myCircle3PAction = Nothing;
}

/**
* \fn GetTypeOfMethod()
* \brief get command Method
* \return Sketcher_ObjectTypeOfMethod
*/
Sketcher_ObjectTypeOfMethod Sketcher_CommandCircle3P::GetTypeOfMethod()
{
	return Circle3P_Method;
}
