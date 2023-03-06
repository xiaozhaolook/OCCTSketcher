#ifndef Sketcher_CommandCircle3Tan_H
#define Sketcher_CommandCircle3Tan_H 

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
#include <Geom2dGcc_Circ2d3Tan.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

#define  MINIMUMDISTANCETOCURVE 100

class AIS_Circle;

class Sketcher_CommandCircle3Tan;
DEFINE_STANDARD_HANDLE(Sketcher_CommandCircle3Tan, Sketcher_Command)

//Command entering Circle by 3 tangential to curve
class Sketcher_CommandCircle3Tan : public Sketcher_Command
{
public:

	enum	Circle3TanAction { Nothing, Input_1CircleTan, Input_2CircleTan, Input_3CircleTan };

	/**
	* \fn Sketcher_CommandCircle3Tan()
	* \brief Constructs a Sketcher_CommandCircle3Tan
	*/
	Sketcher_CommandCircle3Tan();

	/**
	* \fn ~Sketcher_CommandCircle3Tan()
	* \brief destructor
	*/
	~Sketcher_CommandCircle3Tan();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_CommandCircle3Tan, Sketcher_Command)

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

	/**
	* \fn CheckgpObject()
	* \brief check object, is it possible to create tangent circle
	* \return Standard_Boolean
	*/
	Standard_Boolean CheckgpObject();

	/**
	* \fn StoregpObject()
	* \brief store objects for building tangent circle
	* \return Standard_Boolean
	*/
	Standard_Boolean StoregpObject();

	//members
	Circle3TanAction				myCircle3TanAction;
	Handle(Sketcher_Object)			mySObject;

	Standard_Real					minDistance;
	Standard_Real					curDistance;
	Standard_Real					u1, u2, u_temp;
	gp_Pnt2d						tempPnt2d;
	gp_Pnt2d						mySecondgp_Pnt2d;

	gp_Circ2d						temp_Circ2d;
	gp_Circ							best_Circ;
	Handle(AIS_Circle)				myRubberCircle;

	Handle(Geom2d_Circle)			tempGeom2d_Circle;
	Handle(Geom2d_Curve)			tempGeom2d_Curve;

	Handle(Geom2d_Curve)			myFirst2d_Curve;
	Handle(Geom2d_Curve)			mySecond2d_Curve;
	Handle(Geom_Circle)				tempGeom_Circle;


	Standard_Boolean				gp_lin1Exist, gp_lin2Exist;
	Standard_Boolean				gp_circ1Exist, gp_circ2Exist;
	gp_Lin2d						gp_lin1, gp_lin2;
	gp_Circ2d						gp_circ1, gp_circ2;

	Geom2dAPI_ProjectPointOnCurve	myProjectOnCurve;

};

#endif