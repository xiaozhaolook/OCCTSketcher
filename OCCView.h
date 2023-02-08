#ifndef OCCVIEW_H
#define OCCVIEW_H

#include <QGLWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QRubberBand>
#include <QStyleFactory>
#include <QCheckBox>
#include <QApplication>
#include <QCursor>

#include <V3d_View.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <WNT_Window.hxx>
#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>

#include "Sketcher.h"
#include "Sketcher_QtGUI.h"

class QMenu;
class QRubberBand;

#define GRID1 Aspect_GT_Rectangular, Aspect_GDM_Lines
#define GRID2 Aspect_GT_Circular, Aspect_GDM_Points

class OCCView :public QGLWidget{
	Q_OBJECT
public:
	//mouse actions
	enum CurrentAction3d{
		CurAction3d_Nothing,
		CurAction3d_DynamicZooming,
		CurAction3d_WindowZooming,
		CurAction3d_DynamicPanning,
		CurAction3d_GlobalPanning,
		CurAction3d_DynamicRotation,
		SketcherAction
	};

	enum ViewAction {
		ViewFitAllId,
		ViewZoomId,
		ViewPanId,
		ViewGlobalPanId,
		ViewFrontId,
		ViewBackId,
		ViewTopId,
		ViewBottomId,
		ViewLeftId,
		ViewRightId,
		ViewAxoId,
		ViewRotationId,
		ViewResetId
	};

	enum DrawAction {
		MyEraseActionId,
		MyDeleteActionId,
		MyPropertyActionId,
		MyRedrawActionId,
		MyChangePlaneAction,
		MyGridActionId,
		MyInputPointAction,
		MyInputLineAction,
		MyInputCircleAction,
		MyInputCircle3PAction,
		MyInputCircle2PTanAction,
		MyInputCircleP2TanAction,
		MyInputCircle3TanAction,
		MyInputArc3PAction,
		MyInputArcCenter2PAction,
		MyInputBezierCurveAction,
		MyTrimCurveAction
	};

	OCCView(QWidget *parent);

	const Handle(AIS_InteractiveContext) & getContext() const;
	QList<QAction *> *getViewActions();
	QList<QAction *> *getDrawActions();
	void noActiveActions();
signals:
	void selectionChanged(void);

public slots:
	//! operations for the view.
	void pan(void);
	void globalPan();
	void fitArea();
	void fitAll(void);
	void reset(void);
	void zoom(void);
	void rotate(void);
	void rotation();
	void front();
	void back();
	void bottom();
	void top();
	void left();
	void right();
	void axo();

	void updateToggled(bool);

	//mas insert
	void onErase();
	void onDeleteSelected();
	void onProperty();
	void onRedrawAll();
	void onChangePlane();
	void onGrid();
	void onInputPoints();
	void onInputLines();
	void onInputCircles();
	void onInputCircles3P();
	void onInputCircles2PTan();
	void onInputCirclesP2Tan();
	void onInputCircles3Tan();
	void onInputArc3P();
	void onInputArcCenter2P();
	void onInputBezierCurve();
	void onTrimCurve();

	void addItemInPopup(QAction* theAction);
protected:

	void initCursors();
	void initViewActions();
	void initDrawActions();
	// Paint events.
	virtual void paintEvent(QPaintEvent* theEvent);
	virtual void resizeEvent(QResizeEvent* theEvent);

	// Mouse events.
	virtual void mousePressEvent(QMouseEvent* theEvent);
	virtual void mouseReleaseEvent(QMouseEvent* theEvent);
	virtual void mouseMoveEvent(QMouseEvent * theEvent);
	virtual void wheelEvent(QWheelEvent * theEvent);

	// Button events.
	virtual void onLButtonDown(const int theFlags, const QPoint thePoint);
	virtual void onMButtonDown(const int theFlags, const QPoint thePoint);
	virtual void onRButtonDown(const int theFlags, const QPoint thePoint);
	virtual void onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint);
	virtual void onLButtonUp(const int theFlags, const QPoint thePoint);
	virtual void onMButtonUp(const int theFlags, const QPoint thePoint);
	virtual void onRButtonUp(const int theFlags, const QPoint thePoint);
	virtual void onMouseMove(const int theFlags, const QPoint thePoint);
    void DrawRectangle( const int MinX, const int MinY, const int MaxX, const int MaxY, const bool Draw );

protected:
	void init(void);
	void popup(const int x, const int y);
	void dragEvent(const int x, const int y, const int TheState);
	void inputEvent(const int x, const int y);
	void moveEvent(const int x, const int y);
	void multiMoveEvent(const int x, const int y);
	void multiDragEvent(const int x, const int y, const int TheState);
	void multiInputEvent(const int x, const int y);
	void drawRubberBand(const int minX, const int minY, const int maxX, const int maxY);
	void panByMiddleButton(const QPoint& thePoint);
	void activateCursor(const CurrentAction3d);

private:
	Handle(V3d_Viewer)									myViewer;
	Handle(V3d_View)									myView;
	Handle(AIS_InteractiveContext)						myContext;
	CurrentAction3d										myCurrentMode;
	Standard_Integer									myXmin;
	Standard_Integer									myYmin;
	Standard_Integer									myXmax;
	Standard_Integer									myYmax;
    Standard_Real										myCurZoom;
	Standard_Boolean									myDegenerateModeIsOn;
	QList<QAction*>*									myViewActions;
	QList<QAction*>*									myDrawActions;
	//! rubber rectangle for the mouse selection.
	QRubberBand*										myRectBand;
	QMenu *												myMenu;

	//mas insert
	QCheckBox *											PolylineModeCheck;
	bool												GRIDCounter;
	Sketcher *											mySketcher;
    Standard_Real										my_v3dX, my_v3dY, my_v3dZ;
    Standard_Real									projVx, projVy, projVz;
};

#endif
