#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "scrollareaelem.h"
#include <QLabel>
#include <iostream>
#include <vector>
#include <QHBoxLayout>
#include "list.h"
#include <cmath>
#include <algorithm>
#include <set>
#include "dialogaddchar.h"
#include <map>
#include <QPropertyAnimation>
#include <QThread>
#include <QTimer>
#include <QTime>
#include "dialogerror.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_right_btn_clicked();

    void on_left_btn_clicked();

    void on_lineEdit_returnPressed();

    void on_refresh_tape_btn_clicked();

    void on_clear_table_btn_clicked();

    void on_add_char_btn_clicked();

    void on_add_event_btn_clicked();

    void on_start_btn_clicked();

    void update_time();

    void on_stop_btn_clicked();

private:
    std::vector<ScrollAreaElem *> elems;
    List* list;
    Ui::Widget *ui;
    std::map<QChar, std::vector<QString>> programm;
    QTimer *tmr;
    int next_col = 0;

    void update_elems();
    void make_turn(int col);
};
#endif // WIDGET_H
