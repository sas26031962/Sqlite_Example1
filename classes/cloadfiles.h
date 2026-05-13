#ifndef CLOADFILES_H
#define CLOADFILES_H

#include <QSettings>
#include <memory>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QTextBrowser>
#include <QDebug>
#include <QTextBlock>

class cLoadFiles
{
    //Атрибуты

public:
    static bool IsLinux;
    static bool IsWindows;
    static bool IsUTF8;
    static bool IsWindows1251;
    static QString qsProgramPath;

    static QString qsSourceFileName;

    QStringList qslListIn;

    //Конструкторы
    cLoadFiles();

    //Методы

    static bool saveStringListToFile(const QString& fileName, const QStringList& list);
    static QStringList loadStringListFromFile(const QString& fileName);
};

#endif // CLOADFILES_H
