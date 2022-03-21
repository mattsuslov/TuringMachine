#ifndef DIALOGERROR_H
#define DIALOGERROR_H

#include <QDialog>

namespace Ui {
class DialogError;
}

class DialogError : public QDialog
{
    Q_OBJECT

public:
    explicit DialogError(QWidget *parent = nullptr);
    ~DialogError();
    void setMessage(const QString& str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogError *ui;
};

#endif // DIALOGERROR_H
