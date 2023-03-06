#ifndef Sketcher_PropertyArc_H
#define Sketcher_PropertyArc_H

#include "Sketcher_Property.h"
#include "Geom2d_Arc.h"

#include <gce_MakeCirc2d.hxx>
#include <Geom_Circle.hxx>
#include <AIS_Circle.hxx>

//class editing arc
class Sketcher_PropertyArc : public Sketcher_Property
{ 
    Q_OBJECT

public:

//methods

/**
 * \fn Sketcher_PropertyArc( QWidget* parent,  const char* name, WFlags fl )
 * \brief Constructs a Sketcher_PropertyArc which is a child of 'parent', with the name 'name' and widget flags set to 'f' 
 * \param parent QWidget*
 * \param name const char*
 * \param fl WFlags
 */
Sketcher_PropertyArc( QWidget* parent = 0, const char* name = 0);

/**
 * \fn ~Sketcher_PropertyArc() 
 * \brief destructor
 */
~Sketcher_PropertyArc();


//members

QLabel* TextLabelRadius;
QLineEdit* LineEditRadius;
QLabel* TextLabelStartArc;
QLineEdit* LineEditStartArc;
QLabel* TextLabelEndArc;
QLineEdit* LineEditEndArc;

private:

//methods

/**
 * \fn SetGeometry()
 * \brief show object geometry in dialog window
 * \return void 
 */
void SetGeometry();

/**
 * \fn CheckGeometry()
 * \brief check geometry for change
 * \return bool 
 */
bool CheckGeometry();

/**
 * \fn GetGeometry()
 * \brief create new object
 * \return bool 
 */
bool GetGeometry();

//members

Handle(Geom2d_Arc)	curGeom2d_Arc;
double				myRadius,tempRadius;
double				myFirstParameter,myLastParameter,tempFirstParameter,tempLastParameter;
};

#endif // Sketcher_PropertyArc_H
