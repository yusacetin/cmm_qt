#ifndef GLOBAL_KEY_FILTER_H
#define GLOBAL_KEY_FILTER_H

#include "mainwindow.h"
#include <QObject>
#include <QKeyEvent>
#include <QDebug>

class GlobalKeyFilter : public QObject {
public:
    MainWindow* win;

    GlobalKeyFilter(MainWindow* set_win) : win(set_win) {}

    bool eventFilter(QObject* obj, QEvent* event) override {
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
            if (key_event->key() == Qt::Key_F) {
                win->toggle_fullscreen();
                return true;
            }
        }

        return QObject::eventFilter(obj, event);
    }
};

#endif // GLOBAL_KEY_FILTER_H
