#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QIODevice>
#include "../Trucker/TruckerModel.h"

class FileParser
{
public:
    FileParser();

    bool fileOpen();
    bool setFilePath(const QString &fileName);
    bool parseFile(TruckerModel &truckerModel);

private:
    QFile *m_file;
};

#endif // FILEPARSER_H
