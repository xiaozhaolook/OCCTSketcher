#ifndef Sketcher_Object_H
#define Sketcher_Object_H

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//#include <Standard_Transient.hxx>
#include <Standard_Transient.hxx>
#include <Standard_DefineHandle.hxx>

#include <Geom2d_Geometry.hxx>
#include <AIS_InteractiveObject.hxx>
#include <TCollection_ExtendedString.hxx>

#include <Quantity_NameOfColor.hxx>
#include <Aspect_TypeOfLine.hxx>

#include "Sketcher_ObjectType.h"
#include "Sketcher_ObjectGeometryType.h"
#include "Sketcher_ObjectTypeOfMethod.h"

class AIS_InteractiveObject;
class Geom2d_Geometry;

class Sketcher_Object;
DEFINE_STANDARD_HANDLE(Sketcher_Object, Standard_Transient)

class Sketcher_Object : public Standard_Transient{
public:

	/**
	* \fn Sketcher_Object(const Handle(Geom2d_Geometry)& theGeom2d_Geometry,const Handle(AIS_InteractiveObject)& theAIS_InteractiveObject, const TCollection_ExtendedString& theName, const Sketcher_ObjectGeometryType theGeometryType, const Sketcher_ObjectTypeOfMethod theTypeOfMethod)
	* \brief Constructs a Sketcher_Object
	* \param theGeom2d_Geometry const Handle(Geom2d_Geometry)&
	* \param theAIS_InteractiveObject const TCollection_ExtendedString&
	* \param theName const TCollection_ExtendedString&
	* \param theGeometryType const Sketcher_ObjectGeometryType
	* \param theTypeOfMethod const Sketcher_ObjectTypeOfMethod
	*/
	Sketcher_Object(const Handle(Geom2d_Geometry)& theGeom2d_Geometry, const Handle(AIS_InteractiveObject)& theAIS_InteractiveObject, const TCollection_ExtendedString& theName, const Sketcher_ObjectGeometryType theGeometryType, const Sketcher_ObjectTypeOfMethod theTypeOfMethod);

	/**
	* \fn ~Sketcher_Object()
	* \brief destructor
	*/
	~Sketcher_Object();

	/**
	* \fn SetGeometry(const Handle(Geom2d_Geometry)& theGeom2d_Geometry)
	* \brief set Geom2d_Geometry
	* \return void
	* \param theGeom2d_Geometry const Handle(Geom2d_Geometry)&
	*/
	void SetGeometry(const Handle(Geom2d_Geometry)& theGeom2d_Geometry);

	/**
	* \fn GetGeometry()
	* \brief get Geom2d_Geometry
	* \return Handle(Geom2d_Geometry)
	*/
	Handle(Geom2d_Geometry) GetGeometry();

	/**
	* \fn SetAIS_Object(const Handle(AIS_InteractiveObject)& theAIS_InteractiveObject)
	* \brief set object representation
	* \return void
	* \param theAIS_InteractiveObject const Handle(AIS_InteractiveObject)&
	*/
	void SetAIS_Object(const Handle(AIS_InteractiveObject)& theAIS_InteractiveObject);

	/**
	* \fn GetAIS_Object()
	* \brief get object represent
	* \return Handle(AIS_InteractiveObject)
	*/
	Handle(AIS_InteractiveObject) GetAIS_Object();

	/**
	* \fn SetObjectName(const Handle(TCollection_ExtendedString)& theName)
	* \brief set object name
	* \return void
	* \param theName const Handle(TCollection_ExtendedString)&
	*/
	void SetObjectName(const TCollection_ExtendedString& theName);

	/**
	* \fn GetObjectName()
	* \brief get object name
	* \return TCollection_ExtendedString
	*/
	TCollection_ExtendedString GetObjectName();

	/**
	* \fn SetGeometryType(const Sketcher_ObjectGeometryTypeHandle(TCollection_ExtendedString)& theGeometryType)
	* \brief set type of geometry
	* \return void
	* \param theGeometryType const Sketcher_ObjectGeometryType
	*/
	void SetGeometryType(const Sketcher_ObjectGeometryType theGeometryType);

	/**
	* \fn GetGeometryType()
	* \brief get type of geometry
	* \return Sketcher_ObjectGeometryType
	*/
	Sketcher_ObjectGeometryType GetGeometryType();

	/**
	* \fn SetTypeOfMethod(const Sketcher_ObjectTypeOfMethod theTypeOfMethod)
	* \brief set object entering method
	* \return void
	* \param theGeometryType const Sketcher_ObjectTypeOfMethod
	*/
	void SetTypeOfMethod(const Sketcher_ObjectTypeOfMethod theTypeOfMethod);

	/**
	* \fn GetTypeOfMethod()
	* \brief get object entering method
	* \return Sketcher_ObjectTypeOfMethod
	*/
	Sketcher_ObjectTypeOfMethod GetTypeOfMethod();

	/**
	* \fn SetColor(const Quantity_NameOfColor theColor)
	* \brief set color
	* \return void
	* \param theColor const Quantity_NameOfColor
	*/
	void SetColor(const Quantity_NameOfColor theColor);

	/**
	* \fn GetColor()
	* \brief get color
	* \return Quantity_NameOfColor
	*/
	Quantity_NameOfColor GetColor();

	/**
	* \fn SetType(const Sketcher_ObjectType theType)
	* \brief set type of object
	* \return void
	* \param theType const Sketcher_ObjectType
	*/
	void SetType(const Sketcher_ObjectType theType);

	/**
	* \fn GetType()
	* \brief get object type
	* \return Sketcher_ObjectType
	*/
	Sketcher_ObjectType GetType();

	/**
	* \fn SetStyle(const Aspect_TypeOfLine theLineStyle)
	* \brief set line style
	* \return void
	* \param theLineStyle const Aspect_TypeOfLine
	*/
	void SetStyle(const Aspect_TypeOfLine theLineStyle);

	/**
	* \fn GetStyle()
	* \brief get line style
	* \return Aspect_TypeOfLine
	*/
	Aspect_TypeOfLine GetStyle();

	/**
	* \fn SetWidth(const Standard_Real theWidth)
	* \brief set line width
	* \return void
	* \param theWidth const Standard_Real
	*/
	void SetWidth(const Standard_Real theWidth);

	/**
	* \fn GetWidth()
	* \brief get width
	* \return Standard_Real
	*/
	Standard_Real GetWidth();

    DEFINE_STANDARD_RTTIEXT(Sketcher_Object, Standard_Transient)

private:

	Handle(Geom2d_Geometry)			myGeometry;
	Handle(AIS_InteractiveObject)   myAIS_InteractiveObject;

	TCollection_ExtendedString		myName;
	Sketcher_ObjectGeometryType		myGeometryType;
	Sketcher_ObjectTypeOfMethod		myTypeOfMethod;

	Quantity_NameOfColor			myNameOfColor;
	Sketcher_ObjectType				myObjectType;
	Aspect_TypeOfLine				myLineStyle;
	Standard_Real					myWidth;

};


#endif
