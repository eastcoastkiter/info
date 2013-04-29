HEADERS       = application.h \
                closeEvent.h \
                cmdprocess.h
 
SOURCES       = application.cpp \
                main.cpp \
                cmdprocess.cpp

TRANSLATIONS =  application_de.ts \
                application_en.ts

CODECFORTR    = ISO-8859-1
RESOURCES     += application.qrc

# install
target.path = .
#sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS tools.pro README
#sources.path = $$[QT_INSTALL_EXAMPLES]/tools
INSTALLS += target
QT += network
CONFIG += qt release
#CONFIG += qt ordered static debug
LFLAGS = -static-libgcc
QMAKE_LFLAGS += -static-libgcc









