#ifndef Geom2d_Arc_H
#define Geom2d_Arc_H Geom2d_Arc_H

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#include <Standard_DefineHandle.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Circ2d.hxx>
#include <Geom2d_Circle.hxx>
#include <ElCLib.hxx>

class Geom2d_Arc;
DEFINE_STANDARD_HANDLE(Geom2d_Arc, Geom2d_Circle)

class Geom2d_Arc : public Geom2d_Circle{
public:
	/**
	* \fn Geom2d_Arc(const gp_Circ2d& C)
	* \brief Constructs a Geom2d_Arc
	* \param C const gp_Circ2d&
	*/
	Geom2d_Arc(const gp_Circ2d& C);

	/**
	* \fn Geom2d_Arc(const gp_Ax2d& Ax2d,const Standard_Real R)
	* \brief Constructs a Geom2d_Arc
	* \param Ax2d const gp_Ax2d&
	* \param R const Standard_Real
	*/
	Geom2d_Arc(const gp_Ax2d& Ax2d, const Standard_Real R);

	/**
	* \fn ~Geom2d_Arc()
	* \brief destructor
	*/
	~Geom2d_Arc();

	/**
	* \fn SetParam(const gp_Pnt2d& start,const gp_Pnt2d& mid,const gp_Pnt2d& end)
	* \brief set parameters
	* \param start const gp_Pnt2d&
	* \param mid const gp_Pnt2d&
	* \param end const gp_Pnt2d&
	*/
	void SetParam(const gp_Pnt2d& start, const gp_Pnt2d& mid, const gp_Pnt2d& end);

	/**
	* \fn SetFirstParam(const Standard_Real u1)
	* \brief set first parameter
	* \return void
	* \param u1 const Standard_Real
	*/
	void SetFirstParam(const Standard_Real u1);

	/**
	* \fn SetFirstParam(const gp_Pnt2d& p1)
	* \brief set first parameter
	* \return void
	* \param p1 const gp_Pnt2d&
	*/
	void SetFirstParam(const gp_Pnt2d& p1);

	/**
	* \fn SetLastParam(const Standard_Real u2)
	* \brief set last parameter
	* \return void
	* \param u2 const Standard_Real
	*/
	void SetLastParam(const Standard_Real u2);

	/**
	* \fn SetLastParam(const gp_Pnt2d& p2)
	* \brief set last parameter
	* \return void
	* \param p2 const gp_Pnt2d&
	*/
	void SetLastParam(const gp_Pnt2d& p2);

	/**
	* \fn FirstParameter()
	* \brief get first parameter
	* \return Standard_Real const
	*/
	Standard_Real FirstParameter() const;

	/**
	* \fn LastParameter()
	* \brief get last parameter
	* \return Standard_Real const
	*/
	Standard_Real LastParameter() const;

	/**
	* \fn FirstPnt()
	* \brief get first 2d point
	* \return gp_Pnt2d const
	*/
	gp_Pnt2d FirstPnt() const;

	/**
	* \fn LastPnt()
	* \brief get last 2d point
	* \return gp_Pnt2d const
	*/
	gp_Pnt2d LastPnt() const;

	/**
	* \fn MiddlePnt()
	* \brief get middle 2d point
	* \return gp_Pnt2d const
	*/
	gp_Pnt2d MiddlePnt() const;

	DEFINE_STANDARD_RTTIEXT(Geom2d_Arc, Geom2d_Circle)

private:

	/**
	* \fn CheckParam()
	* \brief set correct parameters
	* \return void
	*/
	void CheckParam();

	//members

	Standard_Real	myFirstParam;
	Standard_Real	myLastParam;
};

#endif