#ifndef Sketcher_CommandTrim_H
#define Sketcher_CommandTrim_H Sketcher_CommandTrim_H

#include "Sketcher_Command.h"
#include "Geom2d_Edge.h"
#include "Geom2d_Arc.h"

#include <gp_Circ2d.hxx>
#include <gp_Circ.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Circle.hxx>

#include <AIS_Circle.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <Geom2dGcc_Circ2d3Tan.hxx>


#define  TRIMDISTANCETOCURVE 40

class AIS_Circle;
class Sketcher_CommandTrim;
DEFINE_STANDARD_HANDLE(Sketcher_CommandTrim, Sketcher_Command)

//Command for trim objects
class Sketcher_CommandTrim : public Sketcher_Command
{
public:

	enum	TrimAction  { NothingAction, TrimObject };
	enum	RedrawState	{ NothingRedraw, RedrawTrimmedObject, OneObjectRemove, TwoObjectRemove };

	/**
	* \fn Sketcher_CommandTrim()
	* \brief Constructs a Sketcher_CommandTrim
	*/
	Sketcher_CommandTrim();

	/**
	* \fn ~Sketcher_CommandTrim()
	* \brief destructor
	*/
	~Sketcher_CommandTrim();

	/**
	* \fn Action()
	* \brief turn command to active state
	*/
	void Action();

	/**
	* \fn MouseInputEvent(const gp_Pnt2d& thePnt2d )
	* \brief input event handler
	* \return Standard_Boolean
	* \param thePnt2d const gp_Pnt2d&
	*/
	Standard_Boolean MouseInputEvent(const gp_Pnt2d& thePnt2d);

	/**
	* \fn MouseMoveEvent(const gp_Pnt2d& thePnt2d )
	* \brief mouse move handler
	* \return void
	* \param thePnt2d const gp_Pnt2d&
	*/
	void MouseMoveEvent(const gp_Pnt2d& thePnt2d);

	/**
	* \fn CancelEvent()
	* \brief cancel event handler, stop entering object
	* \return void
	*/
	void CancelEvent();

	/**
	* \fn GetTypeOfMethod()
	* \brief get command Method
	* \return Sketcher_ObjectTypeOfMethod
	*/
	Sketcher_ObjectTypeOfMethod GetTypeOfMethod();

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_CommandTrim, Sketcher_Command)

private:

	// methods

	/**
	* \fn StandardEvent()
	* \brief input event and mouse move handler
	* \return void
	*/
	void StandardEvent();

	/**
	* \fn SelectCurve()
	* \brief select nearest curve
	* \return void
	*/
	void SelectNearestCurve();

	/**
	* \fn FixObjectPoints()
	* \brief find intersection points
	* \return void
	*/
	void FixObjectPoints();

	/**
	* \fn TrimCurve()
	* \brief manager of cutting curve
	* \return void
	*/
	void TrimCurve();

	/**
	* \fn PointProjected(Standard_Integer index )
	* \brief find nearest point
	* \return Standard_Boolean
	* \param index const Standard_Integer
	*/
	Standard_Boolean PointProjected(Standard_Integer index);

	/**
	* \fn SetParam()
	* \brief compute intersection point parameter
	* \return void
	*/
	void SetParam();

	/**
	* \fn AddParam()
	* \brief add parameter to sequence
	* \return void
	*/
	void AddParam();

	/**
	* \fn FindSegment()
	* \brief determine part of curve, that has been cutting
	* \return void
	*/
	void FindSegment();

	/**
	* \fn Redraw()
	* \brief redraw object, if it's necessary
	* \return Standard_Boolean
	*/
	Standard_Boolean Redraw();

	/**
	* \fn RedrawOld()
	* \brief draw erased object
	* \return void
	*/
	void RedrawOld();

	/**
	* \fn DelTrimmedObject()
	* \brief remove object from list of objects, erase object
	* \return void
	*/
	void DelTrimmedObject();

	/**
	* \fn EditLine(Standard_Real u1,Standard_Real u2)
	* \brief edit line by 2 parameters
	* \return void
	* \param u1 Standard_Real
	* \param u2 Standard_Real
	*/
	void EditLine(Standard_Real u1, Standard_Real u2);

	/**
	* \fn AddNewLine(Standard_Real u1,Standard_Real u2)
	* \brief Constructs a new line by 2 parameters
	* \return void
	* \param u1 Standard_Real
	* \param u2 Standard_Real
	*/
	void AddNewLine(Standard_Real u1, Standard_Real u2);

	/**
	* \fn EditCircle()
	* \brief Constructs a arc from circle by 2 parameters
	* \return void
	*/
	void EditCircle();

	/**
	* \fn EditArc(Standard_Real u1,Standard_Real u2)
	* \brief edit arc by 2 parameters
	* \return void
	* \param u1 Standard_Real
	* \param u2 Standard_Real
	*/
	void EditArc(Standard_Real u1, Standard_Real u2);

	/**
	* \fn AddNewArc(Standard_Real u1,Standard_Real u2)
	* \brief Constructs a new arc by 2 parameters
	* \return void
	* \param u1 Standard_Real
	* \param u2 Standard_Real
	*/
	void AddNewArc(Standard_Real u1, Standard_Real u2);


	//members

	TrimAction							myTrimAction;

	Handle(Sketcher_Object)				mySObject;
	Sketcher_ObjectGeometryType			TypeofObject;
	TCollection_ExtendedString			TrimName;
	Standard_Integer					curCurveIndex;
	Standard_Integer					NearestCurveIndex;

	Geom2dAPI_ProjectPointOnCurve		myProjectOnCurve;
	Geom2dAPI_InterCurveCurve			my2dAPI_InterCurveCurve;
	Handle(Geom2d_Edge)					curGeom2d_Edge;
	Handle(Geom2d_Arc)					curGeom2d_Arc;
	Handle(Geom2d_Circle)				curGeom2d_Circle;
	Handle(Geom2d_Curve)				nearestGeom2d_Curve;
	Handle(Geom2d_Line)					temp1Geom2d_Line;
	Handle(Geom2d_Line)					temp2Geom2d_Line;

	Standard_Real						minDistance;
	Standard_Real						curDistance;
	Standard_Real						NearestPntU;
	Standard_Real						tempU, FirstU, SecondU;

	gp_Pnt2d							tempPnt2d;
	gp_Pnt2d							mySecondgp_Pnt2d;
	gp_Circ2d							nearestgp_Circ2d;

	Standard_Boolean					isInputMouse;
	Standard_Boolean					RedrawFlag;

	TColStd_SequenceOfReal 				mySeqOfPntU;

	RedrawState							myRedrawState;
	Handle(AIS_InteractiveObject)		curTrimmedObj;
	Handle(AIS_InteractiveObject)		newTrimmedObj;
	Handle(AIS_InteractiveObject)		FirstObj;
	Handle(AIS_InteractiveObject)		SecondObj;
	Standard_Real						curFirstObjParam_Start;
	Standard_Real						curFirstObjParam_End;
	Standard_Real						newFirstObjParam_Start;
	Standard_Real						newFirstObjParam_End;
	Standard_Real						curSecondObjParam_Start;
	Standard_Real						curSecondObjParam_End;
	Standard_Real						newSecondObjParam_Start;
	Standard_Real						newSecondObjParam_End;

};

#endif