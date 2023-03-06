#include "Geom2d_Arc.h"

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_Arc, Geom2d_Circle)

/**
* \fn Geom2d_Arc(const gp_Circ2d& C)
* \brief Constructs a Geom2d_Arc
* \param C const gp_Circ2d&
*/
Geom2d_Arc::Geom2d_Arc(const gp_Circ2d& C) :Geom2d_Circle(C)
{
	myFirstParam = 0.0;
	myLastParam = 2.0 * M_PI;
}

/**
* \fn Geom2d_Arc(const gp_Ax2d& Ax2d,const Standard_Real R)
* \brief Constructs a Geom2d_Arc
* \param Ax2d const gp_Ax2d&
* \param R const Standard_Real
*/
Geom2d_Arc::Geom2d_Arc(const gp_Ax2d& Ax2d, const Standard_Real R)
	:Geom2d_Circle(Ax2d, R)
{
	myFirstParam = 0.0;
	myLastParam = 2.0 * M_PI;
}

/**
* \fn ~Geom2d_Arc()
* \brief destructor
*/
Geom2d_Arc::~Geom2d_Arc()
{
}

/**
* \fn SetParam(const gp_Pnt2d& start,const gp_Pnt2d& mid,const gp_Pnt2d& end)
* \brief set parameters
* \param start const gp_Pnt2d&
* \param mid const gp_Pnt2d&
* \param end const gp_Pnt2d&
*/
void Geom2d_Arc::SetParam(const gp_Pnt2d& start, const gp_Pnt2d& mid, const gp_Pnt2d& end)
{
	myFirstParam = ElCLib::Parameter(Circ2d(), start);
	myLastParam = ElCLib::Parameter(Circ2d(), end);
	Standard_Real u = ElCLib::Parameter(Circ2d(), mid);
	CheckParam();

	if ((myFirstParam < u) && (u < myLastParam) ||
		(myFirstParam < u + 2 * M_PI) && (u + 2 * M_PI < myLastParam));
	else
	{
		Standard_Real u;
		if (myLastParam > 2 * M_PI)
		{
			myLastParam -= 2 * M_PI;
			u = myFirstParam;
		}
		else u = myFirstParam + 2 * M_PI;

		myFirstParam = myLastParam;
		myLastParam = u;
	}
}

/**
* \fn SetFirstParam(const Standard_Real u1)
* \brief set first parameter
* \return void
* \param u1 const Standard_Real
*/
void Geom2d_Arc::SetFirstParam(const Standard_Real u1)
{
	myFirstParam = u1;
	CheckParam();
}

/**
* \fn SetFirstParam(const gp_Pnt2d& p1)
* \brief set first parameter
* \return void
* \param p1 const gp_Pnt2d&
*/
void Geom2d_Arc::SetFirstParam(const gp_Pnt2d& p1)
{
	myFirstParam = ElCLib::Parameter(Circ2d(), p1);
	CheckParam();
}

/**
* \fn SetLastParam(const Standard_Real u2)
* \brief set last parameter
* \return void
* \param u2 const Standard_Real
*/
void Geom2d_Arc::SetLastParam(const Standard_Real u2)
{
	myLastParam = u2;
	CheckParam();
}

/**
* \fn SetLastParam(const gp_Pnt2d& p2)
* \brief set last parameter
* \return void
* \param p2 const gp_Pnt2d&
*/
void Geom2d_Arc::SetLastParam(const gp_Pnt2d& p2)
{
	myLastParam = ElCLib::Parameter(Circ2d(), p2);
	CheckParam();
}

/**
* \fn FirstParameter()
* \brief get first parameter
* \return Standard_Real const
*/
Standard_Real Geom2d_Arc::FirstParameter() const
{
	return myFirstParam;
}

/**
* \fn LastParameter()
* \brief get last parameter
* \return Standard_Real const
*/
Standard_Real Geom2d_Arc::LastParameter() const
{
	return myLastParam;
}

/**
* \fn FirstPnt()
* \brief get first 2d point
* \return gp_Pnt2d const
*/
gp_Pnt2d Geom2d_Arc::FirstPnt() const
{
	return ElCLib::Value(myFirstParam, Circ2d());
}

/**
* \fn LastPnt()
* \brief get last 2d point
* \return gp_Pnt2d const
*/
gp_Pnt2d Geom2d_Arc::LastPnt() const
{
	return ElCLib::Value(myLastParam, Circ2d());
}

/**
* \fn MiddlePnt()
* \brief get middle 2d point
* \return gp_Pnt2d const
*/
gp_Pnt2d Geom2d_Arc::MiddlePnt() const
{
	return ElCLib::Value((myLastParam + myFirstParam) / 2, Circ2d());
}

/**
* \fn CheckParam()
* \brief set correct parameters
* \return void
*/
void Geom2d_Arc::CheckParam()
{
	while (myFirstParam > 2 * M_PI)
		myFirstParam -= 2 * M_PI;
	while (myLastParam > 2 * M_PI || (myLastParam - myFirstParam)> 2 * M_PI)
		myLastParam -= 2 * M_PI;

	while (myFirstParam > myLastParam)
		myLastParam += 2 * M_PI;
}
