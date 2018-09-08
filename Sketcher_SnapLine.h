#ifndef Sketcher_SnapLine_H
#define Sketcher_SnapLine_H Sketcher_SnapLine_H

#include "Sketcher_Snap.h"

#include <gp_Pnt2d.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Lin.hxx>
#include <gce_MakeDir2d.hxx>
#include <Geom2d_Line.hxx>

class gp_Dir2d;
class Geom2d_Line;

class Sketcher_SnapLine;
DEFINE_STANDARD_HANDLE(Sketcher_SnapLine, Sketcher_Snap)

//base class of snaps searching parallel/perpendicular lines
class Sketcher_SnapLine : public Sketcher_Snap
{
public:
	/**
	* \fn Sketcher_SnapLine()
	* \brief Constructs a Sketcher_SnapLine
	*/
	Sketcher_SnapLine();

	/**
	* \fn ~Sketcher_SnapLine()
	* \brief Destructor
	*/
	~Sketcher_SnapLine();

	/**
	* \fn SelectEvent()
	* \brief find new point
	* \return void
	*/
	virtual void SelectEvent() = 0;

	/**
	* \fn GetSnapType()
	* \brief get Snap type
	* \return Sketcher_SnapType
	*/
	virtual	Sketcher_SnapType GetSnapType() = 0;

	/**
	* \fn DrawRelation()
	* \brief draw relation
	* \return void
	*/
	virtual void DrawRelation() = 0;

	/**
	* \fn EraseRelation()
	* \brief erase relation
	* \return void
	*/
	virtual void EraseRelation() = 0;

	/**
	* \fn setFirstPnt(const gp_Pnt2d& p)
	* \brief set point for exceptions
	* \return void
	* \param p const gp_Pnt2d&
	*/
	void setFirstPnt(const gp_Pnt2d& p);

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapLine, Sketcher_Snap)

protected:

	//methods

	/**
	* \fn SelectNearest()
	* \brief select nearest line
	* \return void
	*/
	void SelectNearest();

	/**
	* \fn checkparallel()
	* \brief check lines for parallel
	* \return void
	*/
	void checkparallel();

	/**
	* \fn ProjectPoint()
	* \brief find point projected to line
	* \return Standard_Boolean
	*/
	Standard_Boolean ProjectPoint();

	/**
	* \fn ProjectPoint()
	* \brief set Edges to display relation
	* \return Standard_Boolean
	*/
	void setEdges();

	//members

	Standard_Real			minAngle;
	Standard_Real			curAngle;

	gp_Pnt2d				nearestPnt2d;
	gp_Dir2d				curDir2d;
	gp_Dir2d				tempDir2d;
	Handle(Geom2d_Line)		curGeom2d_Line;
	Handle(Geom2d_Line)		tempGeom2d_Line;
	gp_Lin					mygp_Lin1, mygp_Lin2;

};

#endif