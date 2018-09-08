#ifndef Sketcher_SnapIntersection_H
#define Sketcher_SnapIntersection_H Sketcher_SnapIntersection_H

#include "Sketcher_Snap.h"
#include "Geom2d_Edge.h"

#include <Geom2d_Line.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <GeomAPI.hxx>

class Geom2d_Curve;

class Sketcher_SnapIntersection;
DEFINE_STANDARD_HANDLE(Sketcher_SnapIntersection, Sketcher_Snap)

//snap searching intersection point of objects
class Sketcher_SnapIntersection : public Sketcher_Snap
{
public:
	/**
	* \fn Sketcher_SnapIntersection()
	* \brief Constructs a Sketcher_SnapIntersection
	*/
	Sketcher_SnapIntersection();

	/**
	* \fn ~Sketcher_SnapIntersection()
	* \brief Destructor
	*/
	~Sketcher_SnapIntersection();

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

	/**
	* \fn DrawRelation()
	* \brief draw relation
	* \return void
	*/
	virtual void DrawRelation();

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapIntersection, Sketcher_Snap)

private:

	//method

	/**
	* \fn findSecondObject(Standard_Integer start)
	* \brief find intersection points for object with start index
	* \return void
	* \param start Standard_Integer
	*/
	void findSecondObject(Standard_Integer start);

	//members

	Handle(Sketcher_Object)		secondSObject;
	Handle(Geom2d_Curve)		cur1Geom2d_Curve;
	Handle(Geom2d_Curve)		cur2Geom2d_Curve;
	Handle(Geom2d_Edge)			cur1Geom2d_Edge;
	Handle(Geom2d_Edge)			cur2Geom2d_Edge;
	Handle(Geom2d_Line)			cur1Geom2d_Line;
	Handle(Geom2d_Line)			cur2Geom2d_Line;

	Standard_Real				bpu;
	Geom2dAPI_InterCurveCurve	my2dAPI_InterCurveCurve;

	Handle(AIS_InteractiveObject)	curHilightedObj2;
};

#endif