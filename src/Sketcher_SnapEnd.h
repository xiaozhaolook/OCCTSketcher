#ifndef Sketcher_SnapEnd_H
#define Sketcher_SnapEnd_H

#include "Sketcher_Snap.h"
#include "Geom2d_Edge.h"
#include "Geom2d_Arc.h"

class Sketcher_SnapEnd;
DEFINE_STANDARD_HANDLE(Sketcher_SnapEnd, Sketcher_Snap)

//snap searching end point of line/arc
class Sketcher_SnapEnd : public Sketcher_Snap
{
public:
	
	/**
	* \fn Sketcher_SnapEnd()
	* \brief Constructs a Sketcher_SnapEnd
	*/
	Sketcher_SnapEnd();

	/**
	* \fn ~Sketcher_SnapEnd()
	* \brief Destructor
	*/
	~Sketcher_SnapEnd();

	/**
	* \fn SelectEvent()
	* \brief find new point
	* \return void
	*/
	void SelectEvent();

	/**
	* \fn GetSnapType()
	* \brief get Snap type
	* \return Sketcher_SnapType
	*/
	Sketcher_SnapType GetSnapType();

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapEnd, Sketcher_Snap)

private:

	Handle(Geom2d_Edge)								curGeom2d_Edge;
	Handle(Geom2d_Arc)								curGeom2d_Arc;
};

#endif