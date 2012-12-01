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

#include "webtab.hpp"
#include "webtabwidget.hpp"
#include <QDebug>
#include <QGroupBox>
namespace scutum{
/**
 * Class constructor.
 * @param	pParent	The parent widget
 */
WebTabWidget::WebTabWidget(QWidget* pParent) 
	: QTabWidget(pParent)
{
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(closeTab(int)));
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

void WebTabWidget::loadTabView(QUrl url){
    qDebug() << __PRETTY_FUNCTION__ << url.toString();
    newWebTab(tr("NEW"));
    WebTab *view = qobject_cast<WebTab*>(widget(currentIndex()));
    view->load(url);
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
    qDebug() << "Setting index to: " << index;
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

void WebTabWidget::showSearchBar(){
  WebTab *w = qobject_cast<WebTab*>(widget(currentIndex()));
  w->showSearchBar();
}

void WebTabWidget::reload(){
  WebTab *w = qobject_cast<WebTab*>(widget(currentIndex()));
  w->reload();
}

} // namespace scutum
// Fri Nov 23 14:52:19 PST 2012
