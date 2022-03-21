#ifndef SCROLLAREAELEM_H
#define SCROLLAREAELEM_H

#include <QWidget>

namespace Ui {
class ScrollAreaElem;
}

class ScrollAreaElem : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollAreaElem(QWidget *parent = nullptr);
    ~ScrollAreaElem();
    void setText(const QString &str);
    QString getText();

private:
    Ui::ScrollAreaElem *ui;
};

#endif // SCROLLAREAELEM_H
