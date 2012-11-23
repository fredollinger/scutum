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

#include "webtabwidget.hpp"
#include <QDebug>
namespace scutum{
/**
 * Class constructor.
 * @param	pParent	The parent widget
 */
WebTabWidget::WebTabWidget(QWidget* pParent) 
	: QTabWidget(pParent)
{
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
    QWebView *view = new QWebView(this);
    addTab(view, "");
    setTabText(currentIndex(), shortUrl(url));
    view->load(url);
	/*
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
	*/
}
//! [9]

void WebTabWidget::newWebTab(){
    int index;
    QWebView *view = new QWebView(this);
    index = addTab(view, tr("NEW"));
    qDebug() << "Setting index to: " << index;
    setCurrentIndex(index);
}

} // namespace scutum
// Fri Nov 23 14:52:19 PST 2012
