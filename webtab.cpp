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

#include "scutcommon.hpp"
#include "webtab.hpp"
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QVBoxLayout>
#include <QWebFrame>
namespace scutum{
/**
 * Class constructor.
 * @param	pParent	The parent widget
 */
WebTab::WebTab(QWidget* pParent) 
	: QGroupBox(pParent)
{
  m_tool = new QToolBar();
  m_view = new ScutView();
  connect(m_view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
  QVBoxLayout *layout = new QVBoxLayout();

  m_locationEdit = new QLineEdit(this);
  m_locationEdit->setSizePolicy(QSizePolicy::Expanding, m_locationEdit->sizePolicy().verticalPolicy());
  connect(m_locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

  m_tool->addAction(m_view->pageAction(QWebPage::Back));
  m_tool->addAction(m_view->pageAction(QWebPage::Forward));
  m_tool->addAction(m_view->pageAction(QWebPage::Reload));
  m_tool->addAction(m_view->pageAction(QWebPage::Stop));
  m_tool->addWidget(m_locationEdit);

  m_find = new QToolBar();
  m_findEdit = new QLineEdit(this);
  m_findEdit->setSizePolicy(QSizePolicy::Expanding, m_findEdit->sizePolicy().verticalPolicy());

  m_find->addWidget(m_findEdit);
  QIcon closeIcon = QIcon::fromTheme("window-close");
  QAction *closeAct = new QAction(closeIcon, "", this);
  m_find->addAction(closeAct);
  connect(m_findEdit, SIGNAL(returnPressed()), SLOT(searchPage()));

  connect(m_view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
  connect(closeAct, SIGNAL(triggered()), SLOT(hideSearchBar()));
  m_find->hide();

  setLayout(layout);

  layout->addWidget(m_tool);
  layout->addWidget(m_view);
  layout->addWidget(m_find);
}

/**
 * Class destructor.
 */
WebTab::~WebTab(){} 

void WebTab::setLocation(const QString &location) {
  m_locationEdit->setText(location);
}

void WebTab::changeLocation() {
    QUrl url = QUrl(m_locationEdit->text());

   // m_view->setUrl(url);
    m_view->loadUrl(url);
    m_view->setFocus();
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

void WebTab::adjustLocation() {
    m_locationEdit->setText(m_view->url().toString());
}

void WebTab::searchPage() {
    m_view->page()->findText(m_findEdit->text(), QWebPage::HighlightAllOccurrences);
    m_view->page()->findText(m_findEdit->text(), QWebPage::FindWrapsAroundDocument);
    m_find->hide();
    m_view->setFocus();
}

void WebTab::showSearchBar() {
  m_find->show();
  m_findEdit->setFocus();
}

void WebTab::hideSearchBar() {
  m_find->hide();
}

void WebTab::reload() {
  m_view->reload();
}

ScutView* WebTab::view() {
  return m_view;
}

void WebTab::searchPageBackwards() {
    m_view->page()->findText(m_findEdit->text(), QWebPage::HighlightAllOccurrences);
    m_view->page()->findText(m_findEdit->text(), QWebPage::QWebPage::FindBackward);
    m_find->hide();
    m_view->setFocus();
}

} // namespace scutum
// Fri Nov 23 14:52:19 PST 2012
