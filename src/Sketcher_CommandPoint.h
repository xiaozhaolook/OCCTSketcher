#ifndef Sketcher_CommandPOINT_H
#define Sketcher_CommandPOINT_H Sketcher_CommandPOINT_H

#include "Sketcher_Command.h"
#include <AIS_Point.hxx>

class Sketcher_CommandPoint;
DEFINE_STANDARD_HANDLE(Sketcher_CommandPoint, Sketcher_Command)

//Command entering Point
class Sketcher_CommandPoint : public Sketcher_Command
{
public:

	enum	PointAction { Nothing, Input_Point };

	/**
	* \fn Sketcher_CommandPoint()
	* \brief Constructs a Sketcher_CommandPoint
	*/
	Sketcher_CommandPoint();

	/**
	* \fn ~Sketcher_CommandPoint()
	* \brief destructor
	*/
	~Sketcher_CommandPoint();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_CommandPoint, Sketcher_Command)

private:

	//members
	PointAction		myPointAction;

};

#endif