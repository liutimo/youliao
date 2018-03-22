#ifndef YLLOCALSETTING_H
#define YLLOCALSETTING_H

#include <QObject>
#include <QVariant>
class QSettings;

class YLLocalSettings : public QObject
{
    Q_OBJECT
private:
    explicit YLLocalSettings(QObject *parent = nullptr);

public:
    static YLLocalSettings* instance();

    void beginGroup(const QString &);
    void endGroup();

    void setValue(const QString &key, const QVariant &value);
    QVariant getValue(const QString &key);
    int getInt(const QString &key);
    bool getBool(const QString &key);

private:
    QSettings *m_settings;
    static YLLocalSettings* m_instance;
};

#endif // YLLOCALSETTING_H
