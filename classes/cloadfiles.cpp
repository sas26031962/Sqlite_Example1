#include "cloadfiles.h"

bool cLoadFiles::IsLinux = false;
bool cLoadFiles::IsWindows = false;
bool cLoadFiles::IsUTF8 = false;
bool cLoadFiles::IsWindows1251 = true;
QString cLoadFiles::qsProgramPath;
QString cLoadFiles::qsSourceFileName = "/data/Text.txt";


cLoadFiles::cLoadFiles()
{
    //...
}

//=============================================================================

bool cLoadFiles::saveStringListToFile(const QString& fileName, const QStringList& list)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    else
    {
        // Установка кодировки
        QTextStream out(&file);
        if(cLoadFiles::IsWindows1251)
        {
            out.setCodec("Windows-1251");
            qDebug() << "Set Codec: Windows-1251";
        }
        else if(cLoadFiles::IsUTF8)
        {
            out.setCodec("UTF-8");
            qDebug() << "Set Codec: UTF-8";
        }
        else
        {
            out.setCodec("UTF-8");
            qDebug() << "Set Codec: UTF-8";
        }

        for (const QString& str : list) {
            out << str << "\n";
        }

        file.close();
        return true;
    }
}

//=============================================================================

QStringList cLoadFiles::loadStringListFromFile(const QString& fileName)
{
    QStringList list;
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        if(cLoadFiles::IsWindows1251)
        {
            in.setCodec("Windows-1251");
            qDebug() << "Set Codec: Windows-1251";
        }
        else if(cLoadFiles::IsUTF8)
        {
            in.setCodec("UTF-8");
            qDebug() << "Set Codec: UTF-8";
        }
        else
        {
            in.setCodec("UTF-8");
            qDebug() << "Set Codec: UTF-8";
        }


        while (!in.atEnd()) {
            list << in.readLine();
        }

        file.close();
    }
    return list;
}

//=============================================================================

