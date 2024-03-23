#include "cmmcanvas.h"
#include <cmath>

CMMCanvas::CMMCanvas(QWidget* parent) : QWidget(parent) {}

/////////////
// Setters //
/////////////

void CMMCanvas::set_points(int new_points) {
    m_shape.points = new_points;
}

void CMMCanvas::set_multiplier(int new_mul) {
    m_shape.mul = new_mul;
}

void CMMCanvas::set_line_width(int new_value) {
    m_shape.width = new_value;
}

//////////////////////
// Helper Functions //
//////////////////////

double CMMCanvas::get_rotation(int index) {
    return 2*3.1415926535897932384626 / m_shape.points * index;
}

int CMMCanvas::get_pair_index(int index) {
    return (index * m_shape.mul) % m_shape.points;
}

Point CMMCanvas::get_point_pos(int index) {
    double cx = width()/2 + dcx;
    double cy = height()/2 + dcy;
    double theta = get_rotation(index);
    double x = cx + m_shape.radius * sin(theta);
    double y = cy - m_shape.radius * cos(theta);
    return Point(x, y);
}

/////////////
// Drawing //
/////////////

void CMMCanvas::draw_outline() {
    m_painter.drawEllipse(dcx+width()/2-m_shape.radius, dcy+height()/2-m_shape.radius, m_shape.radius*2, m_shape.radius*2);
}

void CMMCanvas::draw_circles() {
    for (int i=0; i<m_shape.points; i++) {
        Point pos = get_point_pos(i);
        m_painter.drawEllipse(pos.x-m_shape.width/2, pos.y-m_shape.width/2, m_shape.width, m_shape.width);
    }
}

void CMMCanvas::draw_lines() {
    for (int i=0; i<m_shape.points; i++) {
        Point cur_pos = get_point_pos(i);
        int pair_index = get_pair_index(i);
        Point pair_pos = get_point_pos(pair_index);
        m_painter.drawLine(cur_pos.x, cur_pos.y, pair_pos.x, pair_pos.y);
    }
}

void CMMCanvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    m_painter.begin(this);
    m_painter.setRenderHint(QPainter::Antialiasing);

    QColor bg_color(20, 20, 20, 255);
    m_painter.fillRect(rect(), bg_color);

    QColor fg_color(250, 250, 250, 255);
    QPen pen(fg_color);
    pen.setWidth(m_shape.width);
    m_painter.setPen(pen);

    draw_outline();
    draw_circles();
    draw_lines();

    m_painter.end();
}

//////////////////
// Input Events //
//////////////////

void CMMCanvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (state == IDLE) {
            state = MOVING;
            mouse_pos_prev = event->pos();
        }
    }

    QWidget::mousePressEvent(event);
}

void CMMCanvas::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (state == MOVING) {
            state = IDLE;
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void CMMCanvas::mouseMoveEvent(QMouseEvent* event) {
    if (state == MOVING) {
        QPoint mouse_pos = event->pos();
        double dx = mouse_pos.x() - mouse_pos_prev.x();
        double dy = mouse_pos.y() - mouse_pos_prev.y();
        dcx += dx;
        dcy += dy;
        mouse_pos_prev = mouse_pos;
        update();
    }

    QWidget::mouseMoveEvent(event);
}

void CMMCanvas::wheelEvent(QWheelEvent* event) {
    if (event->source() == Qt::MouseEventNotSynthesized) {
        double zoom_coef = m_shape.radius * 0.001;

        double oldr = m_shape.radius;
        double newr = m_shape.radius + event->angleDelta().y() * zoom_coef;
        m_shape.radius = newr;

        double mouse_dx = event->position().x() - width()/2;
        double mouse_dy = event->position().y() - height()/2;

        double dx = mouse_dx - dcx;
        double dy = mouse_dy - dcy;

        double dx_from_mouse = dx - newr * dx / oldr;
        double dy_from_mouse = dy - newr * dy / oldr;

        dcx += dx_from_mouse;
        dcy += dy_from_mouse;

        update();
    }

    QWidget::wheelEvent(event);
}

