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

#include "scutview.hpp"
#include <QAction>
#include <QDebug>
#include <QWebView>

namespace scutum{
ScutView::ScutView(QWidget* pParent) 
	: QWebView(pParent) 
  , m_isLinkHovered(false)
{
  connect(page() 
  , SIGNAL(linkHovered ( const QString&, const QString&, const QString&)) 
  , SLOT(linkHovered ( const QString&, const QString&, const QString &)) );



}

ScutView::~ScutView(){}

void ScutView::showLinkMenu (){
    QPoint pos = QCursor::pos();
    QPoint globalPos = mapToGlobal(pos);

    QMenu *linkMenu = page()->createStandardContextMenu();
    QAction* openInNewTabAct = new QAction(tr("Open In New Tab"), this);
    connect(openInNewTabAct, SIGNAL(triggered()), SLOT(openInNewTab()));
    linkMenu->addAction(openInNewTabAct);
    linkMenu->exec(pos);
}

void ScutView::openInNewTab(){
	qDebug() << __PRETTY_FUNCTION__ << m_link;
  emit sigOpenInNewTab(QUrl(m_link));
}

void ScutView::contextMenuEvent ( QContextMenuEvent * ev ){
  if (m_isLinkHovered){
	  qDebug() << __PRETTY_FUNCTION__ << m_link;
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
	qDebug() << __PRETTY_FUNCTION__ << m_link;
  return;
}

} // namespace scutum
// Sat Dec  1 11:46:27 PST 2012
