#include "lunchdialog.h"
#include "ui_lunchdialog.h"

LunchDialog::LunchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RSLunchDialog)
{
    qsrand(QTime::currentTime().msec());
    appSettings = AppSettings::getInstance();
    lastAlarm = new QTime(QTime::currentTime().addSecs(-61));

    createActions();
    createTrayIcon();
    updateIcon();
    trayIcon->show();

    ui->setupUi(this);

    updateUiBySettings();
    alarmTime = new QTime(appSettings->lunchTime());

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &LunchDialog::checkTimer);
    timer->setInterval(500);
    timer->start();

    alarmDialog = new AlarmDialog();
    alarmDialog->setWindowFlags(Qt::WindowStaysOnTopHint);

#ifdef QT_DEBUG
    testButton = new QPushButton(tr("Test"), this);
    ui->buttonsHorizontalLayout->addWidget(testButton);
    connect(testButton, &QPushButton::clicked, alarmDialog, &QDialog::showNormal);
#endif
}

void LunchDialog::setVisible(bool visible)
{
    settingsAction->setEnabled(!visible);
    QDialog::setVisible(visible);
}

void LunchDialog::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void LunchDialog::createActions()
{
    settingsAction = new QAction(tr("&Settings..."), this);
    connect(settingsAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void LunchDialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(settingsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void LunchDialog::updateIcon()
{
    AppSettings::Flag flag = appSettings->appFlag();

    if (flag == AppSettings::Random) {
        flag = appSettings->randomFlag();
    }
    switch (flag){
    case AppSettings::Russia:
        trayIcon->setIcon(QIcon(":/images/russia.png"));
        break;
    case AppSettings::Ukraine:
        trayIcon->setIcon(QIcon(":/images/ukraine.png"));
        break;
    case AppSettings::Belarus:
        trayIcon->setIcon(QIcon(":/images/belarus.png"));
        break;
    case AppSettings::Moldova:
        trayIcon->setIcon(QIcon(":/images/moldova.png"));
        break;
    }
}

void LunchDialog::accept()
{
    updateSettingsByUi();
    updateIcon();
    alarmTime = new QTime(appSettings->lunchTime());
    QDialog::accept();
}

void LunchDialog::reject()
{
    updateUiBySettings();
    QDialog::reject();
}

void LunchDialog::updateUiBySettings()
{
    ui->mondayCheckBox->setChecked(appSettings->lunchOnMon());
    ui->tuesdayCheckBox->setChecked(appSettings->lunchOnThu());
    ui->wednesdayCheckBox->setChecked(appSettings->lunchOnWed());
    ui->thursdayCheckBox->setChecked(appSettings->lunchOnThu());
    ui->fridayCheckBox->setChecked(appSettings->lunchOnFri());
    ui->lunchTimeEdit->setTime(appSettings->lunchTime());
    int newIndex;
    switch(appSettings->appFlag()){
    case AppSettings::Random:
        newIndex = 0;
        break;
    case AppSettings::Russia:
        newIndex = 1;
        break;
    case AppSettings::Ukraine:
        newIndex = 2;
        break;
    case AppSettings::Belarus:
        newIndex = 3;
        break;
    case AppSettings::Moldova:
        newIndex = 4;
        break;
    default:
        qWarning() << "Bad appFlag value stored in the application settings";
        newIndex = 0;
    }

    ui->iconComboBox->setCurrentIndex(newIndex);
    ui->dimaModeComboBox->setCurrentIndex(
                appSettings->dimaMode() ? 1 : 0
                );
    ui->launchAutoComboBox->setCurrentIndex(
                appSettings->launchAuto() ? 1: 0
                );
}

void LunchDialog::updateSettingsByUi()
{
    appSettings->lunchOnMon(ui->mondayCheckBox->checkState());
    appSettings->lunchOnTue(ui->tuesdayCheckBox->checkState());
    appSettings->lunchOnWed(ui->wednesdayCheckBox->checkState());
    appSettings->lunchOnThu(ui->thursdayCheckBox->checkState());
    appSettings->lunchOnFri(ui->fridayCheckBox->checkState());

    appSettings->lunchTime(ui->lunchTimeEdit->time());

    AppSettings::Flag newFlag;
    switch (ui->iconComboBox->currentIndex()){
    case 0:
        newFlag = AppSettings::Random;
        break;
    case 1:
        newFlag = AppSettings::Russia;
        break;
    case 2:
        newFlag = AppSettings::Ukraine;
        break;
    case 3:
        newFlag = AppSettings::Belarus;
        break;
    case 4:
        newFlag = AppSettings::Moldova;
        break;
    default:
        qWarning() << "Bad value of the Flag Icon Combo Box";
        newFlag = AppSettings::Random;
    }

    appSettings->appFlag(newFlag);
    appSettings->dimaMode(ui->dimaModeComboBox->currentIndex() == 1);
    appSettings->launchAuto(ui->launchAutoComboBox->currentIndex() == 1);

    appSettings->sync();
}

void LunchDialog::checkTimer()
{
    if (alarmTime->hour() == QTime::currentTime().hour() &&
        alarmTime->minute() == QTime::currentTime().minute() &&
        !(QTime::currentTime().hour() == lastAlarm->hour() &&
          QTime::currentTime().minute() == lastAlarm->minute())
        )
    {
        *lastAlarm = QTime::currentTime();
        alarmDialog->show();
    }
}

LunchDialog::~LunchDialog()
{
    delete ui;
}
