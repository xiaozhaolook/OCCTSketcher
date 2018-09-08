#ifndef Sketcher_SnapMIDDLE_H
#define Sketcher_SnapMIDDLE_H Sketcher_SnapMIDDLE_H

#include "Sketcher_Snap.h"
#include "Geom2d_Edge.h"
#include "Geom2d_Arc.h"

class Sketcher_SnapMiddle;
DEFINE_STANDARD_HANDLE(Sketcher_SnapMiddle, Sketcher_Snap)

//snap searching middle points of line/arc
class Sketcher_SnapMiddle : public Sketcher_Snap
{
public:

	/**
	* \fn Sketcher_SnapMiddle()
	* \brief Constructs a Sketcher_SnapMiddle
	*/
	Sketcher_SnapMiddle();

	/**
	* \fn ~Sketcher_SnapMiddle()
	* \brief Destructor
	*/
	~Sketcher_SnapMiddle();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapMiddle, Sketcher_Snap)

private:

	Handle(Geom2d_Edge)	curGeom2d_Edge;
	Handle(Geom2d_Arc)	curGeom2d_Arc;

};

#endif