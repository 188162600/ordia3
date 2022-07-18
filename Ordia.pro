QT       += core gui widgets core-private gui-private widgets-private


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractinterativeitem.cpp \
    checkpoint.cpp \
    enemy.cpp \
    gamescene.cpp \
    global.cpp \
    iteratorange.cpp \
    main.cpp \
    math2d.cpp \
    myalgorithm.cpp \
    protagonist.cpp \
    rock.cpp \
    spikes.cpp \
    spit.cpp \
    spitter.cpp \
    stickpoint.cpp \
    trajectory.cpp \
    trajectoryindicator.cpp

HEADERS += \
    abstractinterativeitem.h \
    checkpoint.h \
    enemy.h \
    gamescene.h \
    global.h \
    iteratorange.h \
    math2d.h \
    myalgorithm.h \
    private/abstractinterativeitem_p.h \
    private/abstractprotagonist_p.h \
    private/stickpoint_p.h \
    protagonist.h \
    rock.h \
    spikes.h \
    spit.h \
    spitter.h \
    stickpoint.h \
    trajectory.h \
    trajectoryindicator.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
