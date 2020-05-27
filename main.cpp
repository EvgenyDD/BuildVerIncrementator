#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <QCoreApplication>
#include <QDir>
#include <QThread>
#include <QElapsedTimer>
#include <QDateTime>
#include <stdint.h>




double getDataBetween(QString begin,QString end, QString source)
{
    int startIndex = source.indexOf(begin)+begin.length();
    if(startIndex <= 0) return 0;
    int endIndex = source.indexOf(end,startIndex);
    if(endIndex <= 0) return 0;

    QString number = source.mid(startIndex,endIndex - startIndex);
    return number.toDouble();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QElapsedTimer timerSeed;
    srand(timerSeed.elapsed());

    QFile file("buildVersion.h");

    double verMajor = 1;
    double verMinor = 0;
    double verScaler = 10000;

    QString timeStamp;

    if(file.exists())
    {
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << ">Can't open file to read!";
            return 1;
        }
        else
        {
            QByteArray byteContent = file.readAll();
            QString content = QString(byteContent);
            QStringList list = content.split('\n');

            if(list.size() == 20)
            {
                verScaler = getDataBetween("(",")", list.at(9));
                verMajor = getDataBetween("(",")", list.at(11));
                verMinor = getDataBetween("(",")", list.at(12)) + 1;
                if(verMinor >= verScaler)
                {
                    verMinor = 0;
                    verMajor++;
                }
            }
        }
    }

    file.close();

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << ">Can't open file to write!";
        return 1;
    }
    else
    {
        QDateTime current = QDateTime::currentDateTime();
        timeStamp = current.toString("yyyy-MM-dd hh:mm");

        QByteArray workLog;
        workLog.append("/* Define to prevent recursive inclusion -------------------------------------*/\n");
        workLog.append("#ifndef _BUILD_VERSION_H\n");
        workLog.append("#define _BUILD_VERSION_H\n\n");
        workLog.append("/* WARNING\nDon't modify the file structure!\n*/\n\n");
        workLog.append("/* Exported constants --------------------------------------------------------*/\n");
        workLog.append("#define BUILD_VER_SCALER		(");
        workLog.append(QString::number(verScaler));
        workLog.append(")\n\n");
        workLog.append("#define BUILD_VERSION_MAJOR     (");
        workLog.append(QString::number(verMajor));
        workLog.append(")\n");
        workLog.append("#define BUILD_VERSION_MINOR     (");
        workLog.append(QString::number(verMinor));
        workLog.append(")\n\n");
        workLog.append("#define BUILD_TIMESTAMP         (\"");
        workLog.append(timeStamp);
        workLog.append("\")\n\n");
        workLog.append("#define BUILD_NUMBER			(BUILD_VERSION_MAJOR * BUILD_VER_SCALER + BUILD_VERSION_MINOR)\n\n");
        workLog.append("#endif //_BUILD_VERSION_H\n");

        file.write(workLog);
        file.close();

        qDebug() << ">Current BLD_VER_MAJ=" << verMajor << ", BLD_VER_MIN=" << verMinor << ", TIMESTAMP=" << timeStamp;
        return 0;
    }

    return a.exec();
}
