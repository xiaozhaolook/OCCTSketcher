#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QDockWidget>
#include <QHBoxLayout>

#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>

#include <gp_Lin2d.hxx>

#include <Geom_ConicalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

#include <BRepLib.hxx>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>

#include <BRepAlgo_Section.hxx>

#include <AIS_Shape.hxx>

#include <STEPControl_Reader.hxx>

#include <TColgp_Array1OfPnt.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomFill.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom2dAPI_PointsToBSpline.hxx>
#include <Geom2d_OffsetCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <GeomAPI.hxx>
#include <Geom_OffsetCurve.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeAnalysis_Surface.hxx>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	QHBoxLayout * layerout = new QHBoxLayout();
	myFrame = new QFrame(this);
	myFrame->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	myFrame->setLineWidth(0);	
	
	myOccView = new OCCView(myFrame);

	myOccView->setBackgroundRole(QPalette::Midlight);

	layerout->addWidget(myOccView);
	layerout->setMargin(0);
	myFrame->setLayout(layerout);
	setCentralWidget(myFrame);
	createToolBars();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createToolBars(void){
	viewToolBar = addToolBar(QString("view toolBar"));
	myViewActions = myOccView->getViewActions();
	for (auto iter = myViewActions->begin(); iter != myViewActions->end(); iter++)
		viewToolBar->addAction(*iter);

	drawingToolBar = addToolBar(QString("drawing tools"));
	myDrawActions = myOccView->getDrawActions();
	for (auto iter = myDrawActions->begin(); iter != myDrawActions->end(); iter++)
		drawingToolBar->addAction(*iter);
}

void MainWindow::FrontViewSlot(){
	myOccView->front();
}

void MainWindow::BackViewSlot(){
	myOccView->back();
}

void MainWindow::LeftViewSlot(){
	myOccView->left();
}

void MainWindow::RightViewSlot(){
	myOccView->right();
}

void MainWindow::BottomViewSlot(){
	myOccView->bottom();
}

void MainWindow::TopViewSlot(){
	myOccView->top();
}

void MainWindow::GridViewSlot(){
	myOccView->onGrid();
}


