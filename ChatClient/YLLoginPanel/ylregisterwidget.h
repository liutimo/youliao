#ifndef YLREGISTERWIDGET_H
#define YLREGISTERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWidget; }
class QLabel;
class LoadingWidget;
class QMovie;
class QPushButton;
QT_END_NAMESPACE

class YLRegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLRegisterWidget(QWidget *parent = nullptr);

signals:

public slots:

private slots:
    void on_registerButton_clicked();

    void on_pushButton_clicked();

private:
    void uploadImage(const QString &fileName);

    Ui::RegisterWidget *ui;
    QString m_image_url;

    bool m_header_uploaded;
    LoadingWidget  *m_loading_widget;

};


class LoadingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadingWidget(QWidget *parent = nullptr);
    void registerSuccess(const QString &account);
    void registerFailed();

signals:
    void closeClicked(bool success);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QLabel  *m_load;
    bool    m_success;
    QLabel  *m_account;
    QMovie  *m_movie;
    QPushButton *m_login;
};




#endif // YLREGISTERWIDGET_H
