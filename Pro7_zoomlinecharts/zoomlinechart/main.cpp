/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//#include "chart.h"
//#include "chartview.h"
#include <QtWidgets/QApplication>
//#include <QtWidgets/QMainWindow>
//#include <QtCore/QtMath>
//#include <QtCore/QRandomGenerator>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QValueAxis>
#include "mainwindow.h"

//#include "iostream"
//#include "QTextStream"
//#include "QDebug"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow window;
    window.resize(900, 700);
    window.grabGesture(Qt::PanGesture);
    window.grabGesture(Qt::PinchGesture);
    window.show();

    // window2
    MainWindow window2;
    window2.resize(800, 600);
    window2.grabGesture(Qt::PanGesture);
    window2.grabGesture(Qt::PinchGesture);
    window2.show();


    return a.exec();
}
