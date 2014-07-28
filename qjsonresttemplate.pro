TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp \
    qjsonresttemplate.cpp \
    testclass.cpp \
    builder.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    qjsonresttemplate.h \
    testclass.h \
    builder.h \
    types.h \
    JsonClassInterface.h

OTHER_FILES += \
    schema.json
