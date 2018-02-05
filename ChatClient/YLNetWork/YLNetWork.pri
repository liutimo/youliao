HEADERS += \
    $$PWD/common.h \
    $$PWD/ConfigFileReader.h \
    $$PWD/netlib.h \
    $$PWD/os.h \
    $$PWD/UtilPdu.h \
    $$PWD/YLBaseSocket.h \
    $$PWD/YLConn.h \
    $$PWD/YLEventDispatch.h \
    $$PWD/YLPduBase.h \
    $$PWD/protobuf/YLBase.pb.h \
    $$PWD/protobuf/YLLogin.pb.h \
    $$PWD/netservice.h

SOURCES += \
    $$PWD/ConfigFileReader.cpp \
    $$PWD/netlib.cpp \
    $$PWD/UtilPdu.cpp \
    $$PWD/YLBaseSocket.cpp \
    $$PWD/YLConn.cpp \
    $$PWD/YLEventDispatch.cpp \
    $$PWD/YLPduBase.cpp \
    $$PWD/protobuf/YLBase.pb.cc \
    $$PWD/protobuf/YLLogin.pb.cc \
    $$PWD/netservice.cpp

DISTFILES += \
    $$PWD/protobuf/YLBase.proto \
    $$PWD/protobuf/YLLogin.proto

