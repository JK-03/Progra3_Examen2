QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Estudiante.cpp \
    EstudianteLicenciatura.cpp \
    Vehiculo.cpp \
    articulocientifico.cpp \
    automovil.cpp \
    camion.cpp \
    empleado.cpp \
    empleadocontratado.cpp \
    empleadofijo.cpp \
    empresa.cpp \
    estudiantemaestria.cpp \
    flota.cpp \
    libro.cpp \
    main.cpp \
    cframe.cpp \
    publicacion.cpp \
    revista.cpp

HEADERS += \
    Estudiante.h \
    EstudianteLicenciatura.h \
    Vehiculo.h \
    articulocientifico.h \
    automovil.h \
    camion.h \
    cframe.h \
    empleado.h \
    empleadocontratado.h \
    empleadofijo.h \
    empresa.h \
    estudiantemaestria.h \
    flota.h \
    libro.h \
    publicacion.h \
    revista.h

FORMS += \
    cframe.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
