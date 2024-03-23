#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cmmcanvas.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void set_points(int new_points);
    void set_multiplier(int new_mul);
    void set_line_width(int new_width);
    void toggle_fullscreen();

private:
    Ui::MainWindow* ui;
    CMMCanvas* canvas;

};

#endif // MAINWINDOW_H
