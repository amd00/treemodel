MOC_DIR = .moc
OBJECTS_DIR = .obj

QT -= gui

VER_MAJ = 1
VER_MIN = 5
VER_PAT = 2

CONFIG += build_all static_and_shared
CONFIG(static, static|shared){
	TARGET = treemodelS
}
else{
	TARGET = treemodel
}

TEMPLATE = lib

QMAKE_LFLAGS_SONAME += -Wl,-soname,lib$${TARGET}.so.$${VER_MAJ}.$${VER_MIN}

SOURCES += treemodel.cpp \
    treeitem.cpp

HEADERS += treemodel.h\
    treeitem.h

target.path = /orion/lib
includes.files = $$HEADERS
includes.path = /orion/include

INSTALLS += target includes
