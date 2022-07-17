/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCUSTOMMENU_H
#define QCUSTOMMENU_H

#include "qmenu.h"

QT_BEGIN_NAMESPACE

class QCustomMenu : public QMenu
{
public:
    explicit QCustomMenu(QWidget *parent = nullptr) 
        : QMenu(parent)
    {
        setWindowFlags(windowFlags() | Qt::Popup | Qt::FramelessWindowHint
                       | Qt::NoDropShadowWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setStyleSheet(
                "background-color: #FFFFFF;"
                "border-radius: 8px;"
                "margin: 8px;"
                "padding-left: 8px; padding-right: 8px; padding-top: 8px; padding-bottom: 8px;");
        setCursor(Qt::PointingHandCursor);
        setMinimumWidth(100);
    }
    ~QCustomMenu()
    {

    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        int nShadowsWidth = 10; 
        int nRadius = 10; 
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(nShadowsWidth, nShadowsWidth, this->width() - nShadowsWidth * 2,
                            this->height() - nShadowsWidth * 2, nRadius, nRadius);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        painter.fillPath(path, QBrush(Qt::white));

        QColor color(0, 0, 0, 30);
        for (int i = 0; i < nShadowsWidth; i++) {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);

            path.addRoundedRect(nShadowsWidth - i, nShadowsWidth - i,
                                this->width() - (nShadowsWidth - i) * 2,
                                this->height() - (nShadowsWidth - i) * 2, nRadius + i, nRadius + i);

            // path.addRect(nShadowsWidth - i, nShadowsWidth - i, this->width() - (nShadowsWidth -
            // i) * 2, this->height() - (nShadowsWidth - i) * 2);
            color.setAlpha(100 - qSqrt(i) * 40);
            painter.setPen(color);
            painter.drawPath(path);
        }
        QMenu::paintEvent(event);
    }
};


QT_END_NAMESPACE

#endif // QCUSTOMMENU_H
