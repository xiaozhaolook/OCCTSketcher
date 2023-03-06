#include "Sketcher.h"

/**
* \fn Sketcher(Handle(AIS_InteractiveContext)& theContext, Sketcher_GUI* sg)
* \brief Constructs a Sketcher
* \param theContext Handle(AIS_InteractiveContext)&
* \param sg Sketcher_GUI*
*/
Sketcher::Sketcher(Handle(AIS_InteractiveContext)& theContext, Sketcher_GUI* sg)
	: myCoordinateSystem(gp::XOY())
{
	myContext = theContext;
	myGUI = sg;
	myGUI->SetAx3(myCoordinateSystem);
	myGUI->SetContext(myContext);

	myCurrentMethod = Nothing_Method;

	myCurrentDir = gp::DZ();
	myTempPnt = gp::Origin();
	myCurrentPnt2d = gp::Origin2d();
	myCurrentPlane = new Geom_Plane(myCoordinateSystem);
	myCurrentLine = new Geom_Line(myTempPnt, myCurrentDir);

	PolylineFirstPoint = gp::Origin2d();
	PolylineFirstPointExist = Standard_False;

	myData = new TColStd_HSequenceOfTransient();
	myCommands = new TColStd_HSequenceOfTransient();

	myAnalyserSnap = new Sketcher_AnalyserSnap(myContext, myData, myCoordinateSystem);

	addCommand(new Sketcher_CommandPoint());
	addCommand(new Sketcher_CommandLine2P());
	addCommand(new Sketcher_CommandCircleCenterRadius());
	addCommand(new Sketcher_CommandCircle3P());
	addCommand(new Sketcher_CommandCircle2PTan());
	addCommand(new Sketcher_CommandCircleP2Tan());
	addCommand(new Sketcher_CommandCircle3Tan());
	addCommand(new Sketcher_CommandArc3P());
	addCommand(new Sketcher_CommandArcCenter2P());
	addCommand(new Sketcher_CommandBezierCurve());
	addCommand(new Sketcher_CommandTrim());
}

/**
* \fn ~Sketcher()
* \brief destructor
*/
Sketcher::~Sketcher()
{
	delete myGUI;
}

/**
* \fn SetContext(Handle(AIS_InteractiveContext)& theContext)
* \brief set context
* \return void
* \param theContext Handle(AIS_InteractiveContext)&
*/
void Sketcher::SetContext(Handle(AIS_InteractiveContext)& theContext)
{
	myContext = theContext;
	myAnalyserSnap->SetContext(myContext);
	myGUI->SetContext(theContext);
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetContext(myContext);
	}
}


/**
* \fn SetData(Handle(TColStd_HSequenceOfTransient)& thedata)
* \brief set list of objects
* \return void
* \param thedata TColStd_HSequenceOfTransient)&
*/
void Sketcher::SetData(Handle(TColStd_HSequenceOfTransient)& thedata)
{
	myData = thedata;
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetData(myData);
	}
}


/**
* \fn GetData()
* \brief get list of objects
* \return Handle(TColStd_HSequenceOfTransient)&
*/
Handle(TColStd_HSequenceOfTransient) Sketcher::GetData()
{
	return myData;
}

/**
* \fn SetCoordinateSystem(const gp_Ax3& theCS)
* \brief set coordinate system
* \return void
* \param theCS const gp_Ax3&
*/
void Sketcher::SetCoordinateSystem(const gp_Ax3& theCS)
{
	myCoordinateSystem = theCS;
	myCurrentPlane->SetPosition(myCoordinateSystem);
	myAnalyserSnap->SetAx3(myCoordinateSystem);
	myGUI->SetAx3(myCoordinateSystem);

	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetAx3(myCoordinateSystem);
	}
}

/**
* \fn GetCoordinateSystem()
* \brief get coordinate system from Sketcher
* \return gp_Ax3
*/
gp_Ax3 Sketcher::GetCoordinateSystem()
{
	return myCoordinateSystem;
}

/**
* \fn SetPrecise(const Standard_Real& aPrecise)
* \brief set precise for snap
* \return void
* \param aPrecise const Standard_Real&
*/
void Sketcher::SetPrecise(const Standard_Real& aPrecise)
{
	if (aPrecise > 0)
		myAnalyserSnap->SetMinDistance(aPrecise);
}

/**
* \fn SetColor(const Quantity_NameOfColor theColor)
* \brief set color
* \return void
* \param theColor const Quantity_NameOfColor
*/
void Sketcher::SetColor(const Quantity_NameOfColor theColor)
{
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetColor(theColor);
	}
}

/**
* \fn SetType(const Sketcher_ObjectType theType)
* \brief set type of object
* \return void
* \param theType const Sketcher_ObjectType
*/
void Sketcher::SetType(const Sketcher_ObjectType theType)
{
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetType(theType);
	}
}

/**
* \fn SetStyle(const Aspect_TypeOfLine theLineStyle)
* \brief set line style
* \return void
* \param theLineStyle const Aspect_TypeOfLine
*/
void Sketcher::SetStyle(const Aspect_TypeOfLine theLineStyle)
{
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetStyle(theLineStyle);
	}
}

/**
* \fn SetWidth(const Standard_Real& theWidth)
* \brief set line width
* \return void
* \param theWidth const Standard_Real&
*/
void Sketcher::SetWidth(const Standard_Real& theWidth)
{
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetWidth(theWidth);
	}
}

/**
* \fn ObjectAction(const Sketcher_ObjectTypeOfMethod theMethod)
* \brief set entering object command by theMethod
* \return void
* \param theMethod const Sketcher_ObjectTypeOfMethod
*/
void Sketcher::ObjectAction(const Sketcher_ObjectTypeOfMethod theMethod)
{
	myCurrentMethod = theMethod;
	SelectCurCommand();
	CurCommand->Action();
	if ((myCurrentMethod == Line2P_Method || myCurrentMethod == Arc3P_Method) && PolylineFirstPointExist)
		CurCommand->SetPolylineFirstPnt(PolylineFirstPoint);
	else PolylineFirstPointExist = Standard_False;
}

/**
* \fn GetStatus()
* \brief get current object create method
* \return Sketcher_ObjectTypeOfMethod
*/
Sketcher_ObjectTypeOfMethod Sketcher::GetStatus()
{
	return myCurrentMethod;
}

/**
* \fn OnMouseInputEvent(const Standard_Real &v3dX,const Standard_Real &v3dY,const Standard_Real &v3dZ,const Standard_Real& projVx,const Standard_Real& projVy,const Standard_Real& projVz)
* \brief input event handler
* \return void
* \param v3dX const Standard_Real&
* \param v3dY const Standard_Real&
* \param v3dZ const Standard_Real&
* \param projVx const Standard_Real&
* \param projVy const Standard_Real&
* \param projVz const Standard_Real&
*/
void Sketcher::OnMouseInputEvent(const Standard_Real &v3dX, const Standard_Real &v3dY, const Standard_Real &v3dZ,
    const Standard_Real& projVx, const Standard_Real& projVy, const Standard_Real& projVz)
{
	if (ProjectPointOnPlane(v3dX, v3dY, v3dZ, projVx, projVy, projVz))
	{
		SelectCurCommand();
		if (CurCommand->MouseInputEvent(myCurrentPnt2d))
			myCurrentMethod = Nothing_Method;
	}
}

void Sketcher::OnMouseInputEvent(Standard_Integer theX, Standard_Integer theY)
{
	Handle(V3d_View) aView = myContext->CurrentViewer()->ActiveView();

	Standard_Real aVx = 0.0;
	Standard_Real aVy = 0.0;
	Standard_Real aVz = 0.0;
	Standard_Real aPx = 0.0;
	Standard_Real aPy = 0.0;
	Standard_Real aPz = 0.0;

	aView->Convert(theX, theY, aVx, aVy, aVz);
	aView->Proj(aPx, aPy, aPz);

	OnMouseInputEvent(aVx, aVy, aVz, aPx, aPy, aPz);
}

/**
* \fn OnMouseMoveEvent(const Standard_Real &v3dX,const Standard_Real &v3dY,const Standard_Real &v3dZ,const Standard_Real& projVx,const Standard_Real& projVy,const Standard_Real& projVz)
* \brief mouse move handler
* \return void
* \param v3dX const Standard_Real&
* \param v3dY const Standard_Real&
* \param v3dZ const Standard_Real&
* \param projVx const Standard_Real&
* \param projVy const Standard_Real&
* \param projVz const Standard_Real&
*/
void Sketcher::OnMouseMoveEvent(const Standard_Real &v3dX, const Standard_Real &v3dY, const Standard_Real &v3dZ,
    const Standard_Real& projVx, const Standard_Real& projVy, const Standard_Real& projVz)
{
	if (ProjectPointOnPlane(v3dX, v3dY, v3dZ, projVx, projVy, projVz))
	{
		SelectCurCommand();
		CurCommand->MouseMoveEvent(myCurrentPnt2d);
	}
}

void Sketcher::OnMouseMoveEvent(Standard_Integer theX, Standard_Integer theY)
{
	Handle(V3d_View) aView = myContext->CurrentViewer()->ActiveView();

	Standard_Real aVx = 0.0;
	Standard_Real aVy = 0.0;
	Standard_Real aVz = 0.0;
	Standard_Real aPx = 0.0;
	Standard_Real aPy = 0.0;
	Standard_Real aPz = 0.0;

	aView->Convert(theX, theY, aVx, aVy, aVz);
	aView->Proj(aPx, aPy, aPz);

	OnMouseMoveEvent(aVx, aVy, aVz, aPx, aPy, aPz);
}

/**
* \fn OnCancel()
* \brief cancel event handler, stop entering object
* \return void
*/
void Sketcher::OnCancel()
{
	SelectCurCommand();
	myAnalyserSnap->Cancel();
	if (myCurrentMethod == Line2P_Method || myCurrentMethod == Arc3P_Method)
		PolylineFirstPointExist = CurCommand->GetPolylineFirstPnt(PolylineFirstPoint);
	CurCommand->CancelEvent();

	myCurrentMethod = Nothing_Method;
}

/**
* \fn DeleteSelectedObject()
* \brief delete objects selected in the context
* \return void
*/
void Sketcher::DeleteSelectedObject()
{
	for (Standard_Integer i = 1; i <= myData->Length(); i++)
	{
		myCurObject = Handle(Sketcher_Object)::DownCast(myData->Value(i));
		if (myContext->IsSelected(myCurObject->GetAIS_Object()))
		{
			myContext->Erase(myCurObject->GetAIS_Object(), Standard_True);
			myData->Remove(i);
		}
	}
}

/**
* \fn ViewProperties()
* \brief show properties for selected object
* \return void
*/
void Sketcher::ViewProperties()
{
	for (Standard_Integer i = 1; i <= myData->Length(); i++)
	{
		myCurObject = Handle(Sketcher_Object)::DownCast(myData->Value(i));
		if (myContext->IsSelected(myCurObject->GetAIS_Object()))
		{
            myContext->ClearSelected(1);
			myGUI->SetSketcher_Object(myCurObject);
			break;
		}
	}
}

/**
* \fn RedrawAll()
* \brief erase and redraw all objects from object list
* \return void
*/
void Sketcher::RedrawAll()
{
	for (Standard_Integer i = 1; i <= myData->Length(); i++)
	{
		myCurObject = Handle(Sketcher_Object)::DownCast(myData->Value(i));
        myContext->Display(myCurObject->GetAIS_Object(),1);
	}
}

/**
* \fn SetPolylineMode(Standard_Boolean mode)
* \brief set polyline mode
* \return void
* \param amode Standard_Boolean
*/
void Sketcher::SetPolylineMode(Standard_Boolean amode)
{
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		CurCommand->SetPolylineMode(amode);
	}
	PolylineFirstPointExist = Standard_False;
}

/**
* \fn SetSnap(Sketcher_SnapType theSnap)
* \brief set current snap type
* \return void
* \param theSnap Sketcher_SnapType
*/
void Sketcher::SetSnap(Sketcher_SnapType theSnap)
{
	myAnalyserSnap->SetSnapType(theSnap);
}

/**
* \fn GetSnap()
* \brief get current snap type
* \return Sketcher_SnapType
*/
Sketcher_SnapType Sketcher::GetSnap()
{
	return myAnalyserSnap->GetSnapType();
}

/**
* \fn ProjectPointOnPlane(const Standard_Real &v3dX,const Standard_Real &v3dY,const Standard_Real &v3dZ,const Standard_Real& projVx,const Standard_Real& projVy,const Standard_Real& projVz)
* \brief calculate 2d point on current plane
* \return Standard_Boolean
* \param v3dX const Standard_Real&
* \param v3dY const Standard_Real&
* \param v3dZ const Standard_Real&
* \param projVx const Standard_Real&
* \param projVy const Standard_Real&
* \param projVz const Standard_Real&
*/
Standard_Boolean Sketcher::ProjectPointOnPlane(const Standard_Real &v3dX, const Standard_Real &v3dY, const Standard_Real &v3dZ,
    const Standard_Real& projVx, const Standard_Real& projVy, const Standard_Real& projVz)
{
	myTempPnt.SetCoord(v3dX, v3dY, v3dZ);
	myCurrentDir.SetCoord(projVx, projVy, projVz);

	myCurrentLine->SetDirection(myCurrentDir);
	myCurrentLine->SetLocation(myTempPnt);

	myIntCS.Perform(myCurrentLine, myCurrentPlane);
	if (myIntCS.NbPoints() >= 1)
	{
		myTempPnt = myIntCS.Point(1);
		myCurrentPnt2d.SetX((myTempPnt.X() - myCoordinateSystem.Location().X())*myCoordinateSystem.XDirection().X() + (myTempPnt.Y() - myCoordinateSystem.Location().Y())*myCoordinateSystem.XDirection().Y() + (myTempPnt.Z() - myCoordinateSystem.Location().Z())*myCoordinateSystem.XDirection().Z());
		myCurrentPnt2d.SetY((myTempPnt.X() - myCoordinateSystem.Location().X())*myCoordinateSystem.YDirection().X() + (myTempPnt.Y() - myCoordinateSystem.Location().Y())*myCoordinateSystem.YDirection().Y() + (myTempPnt.Z() - myCoordinateSystem.Location().Z())*myCoordinateSystem.YDirection().Z());
		return Standard_True;
	}
	else return Standard_False;
}

/**
* \fn addCommand(Handle(Sketcher_Command) theCommand)
* \brief add theCommand to command list
* \return void
* \param theCommand Handle(Sketcher_Command)
*/
void Sketcher::addCommand(Handle(Sketcher_Command) theCommand)
{
	theCommand->SetData(myData);
	theCommand->SetContext(myContext);
	theCommand->SetAnalyserSnap(myAnalyserSnap);

	theCommand->SetAx3(myCoordinateSystem);
	myCommands->Append(theCommand);
}


/**
* \fn SelectCurCommand()
* \brief get command from command list
* \return void
*/
void Sketcher::SelectCurCommand()
{
	for (Standard_Integer i = 1; i <= myCommands->Length(); i++)
	{
		CurCommand = Handle(Sketcher_Command)::DownCast(myCommands->Value(i));
		if (CurCommand->GetTypeOfMethod() == myCurrentMethod)
			break;
	}
}
