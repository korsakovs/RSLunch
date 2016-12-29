#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QSettings>
#include <QVariant>
#include <QTime>
#include <QtDebug>

#define RSLUNCH_COMPANY_NAME "RSLunch2"
#define RSLUNCH_APP_NAME "RSLunch2"

#define RSLUNCH_DEFAULT_LUNCH_ON_MON false
#define RSLUNCH_DEFAULT_LUNCH_ON_TUE false
#define RSLUNCH_DEFAULT_LUNCH_ON_WED false
#define RSLUNCH_DEFAULT_LUNCH_ON_THU true
#define RSLUNCH_DEFAULT_LUNCH_ON_FRI false

#define RSLUNCH_DEFAULT_FLAG AppSettings::Random
#define RSLUNCH_DEFAULT_LUNCH_TIME QTime(12, 0)

#define RSLUNCH_DEFAULT_DIMA_MODE false
#define RSLUNCH_DEFAULT_LAUNCH_AUTO true

class AppSettings
{
public:
    enum Flag {
        Random,
        Russia,
        Ukraine,
        Belarus,
        Moldova,
        LastFlag // Shuld be last
    };

    static AppSettings* getInstance();
    void configure(const QString& _companyName,
                          const QString& _appName);

    bool lunchOnMon();
    void lunchOnMon(bool);
    bool lunchOnTue();
    void lunchOnTue(bool);
    bool lunchOnWed();
    void lunchOnWed(bool);
    bool lunchOnThu();
    void lunchOnThu(bool);
    bool lunchOnFri();
    void lunchOnFri(bool);

    AppSettings::Flag appFlag();
    AppSettings::Flag randomFlag() const;
    void appFlag(AppSettings::Flag flag);

    QTime lunchTime();
    void lunchTime(const QTime &time);

    bool dimaMode();
    void dimaMode(bool mode);

    bool launchAuto();
    void launchAuto(bool launch);

    void sync();

    ~AppSettings();
private:
    AppSettings();

private:
    static AppSettings* instance;
    QSettings *settings;
    QString appName;
    QString companyName;
};

#endif // APPSETTINGS_H
