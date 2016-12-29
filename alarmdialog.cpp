#include "alarmdialog.h"
#include "ui_alarmdialog.h"

AlarmDialog::AlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmDialog)
{
    ui->setupUi(this);
    gifMovie = new QMovie(":/gif/russ.gif");
    ui->label->setMovie(gifMovie);
    ui->label->setGeometry(QRect(10,10,10+350,10+219));
    gifMovie->start();
}

AlarmDialog::~AlarmDialog()
{
    delete ui;
}
