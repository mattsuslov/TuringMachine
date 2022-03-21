#include "scrollareaelem.h"
#include "ui_scrollareaelem.h"

ScrollAreaElem::ScrollAreaElem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrollAreaElem)
{
    ui->setupUi(this);
}

ScrollAreaElem::~ScrollAreaElem()
{
    delete ui;
}

void ScrollAreaElem::setText(const QString &str) {
    ui->label->setText(str);
}

QString ScrollAreaElem::getText() {
    return ui->label->text();
}
