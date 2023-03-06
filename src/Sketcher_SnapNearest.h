#ifndef Sketcher_SnapNEAREST_H
#define Sketcher_SnapNEAREST_H

#include "Sketcher_Snap.h"
#include <Geom2d_Curve.hxx>

class Geom2d_Curve;

class Sketcher_SnapNearest;
DEFINE_STANDARD_HANDLE(Sketcher_SnapNearest, Sketcher_Snap)

//snap searching nearest point at line/circle/arc
class Sketcher_SnapNearest : public Sketcher_Snap
{
public:

	/**
	* \fn Sketcher_SnapNearest()
	* \brief Constructs a Sketcher_SnapNearest
	*/
	Sketcher_SnapNearest();

	/**
	* \fn ~Sketcher_SnapNearest()
	* \brief Destructor
	*/
	~Sketcher_SnapNearest();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapNearest, Sketcher_Snap)
private:

	Handle(Geom2d_Curve)	curGeom2d_Curve;

};

#endif