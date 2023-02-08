#ifndef Sketcher_SnapLineParallel_H
#define Sketcher_SnapLineParallel_H Sketcher_SnapLineParallel_H

#include "Sketcher_SnapLine.h"
#include <AIS_ParallelRelation.hxx>

class Sketcher_SnapLineParallel;
DEFINE_STANDARD_HANDLE(Sketcher_SnapLineParallel, Sketcher_SnapLine)

//snap searching parallel lines
class Sketcher_SnapLineParallel : public Sketcher_SnapLine
{
public:

	/**
	* \fn Sketcher_SnapLineParallel()
	* \brief Constructs a Sketcher_SnapLineParallel
	*/
	Sketcher_SnapLineParallel();

	/**
	* \fn ~Sketcher_SnapLineParallel()
	* \brief Destructor
	*/
	~Sketcher_SnapLineParallel();

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
	DEFINE_STANDARD_RTTIEXT(Sketcher_SnapLineParallel, Sketcher_SnapLine)

private:

	Handle(AIS_ParallelRelation) myParRelation;
};
#endif