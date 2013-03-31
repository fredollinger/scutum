
/*
 * Scutum
 *
 * ScutView:
 * 
 * Over rides QWebView
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

#include "scutcommon.hpp"
#include "scutview.hpp"
#include "scututil.hpp"
#include "networkaccessmanager.hpp"
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QProcess>
#include <QWebFrame>
#include <QWebView>

namespace scutum{
ScutView::ScutView(QWidget* pParent) 
	: QWebView(pParent) 
  , m_isLinkHovered(false)
  , m_lastPath(QDir::homePath ())
{
  /* BEGIN REPLACE NETWORK ACCESS MANAGER */
  QNetworkAccessManager *oldManager = page()->networkAccessManager();
  NetworkAccessManager *newManager = new NetworkAccessManager(oldManager, this);
  page()->setNetworkAccessManager(newManager);
  page()->setForwardUnsupportedContent(true);
  //downloader = new Downloader(this, newManager);
  /* END REPLACE NETWORK ACCESS MANAGER */

  connect(page() 
  , SIGNAL(unsupportedContent ( QNetworkReply* )) 
  , newManager
  , SLOT(customContent ( QNetworkReply* )) );

  connect(newManager, SIGNAL(finished(QNetworkReply*)),
                   this, SLOT(replyFinished(QNetworkReply*)));

  connect(page() 
  , SIGNAL(linkHovered ( const QString&, const QString&, const QString&)) 
  , SLOT(linkHovered ( const QString&, const QString&, const QString &)) );

  m_linkMenu = new QMenu();

  QAction* openInNewTabAct = new QAction(tr("Open In New Tab"), this);
  connect(openInNewTabAct, SIGNAL(triggered()), SLOT(openInNewTab()));
  m_linkMenu->addAction(openInNewTabAct);

  QAction* copyLinkAct = new QAction(tr("Copy Link"), this);
  connect(copyLinkAct, SIGNAL(triggered()), SLOT(copyLink()));
  m_linkMenu->addAction(copyLinkAct);

  QAction* saveLinkAct = new QAction(tr("Download Link"), this);
  connect(saveLinkAct, SIGNAL(triggered()), SLOT(saveLink()));
  m_linkMenu->addAction(saveLinkAct);

}

ScutView::~ScutView(){}

void ScutView::showLinkMenu (){
    QPoint pos = QCursor::pos();
    QPoint globalPos = mapToGlobal(pos);

    m_linkMenu->exec(pos);
}

void ScutView::openInNewTab(){
  emit sigOpenInNewTab(QUrl(m_link));
}

void ScutView::contextMenuEvent ( QContextMenuEvent * ev ){
  if (m_isLinkHovered){
    showLinkMenu();
    return;       
  }
	QWebView::contextMenuEvent(ev);
	return;
}

void ScutView::linkHovered ( const QString & link, const QString & title, const QString & textContent ){


  if (link.isEmpty()){
    m_isLinkHovered = false;
    return;
  }

  m_isLinkHovered = true;
  m_link = link;
  m_title = title;
  m_textContent = textContent;
  return;
}

void ScutView::copyLink (){
 QClipboard *clipboard = QApplication::clipboard();
 clipboard->setText(m_link);
}

void ScutView::copyHighlightedText (){
 QClipboard *clipboard = QApplication::clipboard();
 clipboard->setText(selectedText());
}

void ScutView::saveLink (){
  //QString fileName = QFileDialog::getOpenFileName(this,
        //tr("Save File"), m_lastPath, tr("Any Files (*)"));
  //QString qs = "fatrat " + m_link + " -O " + fileName;
  QProcess proc;
  QString qs = "fatrat " + m_link;
  proc.start(qs);
  //system (qs.toStdString().c_str());
  return;
}

void ScutView::loadUrl(const QString &url){
    if ( url.startsWith( "javascript://") ){
      runJS(url);
      return;
    }
    else if ( url.startsWith( SCUT_RSS_FEED) ){
      parseRSS(url);
      return;
    }
    else (loadUrl(QUrl(url)));
    return;
}

/* Custom version of setUrl() which will clear view, load the page, filter it,
 * then display it.
 */
void ScutView::loadUrl(const QUrl &u){
  // For now, fall back on just loading the url...
  QUrl url = u; 

    if ("about:" == url.toString()){
      QFile file;
      file.setFileName(":/resources/html/about.html");
      file.open(QIODevice::ReadOnly);
      QString about = file.readAll();
      file.close();

      page()->currentFrame()->setHtml(about);
      return;
    }

    else if ("bookmarks:" == url.toString()){
      QString bm = QDir::homePath () + "/" + SCUT_BOOKMARKS_FILE;
      QFile file;
      file.setFileName(bm);
      file.open(QIODevice::ReadOnly);
      QString about = file.readAll();
      file.close();

      page()->currentFrame()->setHtml(about);
      return;
    }

    else if (!url.toString().contains("://")){
	    url = QUrl("http://" + url.toString());
    } 
  setUrl(url);
}

void ScutView::runJS(const QString &url){
      QString js = url;
      js.remove(0, 13 );
      page()->mainFrame()->evaluateJavaScript(js);
      return;
}

/* Given a chrome url, parse it */
void ScutView::parseRSS(const QString &uri){
      QString url = uri;
      url = url.remove(0, QString(SCUT_RSS_FEED).size());
      url = uri2string(url);
      qDebug() << __PRETTY_FUNCTION__ << "FIXME: STUB: ADD CHROME SUPPORT"<< url;
}

/* FIXME: Need to parse rss here... */
void ScutView::replyFinished(QNetworkReply *reply){
      qDebug() << __PRETTY_FUNCTION__ << "FIXME: STUB: ADD RSS SUPPORT";
}

} // namespace scutum
// Tue Jan  1 17:59:18 PST 2013
