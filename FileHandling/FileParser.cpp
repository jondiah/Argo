#include "FileParser.h"
#include "../Trucker/TruckerItem.h"

#include <QDebug>
#include <QUrl>

FileParser::FileParser() :
    m_file(NULL)
{
}

bool FileParser::fileOpen()
{
    if(m_file != NULL) {
        return m_file->isOpen();
    } else {
        return false;
    }
}

bool FileParser::setFilePath(const QString &fileName)
{
    QUrl url(fileName);
    QString projectFilePath = url.toString();

    m_file = new QFile(projectFilePath);

    if(!m_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file: " << projectFilePath;
        return false;
    }
    return true;
}

bool FileParser::parseFile(TruckerModel &truckerModel)
{
    if(fileOpen()) {
        QTextStream stream(m_file);
        QStringList splitedLine;
        QString name;
        qreal lat, lon;

        QString line;
        do  {
            splitedLine.clear();
            line = stream.readLine();
            qDebug() << "Line: " << line;

            splitedLine = line.split(",");

            if(splitedLine.count() > 1) {
                name = splitedLine.at(0);
                lat = splitedLine.at(1).toFloat();
                lon = splitedLine.at(2).toFloat();
                truckerModel.appendRow(new TruckerItem(name, lat, lon));
            }
        } while (!line.isNull());

        return true;
    } else {
        return false;
    }
}


