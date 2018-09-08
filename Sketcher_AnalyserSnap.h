#ifndef SKETCHER_ANALYSERSNAP_H
#define SKETCHER_ANALYSERSNAP_H SKETCHER_ANALYSERSNAP_H

#include <Standard_Macro.hxx>
#include <MMgt_TShared.hxx>
#include <Standard_DefineHandle.hxx>

#include "Sketcher_Object.h"
#include "Sketcher_Snap.h"

#include "Sketcher_SnapEnd.h"
#include "Sketcher_SnapMiddle.h"
#include "Sketcher_SnapCenter.h"
#include "Sketcher_SnapNearest.h"
#include "Sketcher_SnapIntersection.h"
#include "Sketcher_SnapLineParallel.h"
#include "Sketcher_SnapLinePerpendicular.h"
#include "Sketcher_SnapTangent.h"

#include <TColStd_HSequenceOfTransient.hxx>
#include <AIS_InteractiveContext.hxx>

#include <TColgp_SequenceOfPnt2d.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <TColStd_SequenceOfInteger.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Ax3.hxx>

class Sketcher_AnalyserSnap;
DEFINE_STANDARD_HANDLE(Sketcher_AnalyserSnap, MMgt_TShared)

//Snap Manager class 
class Sketcher_AnalyserSnap : public MMgt_TShared
{
public:

	/**
	* \fn Sketcher_AnalyserSnap(Handle(AIS_InteractiveContext)& theContext,Handle(TColStd_HSequenceOfTransient)& thedata,gp_Ax3 &theAx3)
	* \brief Constructs a Sketcher_AnalyserSnap
	* \param theContext Handle(AIS_InteractiveContext)&
	* \param thedata Handle(TColStd_HSequenceOfTransient)&
	* \param theAx3 gp_Ax3&
	*/
	Sketcher_AnalyserSnap(Handle(AIS_InteractiveContext)& theContext, Handle(TColStd_HSequenceOfTransient)& thedata, gp_Ax3 & theAx3);

	/**
	* \fn ~Sketcher_AnalyserSnap()
	* \brief destructor
	*/
	~Sketcher_AnalyserSnap();

	/**
	* \fn SetContext(Handle(AIS_InteractiveContext)& theContext)
	* \brief set context
	* \return void
	* \param theContext Handle(AIS_InteractiveContext)&
	*/
	void SetContext(Handle(AIS_InteractiveContext)& theContext);

	/**
	* \fn SetData(Handle(TColStd_HSequenceOfTransient)& thedata)
	* \brief set list of objects
	* \return void
	* \param thedata TColStd_HSequenceOfTransient)&
	*/
	void SetData(Handle(TColStd_HSequenceOfTransient)& thedata);

	/**
	* \fn SetAx3(const gp_Ax3& theAx3)
	* \brief set coordinate system
	* \return void
	* \param theAx3 const gp_Ax3&
	*/
	void SetAx3(const gp_Ax3 &theAx3);

	/**
	* \fn SetMinDistance(const Standard_Real& aPrecise)
	* \brief set precise for snap
	* \return void
	* \param aPrecise const Standard_Real&
	*/
	void SetMinDistance(const Standard_Real& aPrecise);

	/**
	* \fn SetSnapType(Sketcher_SnapType theSnap)
	* \brief set current snap type
	* \return void
	* \param theSnap Sketcher_SnapType
	*/
	void SetSnapType(Sketcher_SnapType theSnap);

	/**
	* \fn GetSnapType()
	* \brief get current snap type
	* \return Sketcher_SnapType
	*/
	Sketcher_SnapType GetSnapType();

	/**
	* \fn MouseInput(const gp_Pnt2d& thePnt2d)
	* \brief input event handler
	* \return gp_Pnt2d
	* \param thePnt2d const gp_Pnt2d&
	*/
	gp_Pnt2d MouseInput(const gp_Pnt2d& thePnt2d);

	/**
	* \fn MouseMove(const gp_Pnt2d& thePnt2d)
	* \brief mouse move handler
	* \return gp_Pnt2d
	* \param thePnt2d const gp_Pnt2d&
	*/
	gp_Pnt2d MouseMove(const gp_Pnt2d& thePnt2d);

	/**
	* \fn Cancel()
	* \brief cancel event handler
	* \return void
	*/
	void Cancel();

	/**
	* \fn MouseInputException(const gp_Pnt2d& p1, const gp_Pnt2d& thePnt2d, TangentType CType, Standard_Boolean TangentOnly)
	* \brief input event exception handler
	* \return gp_Pnt2d
	* \param p1 const gp_Pnt2d&
	* \param thePnt2d const gp_Pnt2d&
	* \param CType TangentType
	* \param TangentOnly Standard_Boolean
	*/
	gp_Pnt2d MouseInputException(const gp_Pnt2d& p1, const gp_Pnt2d& thePnt2d, TangentType CType, Standard_Boolean TangentOnly);

	/**
	* \fn MouseMoveException(const gp_Pnt2d& p1, const gp_Pnt2d& thePnt2d, TangentType CType, Standard_Boolean TangentOnly)
	* \brief mouse move exception handler
	* \return gp_Pnt2d
	* \param p1 const gp_Pnt2d&
	* \param thePnt2d const gp_Pnt2d&
	* \param CType TangentType
	* \param TangentOnly Standard_Boolean
	*/
	gp_Pnt2d MouseMoveException(const gp_Pnt2d& p1, const gp_Pnt2d& thePnt2d, TangentType CType, Standard_Boolean TangentOnly);

	// Type management
	DEFINE_STANDARD_RTTIEXT(Sketcher_AnalyserSnap, MMgt_TShared)

private:
	//methods

	/**
	* \fn SnapAnalyserEvent()
	* \brief search best point among all possible snaps
	* \return void
	*/
	void SnapAnalyserEvent();

	/**
	* \fn AddPoints(const Standard_Real& factor)
	* \brief add point to sequence
	* \return void
	* \param factor const Standard_Real&
	*/
	void AddPoints(const Standard_Real& factor);

	/**
	* \fn addSnap(Handle(Sketcher_Snap) theSnap)
	* \brief add theSnap to snap list
	* \return void
	* \param theSnap andle(Sketcher_Snap)
	*/
	void addSnap(Handle(Sketcher_Snap) theSnap);

	/**
	* \fn SelectCurSnap()
	* \brief get snap from snap list
	* \return void
	*/
	void SelectCurSnap();

	//members
	Handle(AIS_InteractiveContext)			myContext;
	Handle(TColStd_HSequenceOfTransient)	data;
	Handle(TColStd_HSequenceOfTransient) 	mySnaps;
	Handle(Sketcher_Snap)					CurSnap;
	Sketcher_SnapType						myCurrentSnap;
	gp_Ax3									curCoordinateSystem;

	gp_Pnt2d								myPnt2d;
	gp_Pnt2d								storedPnt2d;
	TangentType								storedTangentType;
	Standard_Boolean						isTangent;
	Standard_Boolean						isLine;

	TColgp_SequenceOfPnt2d					mySeqOfPnt2d;
	TColStd_SequenceOfReal 					mySeqOfDistance;
	TColStd_SequenceOfReal 					mySeqOfFactor;
	TColStd_SequenceOfInteger				mySnapType;
	Sketcher_SnapType						mySnapAnType;
	Sketcher_SnapType						curSnapAnType;

	Standard_Real							minimumSnapDistance;
	Standard_Real							bestDist;
	Standard_Real							curDist;
};

#endif