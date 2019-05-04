QT += charts

HEADERS += \
    chart.h \
    chartview.h \
    mainwindow.h

SOURCES += \
    main.cpp \
    chart.cpp \
    chartview.cpp \
    mainwindow.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/zoomlinechart
INSTALLS += target

CONFIG+= console
