purge.commands = find . -name \'*~\' -exec rm {} \;
QMAKE_EXTRA_TARGETS += purge

CONFIG	    += qt release warn_on
DEFINES     +=
LANGUAGE    = C++
QMAKE_CLEAN += QUnix
QT	    += concurrent

contains(QMAKE_HOST.arch, armv7l) {
QMAKE_CXXFLAGS_RELEASE += -march=armv7
}

contains(QMAKE_HOST.arch, ppc) {
QMAKE_CXXFLAGS_RELEASE += -mcpu=powerpc -mtune=powerpc
}

QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2

freebsd-* {
QMAKE_CXXFLAGS_RELEASE += -Wall \
                          -Wcast-align \
                          -Wcast-qual \
                          -Werror \
                          -Wextra \
                          -Wformat=2 \
                          -Woverloaded-virtual \
                          -Wpointer-arith \
                          -Wstack-protector \
                          -Wstrict-overflow=5 \
                          -Wundef \
                          -fPIE \
                          -fstack-protector-all \
                          -funroll-loops \
                          -fwrapv \
                          -pedantic \
                          -std=c++17
} else:macx {
QMAKE_CXXFLAGS_RELEASE += -Wall \
                          -Wcast-align \
                          -Wcast-qual \
                          -Wenum-compare \
                          -Wextra \
                          -Wformat=2 \
                          -Wno-c++20-attribute-extensions \
                          -Woverloaded-virtual \
                          -Wpointer-arith \
                          -Wstack-protector \
                          -Wstrict-overflow=5 \
                          -Wundef \
                          -fPIE \
                          -fstack-protector-all \
                          -funroll-loops \
                          -fwrapv \
                          -pedantic \
                          -std=c++17
QMAKE_MACOSX_DEPLOYMENT_TARGET = 12.0
} else {
QMAKE_CXXFLAGS_RELEASE += -Wall \
                          -Wcast-qual \
                          -Wdouble-promotion \
                          -Wenum-compare \
                          -Wextra \
                          -Wfloat-equal \
                          -Wformat=2 \
                          -Wformat-overflow=2 \
                          -Wl,-z,relro \
                          -Wlogical-op \
                          -Wno-class-memaccess \
                          -Wno-deprecated-copy \
                          -Wold-style-cast \
                          -Woverloaded-virtual \
                          -Wpointer-arith \
                          -Wstack-protector \
                          -Wstrict-overflow=5 \
                          -Wstringop-overflow=4 \
                          -Wzero-as-null-pointer-constant \
                          -Wundef \
                          -fPIE \
                          -fstack-protector-all \
                          -funroll-loops \
                          -fwrapv \
                          -pedantic \
                          -pie \
                          -std=c++17
contains(QMAKE_HOST.arch, ppc) {
QMAKE_CXXFLAGS_RELEASE -= -Wformat-overflow=2 \
                          -Wstringop-overflow=4
}
}

greaterThan(QT_MAJOR_VERSION, 5) {
QMAKE_CXXFLAGS_RELEASE += -std=c++17
QMAKE_CXXFLAGS_RELEASE -= -std=c++11
}

QMAKE_DISTCLEAN += -f .qmake* \
                   -fr Temporary

QMAKE_STRIP = echo

HEADERS	    += Source/qunix-user.h
INCLUDEPATH += Source
SOURCES     = qunix.cc

MOC_DIR     = Temporary/moc
OBJECTS_DIR = Temporary/obj
RCC_DIR     = Temporary/rcc

PROJECTNAME  = QUnix
TARGET       = QUnix
TEMPLATE     = app
TRANSLATIONS =
