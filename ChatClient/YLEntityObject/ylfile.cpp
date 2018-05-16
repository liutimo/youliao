#include "ylfile.h"
#include <QCoreApplication>

YLFile::YLFile(QObject *parent) : QObject(parent)
{

}

YLFile::YLFile(const YLFile &f)
{
    m_file_path = f.m_file_path;
    m_file_size = f.m_file_size;
}

YLFile& YLFile::operator =(const YLFile &f)
{
    m_file_path = f.m_file_path;
    m_file_size = f.m_file_size;
    return *this;
}

bool YLFile::operator ==(const YLFile &f)
{
    if (f.m_file_path == m_file_path)
        return true;
    else
        return false;

}

void YLFile::setFilePath(const QString &path)
{
    m_file_path = path;
}

void YLFile::setFileSize(uint32_t size)
{
    m_file_size = size;
}

QString YLFile::getFilePath() const
{
    return m_file_path;
}

uint32_t YLFile::getFileSize() const
{
    return m_file_size;
}

QString YLFile::getFileName() const
{

}

QString YLFile::getFileSizeString()
{
    return humanReadableSize(m_file_size, 2);
}

QString YLFile::humanReadableSize(const uint32_t &size, int precision)
{
    double sizeAsDouble = size;
    static QStringList measures;
    if (measures.isEmpty())
        measures << QCoreApplication::translate("QInstaller", "bytes")
                 << QCoreApplication::translate("QInstaller", "KB")
                 << QCoreApplication::translate("QInstaller", "MB")
                 << QCoreApplication::translate("QInstaller", "GB")
                 << QCoreApplication::translate("QInstaller", "TB")
                 << QCoreApplication::translate("QInstaller", "PB")
                 << QCoreApplication::translate("QInstaller", "EB")
                 << QCoreApplication::translate("QInstaller", "ZB")
                 << QCoreApplication::translate("QInstaller", "YB");
    QStringListIterator it(measures);
    QString measure(it.next());
    while (sizeAsDouble >= 1024.0 && it.hasNext()) {
        measure = it.next();
        sizeAsDouble /= 1024.0;
    }
    return QString::fromLatin1("%1 %2").arg(sizeAsDouble, 0, 'f', precision).arg(measure);
}
