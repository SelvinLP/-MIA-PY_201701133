QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Administrador_UsuyGrup/admin_usuariosygrupos.cpp \
        Administrador_UsuyGrup/permisos.cpp \
        Analizadores/analizador.cpp \
        Analizadores/analizador_caracteres_o.cpp \
        Structs/bitmap.cpp \
        Structs/bloque_journali.cpp \
        Structs/bloqueapuntador.cpp \
        Structs/bloquearchivo.cpp \
        Structs/bloquecarpeta.cpp \
        Structs/superbloque.cpp \
        Structs/tablainodo.cpp \
        Users/structs_users.cpp \
        admin_archivos.cpp \
        admin_disco.cpp \
        admin_particiones.cpp \
        graficar_reportes.cpp \
        main.cpp \
        nodo_mount.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Administrador_UsuyGrup/admin_usuariosygrupos.h \
    Administrador_UsuyGrup/permisos.h \
    Analizadores/analizador.h \
    Analizadores/analizador_caracteres_o.h \
    Structs/bitmap.h \
    Structs/bloque_journali.h \
    Structs/bloqueapuntador.h \
    Structs/bloquearchivo.h \
    Structs/bloquecarpeta.h \
    Structs/superbloque.h \
    Structs/tablainodo.h \
    Users/structs_users.h \
    admin_archivos.h \
    admin_disco.h \
    admin_particiones.h \
    graficar_reportes.h \
    nodo_mount.h
