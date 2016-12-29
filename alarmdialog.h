#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget *parent = 0);
    ~AlarmDialog();

    void setText(const QString& text);

private:
    Ui::AlarmDialog *ui;
    QMovie *gifMovie;
};

#endif // ALARMDIALOG_H
