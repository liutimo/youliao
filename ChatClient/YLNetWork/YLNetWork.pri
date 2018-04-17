DISTFILES += \ss
    $$PWD/base/log4cxx.properties

HEADERS += \
    $$PWD/base/BaseConn.h \
    $$PWD/base/BasePdu.h \
    $$PWD/base/BasicSocket.h \
    $$PWD/base/EventDispatch.h \
    $$PWD/base/Lock.h \
    $$PWD/base/log.h \
    $$PWD/base/netlib.h \
    $$PWD/base/netlibservice.h \
    $$PWD/base/SimpleBuffer.h \
    $$PWD/base/Thread.h \
    $$PWD/base/type_define.h \
    $$PWD/base/util.h \
    $$PWD/login/loginconn.h \
    $$PWD/login/msgservconn.h \
    $$PWD/ylnetservice.h \
    $$PWD/pdusender.h \
    $$PWD/ylbusiness.h \
    $$PWD/pduhandler.h \
    $$PWD/http/httphelper.h

SOURCES += \
    $$PWD/base/BaseConn.cpp \
    $$PWD/base/BasePdu.cpp \
    $$PWD/base/BasicSocket.cpp \
    $$PWD/base/EventDispatch.cpp \
    $$PWD/base/Lock.cpp \
    $$PWD/base/log.cpp \
    $$PWD/base/netlibservice.cpp \
    $$PWD/base/SimpleBuffer.cpp \
    $$PWD/base/Thread.cpp \
    $$PWD/base/util.cpp \
    $$PWD/login/loginconn.cpp \
    $$PWD/login/msgservconn.cpp \
    $$PWD/ylnetservice.cpp \
    $$PWD/pdusender.cpp \
    $$PWD/ylbusiness.cpp \
    $$PWD/pduhandler.cpp \
    $$PWD/http/httphelper.cpp

