#include "alarmdialog.h"
#include "ui_alarmdialog.h"

AlarmDialog::AlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmDialog)
{
    ui->setupUi(this);
    gifMovie = new QMovie(":/gif/russ.gif");
    ui->gifLabel->setMovie(gifMovie);
    ui->gifLabel->setGeometry(QRect(10,10,10+350,10+219));
    gifMovie->start();
}

void AlarmDialog::setText(const QString& text)
{
    ui->textLabel->setText(text);
}

AlarmDialog::~AlarmDialog()
{
    delete ui;
}
