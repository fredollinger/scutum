/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QTextDocument>
#include <QtNetwork>
#include "ftpreply.h"

FtpReply::FtpReply(const QUrl &url)
    : QNetworkReply()
{
    ftp = new QFtp(this);
    connect(ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(processListInfo(QUrlInfo)));
    connect(ftp, SIGNAL(readyRead()), this, SLOT(processData()));
    connect(ftp, SIGNAL(commandFinished(int, bool)), this, SLOT(processCommand(int, bool)));

    offset = 0;
    units = QStringList() << "bytes" << "K" << "M" << "G" << "Ti" << "Pi"
                          << "Ei" << "Zi" << "Yi";

    setUrl(url);
    ftp->connectToHost(url.host());
}

void FtpReply::processCommand(int, bool err)
{
    if (err) {
        setError(ContentNotFoundError, "Unknown command");
        emit error(ContentNotFoundError);
        return;
    }

    switch (ftp->currentCommand()) {
    case QFtp::ConnectToHost:
        ftp->login();
        break;

    case QFtp::Login:
        ftp->list(url().path());
        break;

    case QFtp::List:
        if (items.size() == 1)
            ftp->get(url().path());
        else
            setListContent();
        break;

    case QFtp::Get:
        setContent();

    default:
        ;
    }
}

void FtpReply::processListInfo(const QUrlInfo &urlInfo)
{
    items.append(urlInfo);
}

void FtpReply::processData()
{
    content += ftp->readAll();
}

void FtpReply::setContent()
{
    open(ReadOnly | Unbuffered);
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));
    emit readyRead();
    emit finished();
    ftp->close();
}

void FtpReply::setListContent()
{
    QUrl u = url();
    if (!u.path().endsWith("/"))
        u.setPath(u.path() + "/");

    QString base_url = url().toString();
    QString base_path = u.path();

    open(ReadOnly | Unbuffered);
    QString content(
        "<html>\n"
        "<head>\n"
        "  <title>" + Qt::escape(base_url) + "</title>\n"
        "  <style type=\"text/css\">\n"
        "  th { background-color: #aaaaaa; color: black }\n"
        "  table { border: solid 1px #aaaaaa }\n"
        "  tr.odd { background-color: #dddddd; color: black\n }\n"
        "  tr.even { background-color: white; color: black\n }\n"
        "  </style>\n"
        "</head>\n\n"
        "<body>\n"
        "<h1>Listing for " + base_path + "</h1>\n\n"
        "<table align=\"center\" cellspacing=\"0\" width=\"90%\">\n"
        "<tr><th>Name</th><th>Size</th></tr>\n");

    QUrl parent = u.resolved(QUrl(".."));

    if (parent.isParentOf(u))

        content += QString("<tr><td><strong><a href=\"" + parent.toString() + "\">"
            "Parent directory</a></strong></td><td></td></tr>\n");

    int i = 0;
    foreach (const QUrlInfo &item, items) {

        QUrl child = u.resolved(QUrl(item.name()));

        if (i == 0)
            content += QString("<tr class=\"odd\">");
        else
            content += QString("<tr class=\"even\">");

        content += QString("<td><a href=\"" + child.toString() + "\">"
                           + Qt::escape(item.name()) + "</a></td>");

        qint64 size = item.size();
        int unit = 0;
        while (size) {
            qint64 new_size = size/1024;
            if (new_size && unit < units.size()) {
                size = new_size;
                unit += 1;
            } else
                break;
        }

        if (item.isFile())
            content += QString("<td>" + QString::number(size) + " "
                               + units[unit] + "</td></tr>\n");
        else
            content += QString("<td></td></tr>\n");

        i = 1 - i;
    }

    content += QString("</table>\n"
                       "</body>\n"
                       "</html>\n");

    this->content = content.toUtf8();

    setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/html; charset=UTF-8"));
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(this->content.size()));
    emit readyRead();
    emit finished();
    ftp->close();
}

// QIODevice methods
    
void FtpReply::abort()
{
}

qint64 FtpReply::bytesAvailable() const
{
    return content.size() - offset;
}

bool FtpReply::isSequential() const
{
    return true;
}

qint64 FtpReply::readData(char *data, qint64 maxSize)
{
    if (offset < content.size()) {
        qint64 number = qMin(maxSize, content.size() - offset);
        memcpy(data, content.constData() + offset, number);
        offset += number;
        return number;
    } else
        return -1;
}
