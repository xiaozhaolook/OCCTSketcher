#ifndef Sketcher_CommandLine2P_H
#define Sketcher_CommandLine2P_H 

#include "Sketcher_Command.h"
#include "Geom2d_Edge.h"

class Geom2d_CartesianPoint;
class AIS_Line;

class Sketcher_CommandLine2P;
DEFINE_STANDARD_HANDLE(Sketcher_CommandLine2P, Sketcher_Command)

//Command entering Line by 2 Points
class Sketcher_CommandLine2P : public Sketcher_Command
{
public:

	enum	Line2PAction { Nothing, Input_FirstPointLine, Input_SecondPointLine };


	/**
	* \fn Sketcher_CommandLine2P()
	* \brief Constructs a Sketcher_CommandLine2P
	*/
	Sketcher_CommandLine2P();

	/**
	* \fn ~Sketcher_CommandLine2P()
	* \brief destructor
	*/
	~Sketcher_CommandLine2P();

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

	/**
	* \fn SetPolylineFirstPnt(const gp_Pnt2d& p1)
	* \brief set last entering gp_Pnt2d for polyline
	* \return void
	* \param p1 const gp_Pnt2d&
	*/
	virtual void SetPolylineFirstPnt(const gp_Pnt2d& p1);

	/**
	* \fn GetPolylineFirstPnt(gp_Pnt2d& p1)
	* \brief get last entering gp_Pnt2d for polyline
	* \return Standard_Boolean
	* \param p1 gp_Pnt2d&
	*/
	virtual Standard_Boolean GetPolylineFirstPnt(gp_Pnt2d& p1);

	/**
	* \fn SetPolylineMode(Standard_Boolean mode)
	* \brief set polyline mode
	* \return void
	* \param mode Standard_Boolean
	*/
	void SetPolylineMode(Standard_Boolean mode);

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_CommandLine2P, Sketcher_Command)

private:
	//members

	Line2PAction myLine2PAction;

};

#endif