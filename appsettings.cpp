#include "appsettings.h"

AppSettings* AppSettings::getInstance()
{
    if (!AppSettings::instance)
    {
        AppSettings::instance = new AppSettings();
    }
    return AppSettings::instance;
}

void AppSettings::configure(const QString &_companyName, const QString &_appName)
{
    this->sync();
    settings->deleteLater();
    companyName = _companyName;
    appName     = _appName;
    settings = new QSettings(companyName, appName);
}

bool AppSettings::lunchOnMon()
{
    return settings->value("days/mon", RSLUNCH_DEFAULT_LUNCH_ON_MON).toBool();
}

void AppSettings::lunchOnMon(bool lunch)
{
    settings->setValue("days/mon", lunch);
}

bool AppSettings::lunchOnTue()
{
    return settings->value("days/tue", RSLUNCH_DEFAULT_LUNCH_ON_TUE).toBool();
}

void AppSettings::lunchOnTue(bool lunch)
{
    settings->setValue("days/tue", lunch);
}

bool AppSettings::lunchOnWed()
{
    return settings->value("days/wed", RSLUNCH_DEFAULT_LUNCH_ON_WED).toBool();
}

void AppSettings::lunchOnWed(bool lunch)
{
    settings->setValue("days/wed", lunch);
}

bool AppSettings::lunchOnThu()
{
    return settings->value("days/thu", RSLUNCH_DEFAULT_LUNCH_ON_THU).toBool();
}

void AppSettings::lunchOnThu(bool lunch)
{
    settings->setValue("days/thu", lunch);
}

bool AppSettings::lunchOnFri()
{
    return settings->value("days/fri", RSLUNCH_DEFAULT_LUNCH_ON_FRI).toBool();
}

void AppSettings::lunchOnFri(bool lunch)
{
    settings->setValue("days/fri", lunch);
}

AppSettings::Flag AppSettings::appFlag()
{
    return static_cast<AppSettings::Flag>(settings->value("flag", RSLUNCH_DEFAULT_FLAG).toInt());
}

AppSettings::Flag AppSettings::randomFlag() const
{
    return static_cast<AppSettings::Flag>(qrand() % (AppSettings::LastFlag - 1) + 1);
}

void AppSettings::appFlag(AppSettings::Flag flag)
{
    settings->setValue("flag", flag);
}

QTime AppSettings::lunchTime()
{
    return settings->value("time", RSLUNCH_DEFAULT_LUNCH_TIME).toTime();
}

void AppSettings::lunchTime(const QTime &time)
{
    settings->setValue("time", time);
}

bool AppSettings::dimaMode()
{
    return settings->value("dimaMode", RSLUNCH_DEFAULT_DIMA_MODE).toBool();
}

void AppSettings::dimaMode(bool mode)
{
    settings->setValue("dimaMode", mode);
}

bool AppSettings::launchAuto()
{
    return settings->value("launchAuto", RSLUNCH_DEFAULT_LAUNCH_AUTO).toBool();
}

void AppSettings::launchAuto(bool launch)
{
    settings->setValue("launchAuto", launch);
}

void AppSettings::sync()
{
    settings->sync();
}

AppSettings::AppSettings()
{
    companyName = RSLUNCH_COMPANY_NAME;
    appName     = RSLUNCH_APP_NAME;
    settings = new QSettings(companyName, appName);
    qsrand(QTime::currentTime().msec());
}

AppSettings::~AppSettings()
{
    settings->deleteLater();
}

AppSettings *AppSettings::instance = 0;

