/*
 * Scutum
 *
 * WebTab:
 * 
 * A composite for which combines a toolbar and a web view
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
#include <QVBoxLayout>
#include <QDebug>
namespace scutum{
/**
 * Class constructor.
 * @param	pParent	The parent widget
 */
WebTab::WebTab(QWidget* pParent) 
	: QGroupBox(pParent)
{
  m_tool = new QToolBar();
  m_view = new QWebView();
  connect(m_view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
  QVBoxLayout *layout = new QVBoxLayout();

  m_tool->addAction(m_view->pageAction(QWebPage::Back));
  m_tool->addAction(m_view->pageAction(QWebPage::Forward));
  m_tool->addAction(m_view->pageAction(QWebPage::Reload));
  m_tool->addAction(m_view->pageAction(QWebPage::Stop));

  m_locationEdit = new QLineEdit(this);
  m_locationEdit->setSizePolicy(QSizePolicy::Expanding, m_locationEdit->sizePolicy().verticalPolicy());
  connect(m_locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));
  m_tool->addWidget(m_locationEdit);

  setLayout(layout);

  layout->addWidget(m_tool);
  layout->addWidget(m_view);
}

/**
 * Class destructor.
 */
WebTab::~WebTab(){} 

void WebTab::load(QUrl url){
    m_view->load(url);
}

void WebTab::changeLocation() {
    QUrl url = QUrl(m_locationEdit->text());
    if (!url.toString().contains("://")){
	    url = QUrl("http://" + url.toString());
    } 

    m_view->setUrl(url);
    m_view->setFocus();
    //m_tabwidget->setTabText(m_tabwidget->currentIndex(), shortUrl(url));
}

void WebTab::adjustTitle() {
          emit titleChanged(this);
}

QString WebTab::title(void) {
  return m_view->title();
}

void WebTab::increaseFontSize(void) {
        m_view->setZoomFactor(m_view->zoomFactor()+.1);
}

void WebTab::decreaseFontSize(void) {
        m_view->setZoomFactor(m_view->zoomFactor()-.1);
}

} // namespace scutum
// Fri Nov 23 14:52:19 PST 2012
