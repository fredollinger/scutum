/*
 * Scutum
 *
 * SidePane:
 * 
 * Side Panel
 *
 * Copyright (C) 2012 Fred Ollinger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>
#include <QUrl>

#include "sidepane.hpp"
#include "jsondelicious.hpp"

namespace scutum{
SidePane::SidePane(QWidget *pParent)
    : QWidget(pParent)
    , m_query_mode(SCUTUM_DELICIOUS_MODE_RECENT)
    , m_refresh(true)
{
	setupUi(this);
  m_net = new QNetworkAccessManager(this);

  m_latest = new JsonDelicious();
  m_rss = new JsonDelicious();
  m_links = new JsonDelicious();

  connect(recentButton, 
    SIGNAL(clicked()),
    SLOT(getBookmarks()));

  connect(rssButton, 
    SIGNAL(clicked()),
    SLOT(getRSS()));

  connect(m_net, SIGNAL(finished(QNetworkReply*)),
                   this, SLOT(replyFinished(QNetworkReply*)));

  connect(closeButton, SIGNAL(clicked()),
                   this, SLOT(hide()));

  connect(refreshButton, SIGNAL(clicked()),
                   this, SLOT(refresh()));

  rssButton->setChecked(true);
  getRSS();
  //closeButton->setIcon(QIcon(":/resources/images/window-close.png"));
}

void SidePane::replyFinished(QNetworkReply *reply){
  qDebug() << __PRETTY_FUNCTION__;

  QString data = QString(reply->readAll());
  m_links->setData(data);

  if ( SCUTUM_DELICIOUS_MODE_RSS == m_query_mode )
    m_rss->setData(data);
  else if ( SCUTUM_DELICIOUS_MODE_RECENT == m_query_mode )
    m_latest->setData(data);

	addItems ( m_links );
}

void SidePane::getBookmarks(){
  qDebug() << __PRETTY_FUNCTION__;
  m_query_mode = SCUTUM_DELICIOUS_MODE_RECENT;

  if (m_latest->size() > 0 && false == m_refresh){
    qDebug() << __PRETTY_FUNCTION__ << m_latest->size();
    linkList->clear();
	  addItems ( m_latest );
    return;
  }

  QSettings settings;
  QString user = settings.value("Delicious:User").toString();
  QString url = "http://api.del.icio.us/v2/json/" + user; 
  m_net->get(QNetworkRequest(QUrl(url)));

}

void SidePane::refresh(){
  m_refresh=true;
  if (true == rssButton->isChecked()) getRSS();
  else if (true == recentButton->isChecked()) getBookmarks();
}

void SidePane::getRSS(){
  m_query_mode = SCUTUM_DELICIOUS_MODE_RSS;

        // http://feeds.delicious.com/v2/json/follinge/strange

  if (m_rss->size() > 0 && false == m_refresh){
    qDebug() << __PRETTY_FUNCTION__ << m_rss->size();
    linkList->clear();
	  addItems ( m_rss );
    return;
  }

  qDebug() << __PRETTY_FUNCTION__ << " Getting rss feeds ";
  QSettings settings;
  QString user = settings.value("Delicious:User").toString();
  QString url = "http://feeds.delicious.com/v2/json/" + user +"/atom"; 
  m_net->get(QNetworkRequest(QUrl(url)));
}

void SidePane::addItems(JsonDelicious *jsond){
	QMap <QString, QUrl> map = jsond->titlelinks();

//  if (map.size() < 1) return;
  linkList->clear();

   QMapIterator<QString, QUrl> i(map);
    while (i.hasNext()) {
      i.next();
      // do not include empty strings
      if (i.key().size() < 1 || i.value().toString().size() < 1) continue;
      QVariant var(i.value());
		  QListWidgetItem *item = new QListWidgetItem(i.key());
      item->setData(Qt::UserRole, var);
		  linkList->addItem(item);
    }

  m_refresh = false;
	return;
}

} // namespace scutum
