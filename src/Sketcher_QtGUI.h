#ifndef Sketcher_QtGUI_H
#define Sketcher_QtGUI_H

#include "Sketcher_GUI.h"
#include "Sketcher_Object.h"

#include "Sketcher_PropertyArc.h"
#include "Sketcher_PropertyCircle.h"
#include "Sketcher_PropertyLine.h"
#include "Sketcher_PropertyPoint.h"

#include <QWidget>

class Sketcher_QtGUI : public Sketcher_GUI
{
public:

	/**
	* \fn Sketcher_QtGUI( QWidget* parent)
	* \brief Constructs a Sketcher_QtGUI
	* \param parent QWidget*
	*/
	Sketcher_QtGUI(QWidget* parent = Q_NULLPTR);

	/**
	* \fn ~Sketcher_GUI()
	* \brief destructor
	*/
	~Sketcher_QtGUI();

	/**
	* \fn SetContext(Handle(AIS_InteractiveContext)& theContext)
	* \brief pass context to property classes
	* \return void
	* \param theContext Handle(AIS_InteractiveContext)&
	*/
	void SetContext(Handle(AIS_InteractiveContext)& theContext);

	/**
	* \fn SetAx3(const gp_Ax3& theAx3)
	* \brief pass coordinate system to property classes
	* \return void
	* \param theAx3 const gp_Ax3&
	*/
	void SetAx3(const gp_Ax3& theAx3);

	/**
	* \fn SetSketcher_Object(Handle(Sketcher_Object)& CurObject)
	* \brief determine property to show, pass object to this property class
	* \return void
	* \param CurObject Handle(Sketcher_Object)&
	*/
	void SetSketcher_Object(Handle(Sketcher_Object)& CurObject);

private:

	//members

	Sketcher_PropertyArc*								prop_arc;
	Sketcher_PropertyCircle*							prop_circle;
	Sketcher_PropertyLine*								prop_line;
	Sketcher_PropertyPoint*								prop_point;

};

#endif