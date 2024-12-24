#ifndef COMPGRAPH_CUSTOMVIEW_H
#define COMPGRAPH_CUSTOMVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>

class MainWindow;

class CustomView : public QGraphicsView
{
public:
	CustomView(QWidget* parent = nullptr);

	void set_main_window_pointer(MainWindow* t_mainWindow = nullptr);

protected:
	void wheelEvent(QWheelEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	MainWindow* mainWindow;
	QPoint last_mouse_position;

private:
	float theta;
	float phi;
};

#endif //CUSTOMVIEW_H
