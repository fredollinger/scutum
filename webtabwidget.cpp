/*
 * Scutum
 *
 * WebTabWidget:
 * 
 * A wrapper for QTabWidget, which manages web pages 
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
#include "webtab.hpp"
#include "webtabwidget.hpp"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGroupBox>
namespace scutum{
/**
 * Class constructor.
 * @param	pParent	The parent widget
 */
WebTabWidget::WebTabWidget(QWidget* pParent) 
	: QTabWidget(pParent)
  , m_parent(pParent)
{
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(closeTab(int)));
    setCache();
}

/**
 * Class destructor.
 */
WebTabWidget::~WebTabWidget(){} 

QString WebTabWidget::shortUrl(const QUrl& url){
	QString qs = url.toString();
	qs.remove(0,7);
	if (qs.count() > 10) qs.resize(10);
	return qs;
}

void WebTabWidget::loadTabView(QListWidgetItem *wid){
  qDebug() << __PRETTY_FUNCTION__;
  loadTabView(wid->data(Qt::UserRole).toUrl());
}

void WebTabWidget::loadTabView(QUrl url){
    newWebTab(tr("NEW"));
    WebTab *tab = qobject_cast<WebTab*>(widget(currentIndex()));
    tab->view()->load(url);

    connect(tab->view()->page() 
  , SIGNAL(linkHovered ( const QString&, const QString&, const QString&)) 
  , SLOT(linkHovered ( const QString&, const QString&, const QString &)) );
}

void WebTabWidget::loadTabView(QUrl url, const QString &title){
    newWebTab(title);
    WebTab *tab = qobject_cast<WebTab*>(widget(currentIndex()));
    tab->view()->load(url);
}

void WebTabWidget::loadTabView(const QString &qs, const QString &title){
    newWebTab(tr("NEW"));
    //WebTab *view = qobject_cast<WebTab*>(widget(currentIndex()));
    //view->load(url);
}

	/*
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
	*/

void WebTabWidget::newWebTab(const QString &title){
    int index;
    WebTab *tab = new WebTab(this);
    index = addTab(tab, title);
    setCurrentIndex(index);
    connect(tab, SIGNAL(titleChanged(WebTab*)), SLOT(adjustTitle(WebTab*)));
    connect(tab->view(), SIGNAL(sigOpenInNewTab(QUrl)), SLOT(loadTabView(QUrl)));
}

void WebTabWidget::adjustTitle(WebTab *tab){
    QString qs = tab->title();
	  if (qs.count() > 10) qs.resize(10);
    setTabText(indexOf(tab), qs);
}

void WebTabWidget::increaseFontSize(){
  WebTab *w = qobject_cast<WebTab*>(widget(currentIndex()));
  w->increaseFontSize();
}

void WebTabWidget::decreaseFontSize(){
  WebTab *w = qobject_cast<WebTab*>(widget(currentIndex()));
  w->decreaseFontSize();
}

void WebTabWidget::closeTab(int index){
  if (count() < 2){
    newWebTab(tr("NEW"));
  }

  WebTab *tab = qobject_cast<WebTab*>(widget(index));
  removeTab(index);
  delete tab;

}

/*
void WebTabWidget::showSearchBar(int type){
  WebTab *w = qobject_cast<WebTab*>(widget(currentIndex()));
  w->showSearchBar(type);
}
*/

void WebTabWidget::reload(){
  WebTab *w = qobject_cast<WebTab*>(widget(currentIndex()));
  w->reload();
}

void WebTabWidget::copyHighlightedText(){
    //WebTab *tab = qobject_cast<WebTab*>(widget(currentIndex()));
    tab()->view()->copyHighlightedText();
}

void WebTabWidget::findNext(){
  //WebTab *tab = qobject_cast<WebTab*>(widget(currentIndex()));
  tab()->searchPage();
  return;
}

void WebTabWidget::findPrevious(){
  //WebTab *tab = qobject_cast<WebTab*>(widget(currentIndex()));
  tab()->searchPageBackwards();
  return;
}

bool WebTabWidget::setCache(){

  QString cache = QDir::homePath () + SCUT_CACHE;
  QDir cacheDir = QDir(cache);
  if (!cacheDir.mkpath(cache)){
       qDebug() << __PRETTY_FUNCTION__ << "WARN: Failed to set cache: "<<cache;
       return false;
  }

  QWebSettings::setOfflineStoragePath(cache);
  // FIXME: We should test if this is actually set...
  return true;
}

bool WebTabWidget::ensureBookmarks(){
  QString bm = QDir::homePath () + "/" + SCUT_BOOKMARKS_FILE;
  QFile bmf; 
  bmf.setFileName(bm);
  if (bmf.exists()) return true;

  QFile file;
  file.setFileName(":/resources/html/scutum_bookmarks.html");
  file.open(QIODevice::ReadOnly);
  QString about = file.readAll();
  file.close();

  if (!bmf.open(QIODevice::WriteOnly)) return false;
  bmf.write(about.toAscii());
  bmf.close();
  return true;
}

void WebTabWidget::viewBookmarks(){
  if (!ensureBookmarks()) return;
  newWebTab("bookmarks:");
  WebTab *tab = qobject_cast<WebTab*>(widget(currentIndex()));
  tab->setLocation("bookmarks:");
  tab->changeLocation();
}

WebTab* WebTabWidget::tab(){
  return qobject_cast<WebTab*>(widget(currentIndex()));
}

bool WebTabWidget::newBookmark(){
//<LI><a href="http://ubuntuforums.org/showthread.php?t=1031764">[ubuntu] Brightness adjustment not work - Samsung X360 - Ubuntu Forums</a>
  if (!ensureBookmarks()) return false;
  QString bm = QDir::homePath () + "/" + SCUT_BOOKMARKS_FILE;
  QFile bmf; 
  bmf.setFileName(bm);

  QString mark = "<LI><a href=\"" + tab()->location() + "\">" + tab()->view()->title() + "</a>\n";

  if (!bmf.open(QIODevice::Append)) return false;
  bmf.write(mark.toAscii());
  bmf.close();
  return true;
}

void WebTabWidget::linkHovered ( const QString &one, const QString &two, const QString &three ){
  emit sigLinkHovered(one, two, three);
}

void WebTabWidget::closeTabs (){
  int c = count(); 
  closeTab(0);
  for(int i=c;  i > 0; i--){
      closeTab(i);
  }
}

} // namespace scutum
// Sun Dec 16 12:44:23 PST 2012
