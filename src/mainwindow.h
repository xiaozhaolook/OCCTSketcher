#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QFileDialog>
#include <QFrame>
#include "OCCView.h"
class OCCView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

	void createToolBars(void);

private:
    Ui::MainWindow *									ui;

	QFrame *											myFrame;
	OCCView*											myOccView;

	QList<QAction*>*									myViewActions;
	QList<QAction *> *									myDrawActions;

	QMenu *												fileMenu;
	QMenu *												operatorMenu;
	QToolBar *											viewToolBar;
	QToolBar *											drawingToolBar;

private slots:
	void FrontViewSlot();
	void BackViewSlot();
	void LeftViewSlot();
	void RightViewSlot();
	void BottomViewSlot();
	void TopViewSlot();
	void GridViewSlot();
};

#endif // MAINWINDOW_H
