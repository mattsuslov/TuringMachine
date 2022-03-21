#include "dialogaddchar.h"
#include "ui_dialogaddchar.h"

DialogAddChar::DialogAddChar(QTableWidget *tab, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddChar),
    table(tab)
{
    ui->setupUi(this);
}

DialogAddChar::~DialogAddChar()
{
    delete ui;
}

void DialogAddChar::on_buttonBox_accepted()
{
    table->setRowCount(table->rowCount() + 1);
    const QString &str = ui->lineEdit->text();
    if (str.size() != 1) {
        throw "Неверно введён символ!";
    }
    table->setVerticalHeaderItem(table->rowCount() - 1, new QTableWidgetItem(str));
    this->close();
}

void DialogAddChar::on_buttonBox_rejected()
{
    this->close();
}
