#ifndef LUNCHDIALOG_H
#define LUNCHDIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include "appsettings.h"
#include "alarmdialog.h"

namespace Ui {
    class RSLunchDialog;
}

class LunchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LunchDialog(QWidget *parent = 0);
    ~LunchDialog();

    void setVisible(bool visible) Q_DECL_OVERRIDE;

protected:
    void createActions();
    void createTrayIcon();
    void updateUiBySettings();
    void updateSettingsByUi();

protected slots:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void accept() Q_DECL_OVERRIDE;
    void reject() Q_DECL_OVERRIDE;
    void updateIcon();
    void checkTimer();

private:
    Ui::RSLunchDialog *ui;

    QAction *settingsAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QTimer *timer;
    QTime *alarmTime;
    QTime *lastAlarm;

    AppSettings *appSettings;
    AlarmDialog *alarmDialog;

#ifdef QT_DEBUG
    QPushButton *testButton;
#endif
};

#endif // LUNCHDIALOG_H
