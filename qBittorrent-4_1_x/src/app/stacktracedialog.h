/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2015 The qBittorrent project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 */

#ifndef STACKTRACEDIALOG_H
#define STACKTRACEDIALOG_H

#include <QString>
#include <QDialog>

#include "base/utils/misc.h"
#include "ui_stacktracedialog.h"

class StacktraceDialog : public QDialog, private Ui::StacktraceDialog
{
    Q_OBJECT

public:
    StacktraceDialog(QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setupUi(this);
    }

    void setStacktraceString(const QString &sigName, const QString &trace)
    {
        // try to call Qt function as less as possible
        QString htmlStr = QString(
            "<p align=center><b><font size=7 color=red>"
            "LoTo has crashed"
            "</font></b></p>"
            "<font size=4><p>"
            "Please file a bug report at "
            "<a href=\"http://bugs.qbittorrent.org\">http://bugs.qbittorrent.org</a> "
            "and provide the following information:"
            "</p></font>"
            "<br/><hr><br/>"
            "<p align=center><font size=4>"
#if defined(__x86_64__) || defined(_M_X64)
            "LoTo version: " QBT_VERSION " (64-bit)<br/>"
#else
            "LoTo version: " QBT_VERSION " (32-bit)<br/>"
#endif
            "Libtorrent version: %1<br/>"
            "Qt version: " QT_VERSION_STR "<br/>"
            "Boost version: %2<br/>"
            "OS version: %3<br/><br/>"
            "Caught signal: %4"
            "</font></p>"
            "<pre><code>%5</code></pre>"
            "<br/><hr><br/><br/>")
                .arg(Utils::Misc::libtorrentVersionString())
                .arg(Utils::Misc::boostVersionString())
                .arg(Utils::Misc::osName())
                .arg(sigName)
                .arg(trace);

        errorText->setHtml(htmlStr);
    }
};

#endif // STACKTRACEDIALOG_H
