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

#include <QDebug>
#include <QtNetwork>
#include "networkaccessmanager.hpp"
#include "scutcommon.hpp"

NetworkAccessManager::NetworkAccessManager(QNetworkAccessManager *manager, QObject *parent)
    : QNetworkAccessManager(parent)
{
    setCache(manager->cache());
    setCookieJar(manager->cookieJar());
    setProxy(manager->proxy());
    setProxyFactory(manager->proxyFactory());

// BEGIN SET CACHE 
#if 0
  QString cache = QDir::homePath () + SCUT_CACHE;
  QDir cacheDir = QDir(cache);
  if (!cacheDir.mkpath(cache)){
       return;
  }

  //QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
  diskCache->setCacheDirectory(cache);
  setCache(diskCache);
#endif 
// END SET CACHE 
}

QNetworkReply *NetworkAccessManager::createRequest(
    QNetworkAccessManager::Operation operation, const QNetworkRequest &request,
    QIODevice *device)
{
        qDebug() << __PRETTY_FUNCTION__;
        return QNetworkAccessManager::createRequest(operation, request, device);
  // do a request preferred from cache
  //QNetworkRequest request2(QUrl(QString("http://qt.nokia.com")));
  //request2.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  //manager->get(request2);

//    return QNetworkAccessManager::createRequest(operation, request, device);
#if 0
    if (request.url().scheme() != "ftp")
        return QNetworkAccessManager::createRequest(operation, request, device);

    if (operation == GetOperation)
        // Handle ftp:// URLs separately by creating custom QNetworkReply
        // objects.
        return new FtpReply(request.url());
    else
        return QNetworkAccessManager::createRequest(operation, request, device);
#endif
}

void NetworkAccessManager::customContent( QNetworkReply *reply ){
          qDebug() << __PRETTY_FUNCTION__;
}
