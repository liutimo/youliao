#ifndef YLFILE_H
#define YLFILE_H

#include <QObject>

class YLFile : public QObject
{
    Q_OBJECT
public:
    explicit YLFile(QObject *parent = nullptr);
    YLFile(const YLFile&);
    YLFile&operator =(const YLFile&);
    bool operator ==(const YLFile &);

    void setFilePath(const QString &path);
    void setFileSize(uint32_t size);

    QString     getFilePath() const;
    uint32_t    getFileSize() const;
    QString     getFileName() const;
    QString     getFileSizeString();

private:
    QString humanReadableSize(const uint32_t &size, int precision);

    QString  m_file_path;
    uint32_t m_file_size;
};

#endif // YLFILE_H
