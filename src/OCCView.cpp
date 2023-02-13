#include "OCCView.h"

#define MULTISELECTIONKEY Qt::ShiftModifier

#define CASCADESHORTCUTKEY Qt::ControlModifier

#define ValZWMin 1

static QCursor* defCursor = nullptr;
static QCursor* handCursor = nullptr;
static QCursor* panCursor = nullptr;
static QCursor* globPanCursor = nullptr;
static QCursor* zoomCursor = nullptr;
static QCursor* rotCursor = nullptr;

static Handle(Graphic3d_GraphicDriver)& GetGraphicDriver()
{
	static Handle(Graphic3d_GraphicDriver) aGraphicDriver;
	return aGraphicDriver;
}

OCCView::OCCView(QWidget *parent) : QGLWidget(parent),
    myXmin(0),
    myYmin(0),
    myXmax(0),
    myYmax(0),
    myCurrentMode(CurAction3d_DynamicRotation),
    myDegenerateModeIsOn(Standard_True),
    myRectBand(nullptr),
    myMenu(nullptr),
    myViewActions(nullptr),
    myDrawActions(nullptr){
	setBackgroundRole(QPalette::NoRole);
	setMouseTracking(true);
	
	myMenu = new QMenu(this);

	initViewActions();
	initDrawActions();
	initCursors();
}

void OCCView::init(void){
	Handle(Aspect_DisplayConnection) aDisplayConnection = new Aspect_DisplayConnection();

	if (GetGraphicDriver().IsNull())
	{
		GetGraphicDriver() = new OpenGl_GraphicDriver(aDisplayConnection);
	}

	WId window_handle = (WId)winId();

	Handle(WNT_Window) wind = new WNT_Window((Aspect_Handle)window_handle);

	myViewer = new V3d_Viewer(GetGraphicDriver()/*, Standard_ExtString("viewer3d")*/);

	myView = myViewer->CreateView();
	myView->SetBgGradientColors(Quantity_NOC_SKYBLUE, Quantity_NOC_GRAY, Aspect_GFM_VER);
	myView->SetWindow(wind);
	if (!wind->IsMapped()) wind->Map();
	myContext = new AIS_InteractiveContext(myViewer);

	Sketcher_QtGUI * mySG = new Sketcher_QtGUI(parentWidget());
	mySketcher = new Sketcher(myContext, mySG);
	GRIDCounter = true;
	
	// Set up lights etc
	myViewer->SetDefaultLights();
	myViewer->SetLightOn();

	myView->SetBackgroundColor(Quantity_NOC_GRAY60);
	myView->MustBeResized();
	myView->TriedronDisplay(Aspect_TOTP_RIGHT_LOWER, Quantity_NOC_CHOCOLATE, 0.08, V3d_ZBUFFER);

	myContext->SetDisplayMode(AIS_Shaded, Standard_True);

    mySketcher->SetPolylineMode(Standard_True);
	//mySketcher->SetType(AuxiliarySketcherType);

	//Standard_Real mywidth{2.0};
	//mySketcher->SetWidth(mywidth);
	mySketcher->SetSnap(SnapNearest); 
}

const Handle(AIS_InteractiveContext) & OCCView::getContext() const{
	return myContext;
}

QList<QAction *>* OCCView::getViewActions(){
	initViewActions();
	return myViewActions;
}

QList<QAction *> *OCCView::getDrawActions() {
	initDrawActions();
	return myDrawActions;
}

void OCCView::noActiveActions(){
	for (int i = ViewFitAllId; i <= MyTrimCurveAction; i++)
	{
		QAction* anAction = myViewActions->at(i);
		if ((anAction == myViewActions->at(ViewZoomId)) ||
			(anAction == myViewActions->at(ViewPanId)) ||
			(anAction == myViewActions->at(ViewGlobalPanId)) ||
			(anAction == myViewActions->at(ViewRotationId))
			)
		{
			setCursor(QCursor(Qt::ArrowCursor));
			anAction->setCheckable(true);
			anAction->setChecked(false);
		}
	}

	for (int i = MyEraseActionId; i <= MyTrimCurveAction; i++) {
		QAction* anAction = myDrawActions->at(i);
		if ((anAction == myDrawActions->at(MyInputPointAction)) ||
			(anAction == myDrawActions->at(MyInputLineAction)) ||
			(anAction == myDrawActions->at(MyInputCircleAction)) ||
			(anAction == myDrawActions->at(MyInputCircle3PAction)) ||
			(anAction == myDrawActions->at(MyInputCircle2PTanAction)) ||
			(anAction == myDrawActions->at(MyInputCircleP2TanAction)) ||
			(anAction == myDrawActions->at(MyInputCircle3TanAction)) ||
			(anAction == myDrawActions->at(MyInputArc3PAction)) ||
			(anAction == myDrawActions->at(MyInputArcCenter2PAction)) ||
			(anAction == myDrawActions->at(MyInputBezierCurveAction)) ||
			(anAction == myDrawActions->at(MyTrimCurveAction))) {
			setCursor(QCursor(Qt::ArrowCursor));
			anAction->setCheckable(true);
			anAction->setChecked(false);
		}
	}
}

void OCCView::initCursors(){
	if (!defCursor)
		defCursor = new QCursor(Qt::ArrowCursor);
	if (!handCursor)
		handCursor = new QCursor(Qt::PointingHandCursor);
	if (!panCursor)
		panCursor = new QCursor(Qt::SizeAllCursor);
	if (!globPanCursor)
		globPanCursor = new QCursor(Qt::CrossCursor);
}

void OCCView::initViewActions(){
	if (myViewActions) return;

	myViewActions = new QList<QAction*>();
	QAction* a;

	a = new QAction(QIcon(":/icon_file/view_fitall"), QString("fitall"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(fitAll()));
	myViewActions->insert(ViewFitAllId, a);

	a = new QAction(QIcon(":/icon_file/view_zoom"), QString("zoom"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(zoom()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myViewActions->insert(ViewZoomId, a);

	a = new QAction(QIcon(":/icon_file/view_pan"), QString("pan"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(pan()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myViewActions->insert(ViewPanId, a);

	a = new QAction(QIcon(":/icon_file/view_glpan"), QString("global pan"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(globalPan()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myViewActions->insert(ViewGlobalPanId, a);

	a = new QAction(QIcon(":/icon_file/view_front"), QString("front"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(front()));
	myViewActions->insert(ViewFrontId, a);

	a = new QAction(QIcon(":/icon_file/view_back"), QString("back"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(back()));
	myViewActions->insert(ViewBackId, a);

	a = new QAction(QIcon(":/icon_file/view_top"), QString("top"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(top()));
	myViewActions->insert(ViewTopId, a);

	a = new QAction(QIcon(":/icon_file/view_bottom"), QString("bottom"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(bottom()));
	myViewActions->insert(ViewBottomId, a);

	a = new QAction(QIcon(":/icon_file/view_left"), QString("left"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(left()));
	myViewActions->insert(ViewLeftId, a);

	a = new QAction(QIcon(":/icon_file/view_right"), QString("right"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(right()));
	myViewActions->insert(ViewRightId, a);

	a = new QAction(QIcon(":/icon_file/view_axo"), QString("axo"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(axo()));
	myViewActions->insert(ViewAxoId, a);

	a = new QAction(QIcon(":/icon_file/view_rotate"), QString("rotate"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(rotation()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myViewActions->insert(ViewRotationId, a);

	a = new QAction(QIcon(":/icon_file/view_reset"), QString("reset"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(reset()));
	myViewActions->insert(ViewResetId, a);
}

void OCCView::initDrawActions() {
	if (myDrawActions) return;
	myDrawActions = new QList<QAction *>();
	QAction* a;
	a = new QAction(QIcon(":/icon_file/erase"), QString("erase all"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onErase()));
	myDrawActions->insert(MyEraseActionId, a);
	a->setCheckable(false);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));

	a = new QAction(QIcon(":/icon_file/delete"), QString("delete selected"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onDeleteSelected()));
	myDrawActions->insert(MyDeleteActionId, a);
	a->setCheckable(false);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));

	a = new QAction(QIcon(":/icon_file/property"), QString("view objects property"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onProperty()));
	a->setCheckable(false);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyPropertyActionId, a);

	a = new QAction(QIcon(":/icon_file/redraw"), QString("redraw objects"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onRedrawAll()));
	a->setCheckable(false);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyRedrawActionId, a);

	a = new QAction(QIcon(":/icon_file/plane"), QString("change plane"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onChangePlane()));
	a->setCheckable(false);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyChangePlaneAction, a);

	a = new QAction(QIcon(":/icon_file/grid"), QString("grid"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onGrid()));
	myDrawActions->insert(MyGridActionId, a);

	a = new QAction(QIcon(":/icon_file/inputPoint"), QString("input points"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputPoints()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputPointAction, a);

	a = new QAction(QIcon(":/icon_file/inputLine"), QString("input line"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputLines()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputLineAction, a);

	a = new QAction(QIcon(":/icon_file/inputCircle"), QString("input circles with radius"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputCircles()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputCircleAction, a);

	a = new QAction(QIcon(":/icon_file/inputCircle3p"), QString("input circle by three points"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputCircles3P()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputCircle3PAction, a);

	a = new QAction(QIcon(":/icon_file/inputCircle2PTan"), QString("input circle by 2p, tangential to 3 curve"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputCircles2PTan()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputCircle2PTanAction, a);

	a = new QAction(QIcon(":/icon_file/inputCircleP2Tan"), QString("input circle by p, 2 tangential to 3 curve"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputCirclesP2Tan()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputCircleP2TanAction, a);

	a = new QAction(QIcon(":/icon_file/inputCircle3tan"), QString("input circle by three tan"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputCircles3Tan()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputCircle3TanAction, a);

	a = new QAction(QIcon(":/icon_file/inputArc3p"), QString("input arc by 3 points"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputArc3P()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputArc3PAction, a);

	a = new QAction(QIcon(":/icon_file/inputArcCenter2p"), QString("input arc by center &2points"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputArcCenter2P()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputArcCenter2PAction, a);

	a = new QAction(QIcon(":/icon_file/inputBezierCurve"), QString("input BezierCurve"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onInputBezierCurve()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyInputBezierCurveAction, a);

	a = new QAction(QIcon(":/icon_file/trimcurve"), QString("trim curve"), this);
	connect(a, SIGNAL(triggered()), this, SLOT(onTrimCurve()));
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, SLOT(updateToggled(bool)));
	myDrawActions->insert(MyTrimCurveAction, a);
}

void OCCView::paintEvent(QPaintEvent* theEvent){
	if (myContext.IsNull()){
		init();
	}

	myView->Redraw();
}

void OCCView::resizeEvent(QResizeEvent* theEvent){
	if (!myView.IsNull()){
		myView->MustBeResized();
	}
}

void OCCView::fitArea(){
	myCurrentMode = CurAction3d_WindowZooming;
}

void OCCView::fitAll(void){
	myView->FitAll();
	myView->ZFitAll();
	myView->Redraw();
}

void OCCView::reset(void){
	myView->Reset();
}

void OCCView::pan(void){
	myCurrentMode = CurAction3d_DynamicPanning;
}

void OCCView::globalPan(){
	// save the current zoom value
	myCurZoom = myView->Scale();
	// Do a Global Zoom
	myView->FitAll();
	// Set the mode
	myCurrentMode = CurAction3d_GlobalPanning;
}

void OCCView::zoom(void){
	myCurrentMode = CurAction3d_DynamicZooming;
}

void OCCView::rotate(void){
	myCurrentMode = CurAction3d_DynamicRotation;
}

void OCCView::rotation(){
	myCurrentMode = CurAction3d_DynamicRotation;
}

void OCCView::front(){
	myView->SetProj(V3d_Xpos);
}

void OCCView::back(){
	myView->SetProj(V3d_Xneg);
}

void OCCView::bottom(){
	myView->SetProj(V3d_Zneg);
}

void OCCView::top(){
	myView->SetProj(V3d_Zpos);
}

void OCCView::left(){
	myView->SetProj(V3d_Yneg);
}

void OCCView::right(){
	myView->SetProj(V3d_Ypos);
}

void OCCView::axo(){
	myView->SetProj(V3d_XposYnegZpos);
}

void OCCView::updateToggled(bool isOn){
	QAction* sentBy = (QAction*)sender();

	if (!isOn)
		return;

	if (myCurrentMode == SketcherAction)
		mySketcher->OnCancel();

	for (int i = ViewFitAllId; i < ViewResetId; i++)
	{
		QAction* anAction = myViewActions->at(i);
		if ((anAction == myViewActions->at(ViewZoomId)) ||
			(anAction == myViewActions->at(ViewPanId)) ||
			(anAction == myViewActions->at(ViewGlobalPanId)) ||
			(anAction == myViewActions->at(ViewRotationId))
			)
		{
			if (sentBy == myViewActions->at(ViewZoomId))
				setCursor(QCursor(Qt::SizeBDiagCursor));//缩放
			else if (sentBy == myViewActions->at(ViewPanId))
				setCursor(QCursor(Qt::OpenHandCursor));//平移
			else if (sentBy == myViewActions->at(ViewGlobalPanId))
				setCursor(QCursor(Qt::OpenHandCursor));//平移
			else if (sentBy == myViewActions->at(ViewRotationId))
				setCursor(QCursor(Qt::CrossCursor));//旋转
			else
				setCursor(QCursor(Qt::ArrowCursor));
			sentBy->setCheckable(false);
		}
	}

	for (int i = MyEraseActionId; i <= MyTrimCurveAction; i++) {
		QAction* anAction = myDrawActions->at(i);
		if ((anAction == myDrawActions->at(MyEraseActionId)) ||
			(anAction == myDrawActions->at(MyDeleteActionId)) ||
			(anAction == myDrawActions->at(MyPropertyActionId)) ||
			(anAction == myDrawActions->at(MyRedrawActionId)) ||
			(anAction == myDrawActions->at(MyChangePlaneAction)) ||
			(anAction == myDrawActions->at(MyInputPointAction)) ||
			(anAction == myDrawActions->at(MyInputLineAction)) ||
			(anAction == myDrawActions->at(MyInputCircleAction)) ||
			(anAction == myDrawActions->at(MyInputCircle3PAction)) ||
			(anAction == myDrawActions->at(MyInputCircle2PTanAction)) ||
			(anAction == myDrawActions->at(MyInputCircleP2TanAction)) ||
			(anAction == myDrawActions->at(MyInputCircle3TanAction)) ||
			(anAction == myDrawActions->at(MyInputArc3PAction)) ||
			(anAction == myDrawActions->at(MyInputArcCenter2PAction)) ||
			(anAction == myDrawActions->at(MyInputBezierCurveAction)) ||
			(anAction == myDrawActions->at(MyTrimCurveAction))) {
			if (anAction && (anAction != sentBy))
			{
				if ((anAction == myDrawActions->at(MyEraseActionId)) ||
					(anAction == myDrawActions->at(MyDeleteActionId)) ||
					(anAction == myDrawActions->at(MyPropertyActionId)) ||
					(anAction == myDrawActions->at(MyRedrawActionId)) ||
					(anAction == myDrawActions->at(MyChangePlaneAction)))
					anAction->setCheckable(false);
				else
					anAction->setCheckable(true);
				anAction->setChecked(false);
			}
		}
	}
}

void OCCView::onErase(){
	myContext->EraseAll(1);
}

void OCCView::onDeleteSelected(){
	mySketcher->DeleteSelectedObject();
}

void OCCView::onProperty(){
	mySketcher->ViewProperties();
}

void OCCView::onRedrawAll(){
	mySketcher->RedrawAll();
}

void OCCView::onChangePlane(){
	gp_Dir dir(3, 0, 1);

	gp_Ax3 newgp_Ax3(gp::Origin(), dir);

	mySketcher->SetCoordinateSystem(newgp_Ax3);
}


void OCCView::onGrid(){

	Handle(V3d_Viewer) aViewer = myView->Viewer();
	if (GRIDCounter)
	{
        gp_Dir xDirection(1,0,0),yDirection(0,1,0),zDirection(0,0,1);
        gp_Ax3 diyPlane;

        diyPlane.SetDirection(yDirection);
        aViewer->SetPrivilegedPlane(diyPlane);
        mySketcher->SetCoordinateSystem(diyPlane);

		aViewer->ActivateGrid(GRID1);
		GRIDCounter = false;
	}
	else
	{
		aViewer->DeactivateGrid();
		//	aViewer->ActivateGrid(GRID2);
		GRIDCounter = true;
	}

	myView->Update();
}

void OCCView::onInputPoints(){
	mySketcher->ObjectAction(Point_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputLines(){
	mySketcher->ObjectAction(Line2P_Method);
	//mySketcher->SetWidth(200);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputCircles(){
	mySketcher->ObjectAction(CircleCenterRadius_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputCircles3P(){
	mySketcher->ObjectAction(Circle3P_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputCircles2PTan(){
	mySketcher->ObjectAction(Circle2PTan_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputCirclesP2Tan(){
	mySketcher->ObjectAction(CircleP2Tan_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputCircles3Tan(){
	mySketcher->ObjectAction(Circle3Tan_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputArc3P(){
	mySketcher->ObjectAction(Arc3P_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputArcCenter2P(){
	mySketcher->ObjectAction(ArcCenter2P_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onInputBezierCurve(){
	mySketcher->ObjectAction(BezierCurve_Method);
	myCurrentMode = SketcherAction;
}

void OCCView::onTrimCurve(){
	mySketcher->ObjectAction(Trim_Method);
	myCurrentMode = SketcherAction;
}


void OCCView::mousePressEvent(QMouseEvent* theEvent){
	if (theEvent->button() == Qt::LeftButton)
	{
		onLButtonDown((theEvent->buttons() | theEvent->modifiers()), theEvent->pos());
	}
	else if (theEvent->button() == Qt::MidButton)
	{
		onMButtonDown((theEvent->buttons() | theEvent->modifiers()), theEvent->pos());
	}
	else if (theEvent->button() == Qt::RightButton)
	{
		onRButtonDown((theEvent->buttons() | theEvent->modifiers()), theEvent->pos());
	}
}

void OCCView::mouseReleaseEvent(QMouseEvent* theEvent){
	if (theEvent->button() == Qt::LeftButton)
	{
		onLButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
	}
	else if (theEvent->button() == Qt::MidButton)
	{
		onMButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
	}
	else if (theEvent->button() == Qt::RightButton)
	{
		onRButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
	}
}

void OCCView::mouseMoveEvent(QMouseEvent * theEvent){
	onMouseMove(theEvent->buttons(), theEvent->pos());
}

void OCCView::wheelEvent(QWheelEvent * theEvent){
	onMouseWheel(theEvent->buttons(), theEvent->delta(), theEvent->pos());
}

void OCCView::onLButtonDown(const int theFlags, const QPoint thePoint){
	myXmin = thePoint.x();
	myYmin = thePoint.y();
	myXmax = thePoint.x();
	myYmax = thePoint.y();
	if (theFlags & CASCADESHORTCUTKEY)
	{
		myCurrentMode = CurAction3d_DynamicZooming;
	}
	else
	{
		switch (myCurrentMode)
		{
		case CurAction3d_Nothing:
			if (theFlags & MULTISELECTIONKEY)
				multiDragEvent(myXmax, myYmax, -1);
			else
				dragEvent(myXmax, myYmax, -1);
			break;
		case CurAction3d_DynamicZooming:
			break;
		case CurAction3d_WindowZooming:
			break;
		case CurAction3d_DynamicPanning:
			break;
		case CurAction3d_GlobalPanning:
			break;
		case SketcherAction:
			myView->Convert(myXmin, myYmin, my_v3dX, my_v3dY, my_v3dZ);
			myView->Proj(projVx, projVy, projVz);
			mySketcher->OnMouseInputEvent(my_v3dX, my_v3dY, my_v3dZ, projVx, projVy, projVz);

			break;
		case CurAction3d_DynamicRotation:
			if (!myDegenerateModeIsOn)
				myView->SetComputedMode(Standard_True);
			myView->StartRotation(thePoint.x(), thePoint.y());
			break;
		default:
			Standard_Failure::Raise("incompatible Current Mode");
			break;
		}
	}
	activateCursor(myCurrentMode);
}

void OCCView::onMButtonDown(const int theFlags, const QPoint thePoint){
	//myXmin = thePoint.x();
	//myYmin = thePoint.y();
	//myXmax = thePoint.x();
	//myYmax = thePoint.y();

	//if (myCurrentMode == CurAction3d_DynamicRotation)
	//{
	//	myView->StartRotation(thePoint.x(), thePoint.y());
	//}
	if (theFlags & CASCADESHORTCUTKEY)
		myCurrentMode = CurAction3d_DynamicPanning;
	activateCursor(myCurrentMode);


	//if (theFlags & CASCADESHORTCUTKEY)
	//{
	//	myCurrentMode = CurAction3d_DynamicPanning;
	//	myXmax = thePoint.x();
 //       myYmax = thePoint.y();
	//}
	//else
	//{
	//	myCurrentMode = CurAction3d_DynamicRotation;
		/*if(m_fKeyPoint.x() != 987654321 || m_fKeyPoint.y() != 987654321)
			m_view->StartRotation(event->pos().x(), event->pos().y());
		else*/
	//	myView->StartRotation(thePoint.x(), thePoint.y());
	//}
	//activateCursor(myCurrentMode);

}

void OCCView::onRButtonDown(const int theFlags, const QPoint thePoint){
	if (theFlags & CASCADESHORTCUTKEY)
	{
		if (!myDegenerateModeIsOn)
			myView->SetComputedMode(Standard_True);
		myCurrentMode = CurAction3d_DynamicRotation;
		myView->StartRotation(thePoint.x(), thePoint.y());
	}
	else if (myCurrentMode == SketcherAction)
		mySketcher->OnCancel();

	else
	{
		myMenu->exec(QCursor::pos());
	}
	activateCursor(myCurrentMode);
}

void OCCView::onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint){
	Standard_Integer aFactor = 16;

	Standard_Integer aX = thePoint.x();
	Standard_Integer aY = thePoint.y();

	if (theDelta > 0)
	{
		aX += aFactor;
		aY += aFactor;
	}
	else
	{
		aX -= aFactor;
		aY -= aFactor;
	}

	myView->Zoom(thePoint.x(), thePoint.y(), aX, aY);
}

void OCCView::addItemInPopup(QAction* theAction){
	myMenu->addAction(theAction);
}

void OCCView::popup(const int x, const int y){
	//myMenu->exec(QCursor::pos());
}

void OCCView::onLButtonUp(const int theFlags, const QPoint thePoint){
	// Hide the QRubberBand
	if (myRectBand)	{
		myRectBand->hide();
	}

	// Ctrl for multi selection.
	if (thePoint.x() == myXmin && thePoint.y() == myYmin){
		if (theFlags & Qt::ControlModifier)
		{
			multiInputEvent(thePoint.x(), thePoint.y());
		}
		else{
			inputEvent(thePoint.x(), thePoint.y());
		}
	}
}

void OCCView::onMButtonUp(const int theFlags, const QPoint thePoint){
	if (thePoint.x() == myXmin && thePoint.y() == myYmin)
	{
		panByMiddleButton(thePoint);
	}
}

void OCCView::onRButtonUp(const int theFlags, const QPoint thePoint){
	popup(thePoint.x(), thePoint.y());
}

void OCCView::onMouseMove(const int theFlags, const QPoint thePoint){
	if (theFlags & Qt::LeftButton)
	{
		drawRubberBand(myXmin, myYmin, thePoint.x(), thePoint.y());

		dragEvent(thePoint.x(), thePoint.y(), 1);
	}

	// Ctrl for multi selection.
	if (theFlags & Qt::ControlModifier)
	{
		multiMoveEvent(thePoint.x(), thePoint.y());
	}
	else
	{
		moveEvent(thePoint.x(), thePoint.y());
	}

	// Middle button.
	if (theFlags & Qt::MidButton)
	{
		switch (myCurrentMode)
		{
		case CurAction3d_DynamicRotation:
			myView->Rotation(thePoint.x(), thePoint.y());
			break;

		case CurAction3d_DynamicZooming:
			myView->Zoom(myXmin, myYmin, thePoint.x(), thePoint.y());
			break;

		case CurAction3d_DynamicPanning:
			myView->Pan(thePoint.x() - myXmax, myYmax - thePoint.y());
			myXmax = thePoint.x();
			myYmax = thePoint.y();
			break;

		default:
			break;
		}
	}

	if (!theFlags)
	{
		if (myCurrentMode == SketcherAction)
		{
			myXmax = thePoint.x();
			myYmax = thePoint.y();
			myView->Convert(myXmax, myYmax, my_v3dX, my_v3dY, my_v3dZ);
			myView->Proj(projVx, projVy, projVz);
			mySketcher->OnMouseMoveEvent(my_v3dX, my_v3dY, my_v3dZ, projVx, projVy, projVz);
		}
		myContext->MoveTo(thePoint.x(), thePoint.y(), myView, Standard_True);
	}

}

// TheState == -1  button down
// TheState ==  0  move
// TheState ==  1  button up
void OCCView::dragEvent(const int x, const int y, const int TheState){
	//myContext->Select(myXmin, myYmin, x, y, myView, Standard_True);

	//emit selectionChanged();
	static Standard_Integer theButtonDownX = 0;
	static Standard_Integer theButtonDownY = 0;

	if (TheState == -1){
		theButtonDownX = x;
		theButtonDownY = y;
	}

	if (TheState == 0){
		myContext->Select(theButtonDownX, theButtonDownY, x, y, myView,1);
		emit selectionChanged();
	}
}

void OCCView::inputEvent(const int x, const int y){
	Q_UNUSED(x);
	Q_UNUSED(y);

	myContext->Select(Standard_True);

	emit selectionChanged();
}

void OCCView::moveEvent(const int x, const int y){
	myContext->MoveTo(x, y, myView, Standard_True);
}

void OCCView::multiMoveEvent(const int x, const int y){
	myContext->MoveTo(x, y, myView, Standard_True);
}

void OCCView::multiDragEvent(const int x, const int y, const int TheState){
	//myContext->ShiftSelect(myXmin, myYmin, x, y, myView, Standard_True);

	//emit selectionChanged();
	static Standard_Integer theButtonDownX = 0;
	static Standard_Integer theButtonDownY = 0;

	if (TheState == -1)
	{
		theButtonDownX = x;
		theButtonDownY = y;
	}
	if (TheState == 0)
	{
		myContext->ShiftSelect(theButtonDownX, theButtonDownY, x, y, myView,1);
		emit selectionChanged();
	}
}

void OCCView::multiInputEvent(const int x, const int y){
	Q_UNUSED(x);
	Q_UNUSED(y);

	myContext->ShiftSelect(Standard_True);

	emit selectionChanged();
}

void OCCView::drawRubberBand(const int minX, const int minY, const int maxX, const int maxY){
	QRect aRect;

	// Set the rectangle correctly.
	(minX < maxX) ? (aRect.setX(minX)) : (aRect.setX(maxX));
	(minY < maxY) ? (aRect.setY(minY)) : (aRect.setY(maxY));

	aRect.setWidth(abs(maxX - minX));
	aRect.setHeight(abs(maxY - minY));

	if (!myRectBand)
	{
		myRectBand = new QRubberBand(QRubberBand::Rectangle, this);

		// setStyle is important, set to windows style will just draw
		// rectangle frame, otherwise will draw a solid rectangle.
		myRectBand->setStyle(QStyleFactory::create("windows"));
	}

	myRectBand->setGeometry(aRect);
	myRectBand->show();
}

void OCCView::panByMiddleButton(const QPoint& thePoint){
	Standard_Integer aCenterX = 0;
	Standard_Integer aCenterY = 0;

	QSize aSize = size();

	aCenterX = aSize.width() / 2;
	aCenterY = aSize.height() / 2;

	myView->Pan(aCenterX - thePoint.x(), thePoint.y() - aCenterY);
}

void OCCView::activateCursor(const CurrentAction3d mode){
	switch (mode)
	{
	case CurAction3d_DynamicPanning:
		//setCursor(*panCursor);
		setCursor(QCursor(Qt::OpenHandCursor));//平移
		break;
	case CurAction3d_DynamicZooming:
		//setCursor(*zoomCursor);
		setCursor(QCursor(Qt::SizeBDiagCursor));//缩放
		break;
	case CurAction3d_DynamicRotation:
		//setCursor(*rotCursor);
		setCursor(QCursor(Qt::CrossCursor));//旋转
		break;
	case CurAction3d_GlobalPanning:
		//setCursor(*globPanCursor);
		setCursor(QCursor(Qt::OpenHandCursor));//平移
		break;
	case CurAction3d_WindowZooming:
		//setCursor(*handCursor);
		setCursor(QCursor(Qt::SizeBDiagCursor));//缩放
		break;
	case CurAction3d_Nothing:
	default:
		//setCursor(*defCursor);
		setCursor(QCursor(Qt::ArrowCursor));
		break;
	}
}

void OCCView::DrawRectangle(const int MinX, const int MinY,
                         const int MaxX, const int MaxY, const bool Draw)
{
    QPainter thePainter(this);
//    thePainter.setRasterOp(Qt::XorROP); //改了
    thePainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    thePainter.setPen(Qt::white);

    static Standard_Integer StoredMinX, StoredMaxX, StoredMinY, StoredMaxY;
    static Standard_Boolean m_IsVisible;

    QRect aRect;
    if ( m_IsVisible && !Draw) // move or up  : erase at the old position
    {
        aRect.setRect( StoredMinX, StoredMinY, abs(StoredMaxX-StoredMinX), abs(StoredMaxY-StoredMinY));
        thePainter.drawRect(aRect);
        m_IsVisible = false;
    }
    StoredMinX = (MinX < MaxX) ? MinX: MaxX ;
    StoredMinY = (MinY < MaxY) ? MinY: MaxY ;
    StoredMaxX = (MinX > MaxX) ? MinX: MaxX ;
    StoredMaxY = (MinY > MaxY) ? MinY: MaxY ;

    if (Draw) // move : draw
    {
        aRect.setRect( StoredMinX, StoredMinY, abs(StoredMaxX-StoredMinX), abs(StoredMaxY-StoredMinY));
        thePainter.drawRect(aRect);
        m_IsVisible = true;
    }
}



