#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    //setting tape
    this->list = new List(11);
    for (ListNode* it = list->lbound; it != list->rbound->next; it = it->next) {
        this->elems.push_back(new ScrollAreaElem);
        this->elems[this->elems.size()-1]->setText(it->data);
    }
    for (size_t i = 0; i < this->elems.size(); ++i) {
        ui->tape->addWidget(this->elems[i], 0, i);
    }
    elems[5]->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    on_clear_table_btn_clicked();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_right_btn_clicked()
{
    this->list->swapRight();
    update_elems();
}

void Widget::on_left_btn_clicked()
{
    this->list->swapLeft();
    update_elems();
}

void Widget::update_elems() {
    int i = 0;
    for (ListNode *it = list->lbound; it != list->rbound->next; it = it->next) {
        elems[i]->setText(it->data);
        ++i;
    }
    next_col = 0;
}



void Widget::on_lineEdit_returnPressed()
{
    delete this->list;
    QString str = ui->lineEdit->text();
    this->list = new List(11);
    std::set<QChar> all_characters;

    ListNode *ptr = list->begin;
    for (int i = 0; i < str.size(); ++i) {
        if (ptr == nullptr) {
            list->ins_after(list->end);
            ptr = list->end;
        }
        ptr->data = str[i];
        ptr = ptr->next;
    }

    for (int i = 0; i < 5; ++i) {
        list->swapLeft();
    }

    update_elems();
}

void Widget::on_refresh_tape_btn_clicked()
{
    on_lineEdit_returnPressed();
}

void Widget::on_clear_table_btn_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(1);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList({"q0"}));
    ui->tableWidget->setVerticalHeaderLabels(QStringList({'_'}));
}


void Widget::on_add_char_btn_clicked()
{
    DialogAddChar *dlg = new DialogAddChar(this->ui->tableWidget, this);
    dlg->show();
}

void Widget::on_add_event_btn_clicked()
{
    int col_cnt = ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(col_cnt + 1);
    QString num = "";
    int tmp = col_cnt;
    while (tmp != 0) {
        num += '0' + tmp % 10;
        tmp /= 10;
    }
    std::reverse(num.begin(), num.end());
    ui->tableWidget->setHorizontalHeaderItem(col_cnt, new QTableWidgetItem("q" + num));
}

void Widget::on_start_btn_clicked()
{
    programm.clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            programm[ui->tableWidget->verticalHeaderItem(i)->text()[0]].push_back(ui->tableWidget->item(i, j)->text());
        }
    }
    if (ui->fast_mode_radio->isChecked()) {
        make_turn(0);
    } else {
        ui->start_btn->setEnabled(false);
        ui->stop_btn->setEnabled(true);
        tmr = new QTimer;
        tmr->setInterval(500);
        connect(tmr, SIGNAL(timeout()), this, SLOT(update_time()));
        tmr->start();
    }
}

void Widget::make_turn(int col) {
    const QString &command = programm[this->elems[6]->getText()[0]][col];
    if (command.size() == 0) {
        DialogError *dlg = new DialogError;
        dlg->setMessage("Поле не заполнено");
        dlg->show();
        return;
    } else if (command.size() < 2) {
        DialogError *dlg = new DialogError;
        dlg->setMessage("Неверная командочка");
        dlg->show();
        return;
    }
    ListNode *ptr = list->lbound->next->next->next->next->next;
    ptr->data = command[0];
    update_elems();
    if (command[1] == '!') {
        return;
    } else if (command[1] == '<') {
        list->swapLeft();
        update_elems();
    } else if (command[1] == '>') {
        list->swapRight();
        update_elems();
    } else if (command[1] != '|') {
        DialogError *dlg = new DialogError;
        dlg->setMessage("непонтно куда двигать");
        dlg->show();
        return;
    }
    if (command[2] != 'q') {
        DialogError *dlg = new DialogError;
        dlg->setMessage("форматик неверный");
        dlg->show();
        return;
    }
    if (command.size() < 4) {
        DialogError *dlg = new DialogError;
        dlg->setMessage("Непонятное событие");
        dlg->show();
        return;
    }
    int num = 0;
    for (int i = 3; i < command.size(); ++i) {
        num *= 10;
        num += command[i].digitValue();
    }
    make_turn(num);
}

void Widget::update_time() {
    const QString &command = programm[this->elems[5]->getText()[0]][next_col];
    if (command.size() == 0) {
        DialogError *dlg = new DialogError;
        dlg->setMessage("Поле не заполнено");
        dlg->show();
        tmr->stop();
        ui->start_btn->setEnabled(true);
        ui->stop_btn->setEnabled(false);
        return;
    } else if (command.size() < 2) {
        DialogError *dlg = new DialogError;
        dlg->setMessage("Неверная командочка");
        dlg->show();
        tmr->stop();
        ui->start_btn->setEnabled(true);
        ui->stop_btn->setEnabled(false);
        return;
    }
    ListNode *ptr = list->lbound->next->next->next->next->next;
    ptr->data = command[0];
    update_elems();
    if (command[1] == '!') {
        tmr->stop();
        ui->start_btn->setEnabled(true);
        ui->stop_btn->setEnabled(false);
        return;
    } else if (command[1] == '<') {
        list->swapLeft();
        update_elems();
    } else if (command[1] == '>') {
        list->swapRight();
        update_elems();
    } else if (command[1] != '|') {
        DialogError *dlg = new DialogError;
        dlg->setMessage("непонтно куда двигать");
        dlg->show();
        tmr->stop();
        ui->start_btn->setEnabled(true);
        ui->stop_btn->setEnabled(false);
        return;
    }
    if (command[2] != 'q') {
        DialogError *dlg = new DialogError;
        dlg->setMessage("форматик неверный");
        dlg->show();
        tmr->stop();
        ui->start_btn->setEnabled(true);
        ui->stop_btn->setEnabled(false);
        return;
    }
    if (command.size() < 4) {
        DialogError *dlg = new DialogError;
        dlg->setMessage("Непонятное событие");
        dlg->show();
        tmr->stop();
        ui->start_btn->setEnabled(true);
        ui->stop_btn->setEnabled(false);
        return;
    }
    int num = 0;
    for (int i = 3; i < command.size(); ++i) {
        num *= 10;
        num += command[i].digitValue();
    }
    next_col = num;
}


void Widget::on_stop_btn_clicked()
{
    tmr->stop();
    ui->start_btn->setEnabled(true);
    ui->stop_btn->setEnabled(false);
}
