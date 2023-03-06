#include "Sketcher_Snap.h"
#include <Geom2d_Circle.hxx>

class Geom2d_Circle;

class Sketcher_SnapCenter;
DEFINE_STANDARD_HANDLE(Sketcher_SnapCenter, Sketcher_Snap)

//snap searching center curve/circle/arc
class Sketcher_SnapCenter : public Sketcher_Snap
{
public:
	
	/**
	* \fn Sketcher_SnapCenter()
	* \brief Constructs a Sketcher_SnapCenter
	*/
	Sketcher_SnapCenter();

	/**
	* \fn ~Sketcher_SnapCenter()
	* \brief Destructor
	*/
	~Sketcher_SnapCenter();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapCenter, Sketcher_Snap)

private:

	Handle(Geom2d_Circle)								curGeom2d_Circle;

};