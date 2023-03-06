#ifndef Sketcher_CommandCircle2PTan_H
#define Sketcher_CommandCircle2PTan_H 

#include "Sketcher_Command.h"
#include "Geom2d_Edge.h"
#include "Geom2d_Arc.h"

#include <gp_Circ2d.hxx>
#include <gp_Circ.hxx>
#include <Geom2d_CartesianPoint.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Circle.hxx>

#include <AIS_Circle.hxx>
#include <Geom2dGcc_Circ2d3Tan.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

#define  MINIMUMDISTANCETOCURVE 100

class AIS_Circle;

class Sketcher_CommandCircle2PTan;
DEFINE_STANDARD_HANDLE(Sketcher_CommandCircle2PTan, Sketcher_Command)

//Command entering Circle by 2 Point & 1 tangential to curve
class Sketcher_CommandCircle2PTan : public Sketcher_Command
{
public:

	enum	Circle2PTanAction { Nothing, Input_1CirclePoint, Input_2CirclePoint, Input_3CircleTan };

	/**
	* \fn Sketcher_CommandCircle2PTan()
	* \brief Constructs a Sketcher_CommandCircle2PTan
	*/
	Sketcher_CommandCircle2PTan();

	/**
	* \fn ~Sketcher_CommandCircle2PTan()
	* \brief destructor
	*/
	~Sketcher_CommandCircle2PTan();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_CommandCircle2PTan, Sketcher_Command)

private:

	//methods

	/**
	* \fn SelectCurve()
	* \brief selecy nearest curve
	* \return void
	*/
	void SelectCurve();

	/**
	* \fn SumDistanceToCircle()
	* \brief select circle orientation
	* \return Standard_Boolean
	*/
	Standard_Boolean SumDistanceToCircle();

	//members

	Circle2PTanAction				myCircle2PTanAction;
	Handle(Sketcher_Object)			mySObject;

	Standard_Real					minDistance;
	Standard_Real					curDistance;
	Standard_Real					u_temp;

	gp_Pnt2d						tempPnt2d;
	Handle(Geom2d_CartesianPoint)	First2dPoint;
	Handle(Geom2d_CartesianPoint)	Second2dPoint;


	gp_Circ2d						temp_Circ2d;
	gp_Circ							best_Circ;

	Handle(AIS_Circle)				myRubberCircle;

	Handle(Geom2d_Line)				tempGeom2d_Line;
	Handle(Geom2d_Circle)			tempGeom2d_Circle;
	Handle(Geom2d_Curve)			tempGeom2d_Curve;

	Handle(Geom_Circle)				tempGeom_Circle;

	Geom2dAPI_ProjectPointOnCurve	myProjectOnCurve;

};

#endif