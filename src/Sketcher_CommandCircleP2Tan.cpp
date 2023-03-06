#include "Sketcher_CommandCircleP2Tan.h"


IMPLEMENT_STANDARD_RTTIEXT(Sketcher_CommandCircleP2Tan, Sketcher_Command)

/**
* \fn Sketcher_CommandCircleP2Tan()
* \brief Constructs a Sketcher_CommandCircleP2Tan
*/
Sketcher_CommandCircleP2Tan::Sketcher_CommandCircleP2Tan()
: Sketcher_Command("Circle3Tan."),
temp_Circ2d(gp::OX2d(), SKETCHER_RADIUS),
best_Circ(gp::XOY(), SKETCHER_RADIUS)
{
	myCircleP2TanAction = Nothing;

	minDistance = 0;
	curDistance = 0;
	u2 = u_temp = 0;
	mySecondgp_Pnt2d = gp::Origin2d();
	First2dPoint = new Geom2d_CartesianPoint(myFirstgp_Pnt2d);

	tempGeom2d_Circle = new Geom2d_Circle(temp_Circ2d);
	tempGeom_Circle = new Geom_Circle(best_Circ);
	myRubberCircle = new AIS_Circle(tempGeom_Circle);
	myRubberCircle->SetColor(Quantity_NOC_LIGHTPINK1);

	gp_linExist = Standard_False;
	gp_circExist = Standard_False;
}


/**
* \fn ~Sketcher_CommandCircleP2Tan()
* \brief destructor
*/
Sketcher_CommandCircleP2Tan::~Sketcher_CommandCircleP2Tan()
{
}

/**
* \fn Action()
* \brief turn command to active state
*/
void Sketcher_CommandCircleP2Tan::Action()
{
	myCircleP2TanAction = Input_1CirclePoint;
}


/**
* \fn MouseInputEvent(const gp_Pnt2d& thePnt2d )
* \brief input event handler
* \return Standard_Boolean
* \param thePnt2d const gp_Pnt2d&
*/
Standard_Boolean Sketcher_CommandCircleP2Tan::MouseInputEvent(const gp_Pnt2d& thePnt2d)
{
	curPnt2d = myAnalyserSnap->MouseInput(thePnt2d);
	switch (myCircleP2TanAction)
	{
	case Nothing:	break;

	case Input_1CirclePoint:
		First2dPoint->SetPnt2d(curPnt2d);
		myFirstPoint->SetPnt(ElCLib::To3d(curCoordinateSystem.Ax2(), curPnt2d));

		myRubberLine->SetPoints(myFirstPoint, myFirstPoint);
        myContext->Display(myRubberLine, 0, -1,1);
		myCircleP2TanAction = Input_2CircleTan;
		break;

	case Input_2CircleTan:
		SelectCurve();
		if (StoregpObject())
		{
			u2 = u_temp;
			mySecondgp_Pnt2d = tempPnt2d;
			mySecond2d_Curve = tempGeom2d_Curve;
			mySecondPoint->SetPnt(ElCLib::To3d(curCoordinateSystem.Ax2(), tempPnt2d));

			tempGeom_Circle->SetRadius(SKETCHER_RADIUS);
			myRubberCircle->SetCircle(tempGeom_Circle);

            myContext->Display(myRubberCircle, 0, -1,1);
            myContext->Redisplay(myRubberCircle,1);

			myCircleP2TanAction = Input_3CircleTan;
		}
		break;
	case Input_3CircleTan:
		SelectCurve();
		if (CheckgpObject())
		{
			Geom2dAdaptor_Curve SecondAdaptor_Curve(mySecond2d_Curve);
			Geom2dAdaptor_Curve ThirdAdaptor_Curve(tempGeom2d_Curve);

			Geom2dGcc_QualifiedCurve SecondQualifiedCurve(SecondAdaptor_Curve, GccEnt_unqualified);
			Geom2dGcc_QualifiedCurve ThirdQualifiedCurve(ThirdAdaptor_Curve, GccEnt_unqualified);

			//Geom2dGcc_Circ2d3Tan myGcc_Circ2d3Tan(SecondQualifiedCurve, ThirdQualifiedCurve, First2dPoint, 1.0e-12, u2, u_temp);
			Geom2dGcc_Circ2d3Tan* myGcc_Circ2d3Tan = new Geom2dGcc_Circ2d3Tan(SecondQualifiedCurve, ThirdQualifiedCurve, First2dPoint, 1.0e-12, u2, u_temp);

			if (myGcc_Circ2d3Tan->IsDone() && myGcc_Circ2d3Tan->NbSolutions() >0)
			{
				temp_Circ2d = myGcc_Circ2d3Tan->ThisSolution(1);
				Standard_Integer bestCircleIndex = 1;
				if (SumDistanceToCircle())
				{
					minDistance = curDistance;
					best_Circ = ElCLib::To3d(curCoordinateSystem.Ax2(), temp_Circ2d);
					for (Standard_Integer i = 2; i <= myGcc_Circ2d3Tan->NbSolutions(); i++)
					{
						temp_Circ2d = myGcc_Circ2d3Tan->ThisSolution(i);
						if (SumDistanceToCircle() && minDistance > curDistance)
						{
							minDistance = curDistance;
							bestCircleIndex = i;
							best_Circ = ElCLib::To3d(curCoordinateSystem.Ax2(), temp_Circ2d);
						}
					}
					Handle(Geom2d_Circle) myGeom2d_Circle = new Geom2d_Circle(myGcc_Circ2d3Tan->ThisSolution(bestCircleIndex));

					Handle(Geom_Circle) Geom_Circle1 = new Geom_Circle(best_Circ);
					Handle(AIS_Circle) myAIS_Circle = new AIS_Circle(Geom_Circle1);
					AddObject(myGeom2d_Circle, myAIS_Circle, CircleSketcherObject);

                    myContext->Remove(myRubberLine,1);
                    myContext->Remove(myRubberCircle,1);
                    myContext->Display(myAIS_Circle,1);

					gp_linExist = Standard_False;
					gp_circExist = Standard_False;
					myCircleP2TanAction = Input_1CirclePoint;
				}
			}
			//delete myGcc_Circ2d3Tan;
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
void Sketcher_CommandCircleP2Tan::MouseMoveEvent(const gp_Pnt2d& thePnt2d)
{
	curPnt2d = myAnalyserSnap->MouseMove(thePnt2d);
	switch (myCircleP2TanAction)
	{
	case Nothing:break;

	case Input_1CirclePoint:  break;

	case Input_2CircleTan:
		SelectCurve();
		if (minDistance != MINIMUMDISTANCETOCURVE)
		{
			mySecondPoint->SetPnt(ElCLib::To3d(curCoordinateSystem.Ax2(), tempPnt2d));
			myRubberLine->SetPoints(myFirstPoint, mySecondPoint);
            myContext->Redisplay(myRubberLine,1);
		}
		break;
	case Input_3CircleTan:
		SelectCurve();
		if (CheckgpObject())
		{
			Geom2dAdaptor_Curve SecondAdaptor_Curve(mySecond2d_Curve);
			Geom2dAdaptor_Curve ThirdAdaptor_Curve(tempGeom2d_Curve);

			Geom2dGcc_QualifiedCurve SecondQualifiedCurve(SecondAdaptor_Curve, GccEnt_unqualified);
			Geom2dGcc_QualifiedCurve ThirdQualifiedCurve(ThirdAdaptor_Curve, GccEnt_unqualified);

			//Geom2dGcc_Circ2d3Tan myGcc_Circ2d3Tan(SecondQualifiedCurve, ThirdQualifiedCurve, First2dPoint, 1.0e-12, u2, u_temp);
			Geom2dGcc_Circ2d3Tan* myGcc_Circ2d3Tan = new Geom2dGcc_Circ2d3Tan(SecondQualifiedCurve, ThirdQualifiedCurve, First2dPoint, 1.0e-12, u2, u_temp);

			if (myGcc_Circ2d3Tan->IsDone() && myGcc_Circ2d3Tan->NbSolutions() >0)
			{
				temp_Circ2d = myGcc_Circ2d3Tan->ThisSolution(1);
				if (SumDistanceToCircle())
				{
					minDistance = curDistance;
					best_Circ = ElCLib::To3d(curCoordinateSystem.Ax2(), temp_Circ2d);
					for (Standard_Integer i = 2; i <= myGcc_Circ2d3Tan->NbSolutions(); i++)
					{
						temp_Circ2d = myGcc_Circ2d3Tan->ThisSolution(i);
						if (SumDistanceToCircle() && minDistance > curDistance)
						{
							minDistance = curDistance;
							best_Circ = ElCLib::To3d(curCoordinateSystem.Ax2(), temp_Circ2d);
						}
					}
					tempGeom_Circle->SetCirc(best_Circ);
					myRubberCircle->SetCircle(tempGeom_Circle);
                    myContext->Redisplay(myRubberCircle,1);
				}
			}
			else
			{
				tempGeom_Circle->SetRadius(SKETCHER_RADIUS);
                myContext->Redisplay(myRubberCircle,1);
			}
			//delete myGcc_Circ2d3Tan;
		}
		else
		{
			tempGeom_Circle->SetRadius(SKETCHER_RADIUS);
            myContext->Redisplay(myRubberCircle,1);
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
void Sketcher_CommandCircleP2Tan::CancelEvent()
{
	switch (myCircleP2TanAction)
	{
	case Nothing:	break;

	case Input_1CirclePoint:break;

    case Input_2CircleTan: 	myContext->Remove(myRubberLine,1);
		break;
    case Input_3CircleTan: 	myContext->Remove(myRubberLine,1);
        myContext->Remove(myRubberCircle,1);
		break;
	default: break;
	}
	gp_linExist = Standard_False;
	gp_circExist = Standard_False;
	myCircleP2TanAction = Nothing;
}

/**
* \fn GetTypeOfMethod()
* \brief get command Method
* \return Sketcher_ObjectTypeOfMethod
*/
Sketcher_ObjectTypeOfMethod Sketcher_CommandCircleP2Tan::GetTypeOfMethod()
{
	return CircleP2Tan_Method;
}


/**
* \fn SelectCurve()
* \brief selecy nearest curve
* \return void
*/
void Sketcher_CommandCircleP2Tan::SelectCurve()
{
	minDistance = MINIMUMDISTANCETOCURVE;

	for (Standard_Integer i = 1; i <= data->Length(); i++)
	{
		mySObject = Handle(Sketcher_Object)::DownCast(data->Value(i));
		switch (mySObject->GetGeometryType())
		{
		case PointSketcherObject:	break;
		case LineSketcherObject:
		{
			Handle(Geom2d_Edge) curGeom2d_Edge = Handle(Geom2d_Edge)::DownCast(mySObject->GetGeometry());
			myProjectOnCurve.Init(curPnt2d, curGeom2d_Edge, curGeom2d_Edge->StartParameter(), curGeom2d_Edge->EndParameter());
			if (myProjectOnCurve.NbPoints() > 0)
			{
				curDistance = curPnt2d.Distance(myProjectOnCurve.NearestPoint());
				if (minDistance > curDistance)
				{
					minDistance = curDistance;
					tempPnt2d = myProjectOnCurve.NearestPoint();
					u_temp = ElCLib::Parameter(curGeom2d_Edge->Lin2d(), tempPnt2d);
					Handle(Geom2d_Line) temp_Line = new Geom2d_Line(curGeom2d_Edge->Lin2d());
					tempGeom2d_Curve = temp_Line;
				}
			}
		}
		break;
		case CircleSketcherObject:
		{
			Handle(Geom2d_Circle) curGeom2d_Circle = Handle(Geom2d_Circle)::DownCast(mySObject->GetGeometry());
			myProjectOnCurve.Init(curPnt2d, curGeom2d_Circle);
			if (myProjectOnCurve.NbPoints() > 0)
			{
				curDistance = curPnt2d.Distance(myProjectOnCurve.NearestPoint());
				if (minDistance > curDistance)
				{
					minDistance = curDistance;
					tempPnt2d = myProjectOnCurve.NearestPoint();
					u_temp = ElCLib::Parameter(curGeom2d_Circle->Circ2d(), tempPnt2d);
					tempGeom2d_Curve = curGeom2d_Circle;
				}
			}
		}
		break;
		case ArcSketcherObject:
		{
			Handle(Geom2d_Arc) curGeom2d_Arc = Handle(Geom2d_Arc)::DownCast(mySObject->GetGeometry());
			myProjectOnCurve.Init(curPnt2d, curGeom2d_Arc);
			if (myProjectOnCurve.NbPoints() > 0)
			{
				curDistance = curPnt2d.Distance(myProjectOnCurve.NearestPoint());
				if (minDistance > curDistance)
				{
					minDistance = curDistance;
					tempPnt2d = myProjectOnCurve.NearestPoint();
					u_temp = ElCLib::Parameter(curGeom2d_Arc->Circ2d(), tempPnt2d);
					Handle(Geom2d_Circle) temp_Circle = new Geom2d_Circle(curGeom2d_Arc->Circ2d());
					tempGeom2d_Curve = temp_Circle;
				}
			}
		}
		break;
		default:break;
		}
	}
}


/**
* \fn SumDistanceToCircle()
* \brief select circle orientation
* \return Standard_Boolean
*/
Standard_Boolean Sketcher_CommandCircleP2Tan::SumDistanceToCircle()
{
	curDistance = 0;
	tempGeom2d_Circle->SetCirc2d(temp_Circ2d);
	myProjectOnCurve.Init(mySecondgp_Pnt2d, tempGeom2d_Circle);
	if (myProjectOnCurve.NbPoints() > 0)
		curDistance = mySecondgp_Pnt2d.Distance(myProjectOnCurve.NearestPoint());
	else
		return Standard_False;

	myProjectOnCurve.Init(tempPnt2d, tempGeom2d_Circle);
	if (myProjectOnCurve.NbPoints() > 0)
		curDistance += tempPnt2d.Distance(myProjectOnCurve.NearestPoint());
	else
		return Standard_False;

	return Standard_True;
}


/**
* \fn CheckgpObject()
* \brief check object, is it possible to create tangent circle
* \return Standard_Boolean
*/
Standard_Boolean Sketcher_CommandCircleP2Tan::CheckgpObject()
{
	if (minDistance != MINIMUMDISTANCETOCURVE)
	{
		if (tempGeom2d_Curve->IsKind(STANDARD_TYPE(Geom2d_Line)))
		{
			Handle(Geom2d_Line) tnl = Handle(Geom2d_Line)::DownCast(tempGeom2d_Curve);
			if (gp_linExist)
				if (gp_lin.Position().IsParallel(tnl->Lin2d().Position(), 1.0e-12) && gp_lin.Contains(tnl->Lin2d().Location(), 1.0e-12))
					return Standard_False;
		}
		else if (tempGeom2d_Curve->IsKind(STANDARD_TYPE(Geom2d_Circle)))
		{
			Handle(Geom2d_Circle) tnc = Handle(Geom2d_Circle)::DownCast(tempGeom2d_Curve);
			if (gp_circExist)
			{
				if (gp_circ.Location().IsEqual(tnc->Circ2d().Location(), 1.0e-12) && gp_circ.Radius() == tnc->Circ2d().Radius())
					return Standard_False;
			}
		}
		return Standard_True;
	}
	else return Standard_False;
}


/**
* \fn StoregpObject()
* \brief store objects for building tangent circle
* \return Standard_Boolean
*/
Standard_Boolean Sketcher_CommandCircleP2Tan::StoregpObject()
{
	if (minDistance != MINIMUMDISTANCETOCURVE)
	{
		if (tempGeom2d_Curve->IsKind(STANDARD_TYPE(Geom2d_Line)))
		{
			Handle(Geom2d_Line) tnl = Handle(Geom2d_Line)::DownCast(tempGeom2d_Curve);
			gp_lin = tnl->Lin2d();
			gp_linExist = Standard_True;
		}
		else if (tempGeom2d_Curve->IsKind(STANDARD_TYPE(Geom2d_Circle)))
		{
			Handle(Geom2d_Circle) tnc = Handle(Geom2d_Circle)::DownCast(tempGeom2d_Curve);
			gp_circ = tnc->Circ2d();
			gp_circExist = Standard_True;
		}
		return Standard_True;
	}
	else return Standard_False;
}
