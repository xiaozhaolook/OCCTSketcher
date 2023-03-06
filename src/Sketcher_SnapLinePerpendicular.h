#ifndef Sketcher_SnapLinePerpendicular_H
#define Sketcher_SnapLinePerpendicular_H

#include "Sketcher_SnapLine.h"
#include <AIS_PerpendicularRelation.hxx>

class Sketcher_SnapLinePerpendicular;
DEFINE_STANDARD_HANDLE(Sketcher_SnapLinePerpendicular, Sketcher_SnapLine)

//snap searching perpendicular lines
class Sketcher_SnapLinePerpendicular : public Sketcher_SnapLine
{
public:

	/**
	* \fn Sketcher_SnapLinePerpendicular()
	* \brief Constructs a Sketcher_SnapLinePerpendicular
	*/
	Sketcher_SnapLinePerpendicular();

	/**
	* \fn ~Sketcher_SnapLinePerpendicular()
	* \brief Destructor
	*/
	~Sketcher_SnapLinePerpendicular();

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
	void DrawRelation();

	/**
	* \fn EraseRelation()
	* \brief erase relation
	* \return void
	*/
	void EraseRelation();

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapLinePerpendicular, Sketcher_SnapLine)

private:

	Handle(AIS_PerpendicularRelation) myPerRelation;

};

#endif