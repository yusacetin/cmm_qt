#ifndef CMMCANVAS_H
#define CMMCANVAS_H

#include "point.h"
#include "cmmshape.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QDebug>

class CMMCanvas : public QWidget {
    Q_OBJECT
public:
    explicit CMMCanvas(QWidget* parent = nullptr);

private:
    QPainter m_painter;
    CMMShape m_shape;
    void draw_circles();
    int dcx = 0;
    int dcy = 0;
    double get_rotation(int index);
    Point get_point_pos(int index);
    int get_pair_index(int index);
    void draw_lines();
    void draw_outline();
    enum State{
        IDLE,
        MOVING
    };
    State state = IDLE;
    QPoint mouse_pos_prev;

public slots:
    void set_points(int new_points);
    void set_multiplier(int new_mul);
    void set_line_width(int new_width);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

};

#endif // CMMCANVAS_H
