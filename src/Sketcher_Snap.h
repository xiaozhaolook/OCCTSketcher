#ifndef Sketcher_Snap_H
#define Sketcher_Snap_H Sketcher_Snap_H

#include <Standard_Macro.hxx>
#include <Standard_Transient.hxx>
#include <Standard_DefineHandle.hxx>

#include "Sketcher_Object.h"
#include "Sketcher_SnapType.h"

#include <TColStd_HSequenceOfTransient.hxx>
#include <AIS_InteractiveContext.hxx>

#include <gp_Ax3.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Pnt.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <ElCLib.hxx>

#include <Geom_CartesianPoint.hxx>
#include <Geom2d_CartesianPoint.hxx>
#include <AIS_Point.hxx>

#include <Geom_Plane.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

#define MINIMUMSNAP 25
#define	MINANGLE M_PI / 64

class AIS_InteractiveContext;
class AIS_Point;
class Geom_CartesianPoint;
class Geom2dAPI_ProjectPointOnCurve;

class Sketcher_Snap;
DEFINE_STANDARD_HANDLE(Sketcher_Snap, Standard_Transient)

//base class of Snap
class Sketcher_Snap : public Standard_Transient{
public:
	/**
	* \fn Sketcher_Snap()
	* \brief Constructs a Sketcher_Snap
	*/
	Sketcher_Snap();

	/**
	* \fn ~Sketcher_Snap()
	* \brief Destructor
	*/
	~Sketcher_Snap();

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
	* \brief set precise
	* \return void
	* \param aPrecise const Standard_Real&
	*/
	void SetMinDistance(const Standard_Real& aPrecise);

	/**
	* \fn MouseInputEvent(const gp_Pnt2d& thePnt2d)
	* \brief input event handler
	* \return gp_Pnt2d
	* \param thePnt2d const gp_Pnt2d&
	*/
	virtual gp_Pnt2d MouseInputEvent(const gp_Pnt2d& tempPnt2d);

	/**
	* \fn MouseMoveEvent(const gp_Pnt2d& thePnt2d)
	* \brief mouse move handler
	* \return gp_Pnt2d
	* \param thePnt2d const gp_Pnt2d&
	*/
	gp_Pnt2d MouseMoveEvent(const gp_Pnt2d& tempPnt2d);

	/**
	* \fn EraseSnap()
	* \brief cancel event handler
	* \return void
	*/
	virtual void EraseSnap();

	/**
	* \fn AnalyserEvent(const gp_Pnt2d& tempPnt2d, gp_Pnt2d& newPnt2d,Standard_Real& dist,Standard_Integer& type)
	* \brief get new point, minimum distance, snap type
	* \return Standard_Boolean
	* \param tempPnt2d const gp_Pnt2d&
	* \param newPnt2d const gp_Pnt2d&
	* \param dist Standard_Real&
	* \param type Standard_Integer&
	*/
	Standard_Boolean AnalyserEvent(const gp_Pnt2d& tempPnt2d, gp_Pnt2d& newPnt2d, Standard_Real& dist, Standard_Integer& type);

	/**
	* \fn SelectEvent()
	* \brief find new point
	* \return void
	*/
	virtual	void SelectEvent() = 0;

	/**
	* \fn GetSnapType()
	* \brief get Snap type
	* \return Sketcher_SnapType
	*/
	virtual Sketcher_SnapType GetSnapType() = 0;
	/**
	* \fn DrawRelation()
	* \brief draw relation
	* \return void
	*/
	virtual void DrawRelation();

	/**
	* \fn EraseRelation()
	* \brief erase relation
	* \return void
	*/
	virtual void EraseRelation();

	/**
	* \fn setFirstPnt(const gp_Pnt2d& p)
	* \brief set point for exceptions
	* \return void
	* \param p const gp_Pnt2d&
	*/
	virtual void setFirstPnt(const gp_Pnt2d& p);

	/**
	* \fn setFirstPnt(const gp_Pnt2d& p)
	* \brief set point and tangent type for exceptions
	* \return void
	* \param p const gp_Pnt2d&
	* \param ttype TangentType
	*/
	virtual void setFirstPnt(const gp_Pnt2d& p, TangentType ttype);

    DEFINE_STANDARD_RTTIEXT(Sketcher_Snap, Standard_Transient)

protected:
	/**
	* \fn countProject()
	* \brief find point projected on curve
	* \return Standard_Boolean
	*/
	Standard_Boolean countProject();

	/**
	* \fn count()
	* \brief check distance to point
	* \return Standard_Boolean
	*/
	Standard_Boolean count();

	//members

	Handle(TColStd_HSequenceOfTransient)	data;
	Handle(AIS_InteractiveContext)			myContext;
	gp_Ax3									curCoordinateSystem;
	Handle(Sketcher_Object)					mySObject;
	Sketcher_ObjectGeometryType				myGeometryType;

	Standard_Boolean						firstDisplay;
	Handle(Geom_CartesianPoint)				myGeom_Point;
	Handle(AIS_Point)						myAIS_Point;
	Handle(AIS_InteractiveObject)			curHilightedObj;

	gp_Pnt2d								curPnt2d;
	gp_Pnt2d								objectPnt2d;
	gp_Pnt2d								bestPnt2d;
	Standard_Boolean						findbestPnt2d;

	Handle(Geom2d_CartesianPoint)			curGeom2d_Point;
	Standard_Real							minimumSnapDistance;
	Standard_Real							minDistance;
	Standard_Real							curDistance;
	Geom2dAPI_ProjectPointOnCurve			ProjectOnCurve;

	Handle(Geom_Plane)						myPlane;
	TopoDS_Edge								FirstEdge;
	TopoDS_Edge								SecondEdge;
};

#endif
