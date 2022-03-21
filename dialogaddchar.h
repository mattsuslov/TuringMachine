#ifndef DIALOGADDCHAR_H
#define DIALOGADDCHAR_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class DialogAddChar;
}

class DialogAddChar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddChar(QTableWidget *tab, QWidget *parent = nullptr);
    ~DialogAddChar();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogAddChar *ui;
    QTableWidget *table;
};

#endif // DIALOGADDCHAR_H
