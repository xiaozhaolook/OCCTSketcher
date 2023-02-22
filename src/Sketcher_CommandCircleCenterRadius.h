#ifndef Sketcher_CommandCIRCLECENTERRADIUS_H
#define Sketcher_CommandCIRCLECENTERRADIUS_H 

#include "Sketcher_Command.h"

#include <Geom2d_CartesianPoint.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Circle.hxx>
#include <AIS_Circle.hxx>
#include <gp_Ax2d.hxx>

class Geom_Circle;
class AIS_Circle;
class AIS_Line;

class Sketcher_CommandCircleCenterRadius;
DEFINE_STANDARD_HANDLE(Sketcher_CommandCircleCenterRadius, Sketcher_Command)

//Command entering Circle by Center point and other point
class Sketcher_CommandCircleCenterRadius : public Sketcher_Command
{
public:

	enum	CircleCenterRadiusAction { Nothing, Input_CenterPoint, Input_RadiusPoint };

	/**
	* \fn Sketcher_CommandCircleCenterRadius()
	* \brief Constructs a Sketcher_CommandCircleCenterRadius
	*/
	Sketcher_CommandCircleCenterRadius();

	/**
	* \fn ~Sketcher_CommandCircleCenterRadius()
	* \brief destructor
	*/
	~Sketcher_CommandCircleCenterRadius();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_CommandCircleCenterRadius, Sketcher_Command)

private:

	//members
	CircleCenterRadiusAction		myCircleCenterRadiusAction;
	Standard_Real					radius;

	Handle(Geom_Circle)				tempGeom_Circle;
	Handle(AIS_Circle)				myRubberCircle;
	gp_Ax2d							myCircleAx2d;
};

#endif