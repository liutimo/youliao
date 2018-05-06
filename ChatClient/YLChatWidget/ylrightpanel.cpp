#include "ylrightpanel.h"
#include <QPainter>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include "yltransferfiletasklistwidget.h"
YLRightPanel::YLRightPanel(QWidget *parent) : QWidget(parent)
{
    m_tab_widget = new QTabWidget(this);
    hLayout = new QHBoxLayout;
    hLayout->addWidget(m_tab_widget);
    setLayout(hLayout);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);

    YLTransferFileTaskListWidget *w = new YLTransferFileTaskListWidget(this);

    m_tab_widget->addTab(w, "传送文件");
    m_tab_widget->setTabsClosable(true);
    m_tab_widget->tabBar()->setStyleSheet(qss_tab_bar);
    connect(m_tab_widget, &QTabWidget::tabCloseRequested, this, [](int index){
        qDebug() << index;
    });
}

YLRightPanel::~YLRightPanel()
{
    qDebug() << "~YLRightPanel()";
    delete hLayout;
}

void YLRightPanel::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush(Qt::red);
    p.drawRect(rect());
}
