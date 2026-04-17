#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>
#include <QString>
#include <QCoreApplication>

class AppConfig{

public:
    static AppConfig& instance() {
            static AppConfig inst;
            return inst;
        }
private:
    // Khai báo con trỏ để quản lý đối tượng QSettings
    QSettings *m_settings;

private:
    AppConfig() {
        QString path = QCoreApplication::applicationDirPath() + "/settings.ini";
        m_settings = new QSettings(path, QSettings::IniFormat);
    }
public:
    void savePwdHash(const QString &pwd){
        m_settings->setValue("Auth/Pwd", pwd);
    }

    QString getPwdHash(){
        return m_settings->value("Auth/Pwd").toString();
    }
};

#endif // APPCONFIG_H
