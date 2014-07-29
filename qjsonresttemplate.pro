TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp \
    qjsonresttemplate.cpp \
    builder.cpp \
    writecode.cpp \
    writecplusplusclass.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    qjsonresttemplate.h \
    builder.h \
    types.h \
    JsonClassInterface.h \
    writecode.h \
    writecplusplusclass.h

OTHER_FILES += \
    schema.json
