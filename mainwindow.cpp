#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmmcanvas.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->panel->setStyleSheet("#panel{background-color: rgb(16, 16, 16);}");

    canvas = ui->cmmwidget;

    connect(ui->points_spinbox, SIGNAL(valueChanged(int)), this, SLOT(set_points(int)));
    connect(ui->mul_spinbox, SIGNAL(valueChanged(int)), this, SLOT(set_multiplier(int)));
    connect(ui->line_width_spinbox, SIGNAL(valueChanged(int)), this, SLOT(set_line_width(int)));
    connect(ui->fullscreen_button, SIGNAL(clicked(bool)), this, SLOT(toggle_fullscreen()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canvas;
}

void MainWindow::set_points(int new_points) {
    canvas->set_points(new_points);
    canvas->update();
}

void MainWindow::set_multiplier(int new_mul) {
    canvas->set_multiplier(new_mul);
    canvas->update();
}

void MainWindow::set_line_width(int new_width) {
    canvas->set_line_width(new_width);
    canvas->update();
}

void MainWindow::toggle_fullscreen() {
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}
