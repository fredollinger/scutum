/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtGui>
#include <QSplitter>
#include <QStatusBar>
#include <QtWebKit>
#include "mainwindow.h"
#include "scutcommon.hpp"
#include "sidepane.hpp"
#include "webtab.hpp"

#ifdef QT5
#include <QMenu>
#include <QMenuBar>
#include <QNetworkProxyFactory>
#include <QNetworkReply>
#include <QTextEdit>
#endif

//! [1]

namespace scutum{
MainWindow::MainWindow(const QUrl& url)
{
    progress = 0;

    //setWindowIcon ( QIcon(":/scutum.png"));
    setWindowIcon ( QIcon(" :/resources/images/scutum.png"));

    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    file.close();

    QNetworkProxyFactory::setUseSystemConfiguration(true);

    m_tabwidget = new WebTabWidget(this);
    m_tabwidget->setTabsClosable(true);
    m_tabwidget->loadTabView(url);
    connect(m_tabwidget, 
    SIGNAL(sigLinkHovered( const QString&, const QString&, const QString& )),
    SLOT(linkHovered( const QString&, const QString&, const QString& )));

    // BEGIN VIEW MENU
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    QAction* viewNewTab = new QAction(tr("New Tab"), this);
    connect(viewNewTab, SIGNAL(triggered()), SLOT(newTab()));
    viewMenu->addAction(viewNewTab);

    QAction* textBig = new QAction(tr("Text Bigger (+)"), this);
    connect(textBig, SIGNAL(triggered()), m_tabwidget, SLOT(increaseFontSize()));
    viewMenu->addAction(textBig);

    QAction* textSmall = new QAction(tr("Text Smaller (-)"), this);
    connect(textSmall, SIGNAL(triggered()), m_tabwidget, SLOT(decreaseFontSize()));
    viewMenu->addAction(textSmall);

    QAction* aboutTab = new QAction(tr("About"), this);
    connect(aboutTab, SIGNAL(triggered()), SLOT(aboutTab()));
    viewMenu->addAction(aboutTab);

    QAction* quitTab = new QAction(tr("&Quit"), this);
    connect(quitTab, SIGNAL(triggered()), SLOT(quit()));
    viewMenu->addAction(quitTab);
    // END VIEW MENU

    // BEGIN BOOKMARKS MENU
    QMenu *bookmarksMenu = menuBar()->addMenu(tr("&Bookmarks"));

    QAction* newBookmark = new QAction(tr("New Bookmark"), this);
    connect(newBookmark, SIGNAL(triggered()), m_tabwidget, SLOT(newBookmark()));
    bookmarksMenu->addAction(newBookmark);

    QAction* viewBookmarks = new QAction(tr("View Bookmark"), this);
    connect(viewBookmarks, SIGNAL(triggered()), m_tabwidget, SLOT(viewBookmarks()));
    bookmarksMenu->addAction(viewBookmarks);
    // END BOOKMARKS MENU

    m_sidepane = new SidePane(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(m_sidepane);
    splitter->addWidget(m_tabwidget);
    setCentralWidget(splitter);
   // setCentralWidget(m_tabwidget);
    setUnifiedTitleAndToolBarOnMac(true);
    showMaximized();
    m_sidepane->hide();
}

void MainWindow::slotSourceDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
    QTextEdit* textEdit = new QTextEdit(NULL);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->show();
    textEdit->setPlainText(reply->readAll());
    reply->deleteLater();
}

void MainWindow::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    if (!url.toString().contains("://")){
	url = QUrl("http://" + url.toString());
    } 

    QWebView *l_view;
    l_view = qobject_cast<QWebView*>(m_tabwidget->currentWidget());
    l_view->setUrl(url);
    l_view->setFocus();
    m_tabwidget->setTabText(m_tabwidget->currentIndex(), shortUrl(url));
}
//! [4]

//! [5]
void MainWindow::adjustTitle()
{
#if 0
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
#endif
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}
//! [5]

//! [6]
void MainWindow::finishLoading(bool)
{
    progress = 100;
    adjustTitle();
    //view->page()->mainFrame()->evaluateJavaScript(jQuery);

    //rotateImages(rotateAction->isChecked());
}
//! [6]

//! [7]
void MainWindow::highlightAllLinks()
{
    QString code = "$('a').each( function () { $(this).css('background-color', 'yellow') } )";
    //view->page()->mainFrame()->evaluateJavaScript(code);
}
//! [7]

//! [8]
void MainWindow::rotateImages(bool invert)
{
    QString code;
    if (invert)
        code = "$('img').each( function () { $(this).css('-webkit-transition', '-webkit-transform 2s'); $(this).css('-webkit-transform', 'rotate(180deg)') } )";
    else
        code = "$('img').each( function () { $(this).css('-webkit-transition', '-webkit-transform 2s'); $(this).css('-webkit-transform', 'rotate(0deg)') } )";
    //view->page()->mainFrame()->evaluateJavaScript(code);
}
//! [8]

//! [9]
void MainWindow::removeGifImages()
{
    QString code = "$('[src*=gif]').remove()";
    //view->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::removeInlineFrames()
{
    QString code = "$('iframe').remove()";
    //view->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::removeObjectElements()
{
    QString code = "$('object').remove()";
    //view->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::removeEmbeddedElements()
{
    QString code = "$('embed').remove()";
    //view->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::newTab(){
    m_tabwidget->newWebTab(tr("New"));
}

void MainWindow::aboutTab(){
    WebTab *tab = new WebTab(this);
    m_tabwidget->addTab(tab, "about:");
    tab->setLocation("about:");
    tab->changeLocation();
}

QString MainWindow::shortUrl(const QUrl& url){
	QString qs = url.toString();
	qs.remove(0,7);
	if (qs.count() > 10) qs.resize(10);
	return qs;
}

void MainWindow::loadTabView(QUrl url){
    WebTabWidget *view = new WebTabWidget(this);
    m_tabwidget->addTab(view, "");
    m_tabwidget->setTabText(m_tabwidget->currentIndex(), shortUrl(url));

//    view->load(url);
/*
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
*/
}

void MainWindow::quit(){
  qApp->quit(); 
}

void MainWindow::toggleSidePane(){
  if (m_sidepane->isVisible()) m_sidepane->hide();
  else m_sidepane->show();
}

bool MainWindow::event(QEvent *event){
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *ke = static_cast<QKeyEvent *>(event);
    if (ke->key() == Qt::Key_Plus) {
      m_tabwidget->increaseFontSize();
      // return true to end handling of event, false to pass it on
      return QWidget::event(event);
      // return true;
    }

    else if (ke->key() == Qt::Key_Minus) {
      m_tabwidget->decreaseFontSize();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_B && ke->modifiers() == Qt::ControlModifier ) {
      m_tabwidget->viewBookmarks();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_C && ke->modifiers() == Qt::ControlModifier ) {
      m_tabwidget->copyHighlightedText();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_F && ke->modifiers() == Qt::ControlModifier ||  
             ke->key() == Qt::Key_Slash) {
      m_tabwidget->tab()->showSearchBar(SCUT_SEARCH_PAGE);
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_N || ke->key() == Qt::Key_Asterisk ) {
      m_tabwidget->findNext();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_P ||  ke->key() == Qt::Key_NumberSign) {
      m_tabwidget->findPrevious();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_Q && ke->modifiers() == Qt::ControlModifier ) {
      quit();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_R && ke->modifiers() == Qt::ControlModifier ) {
      m_tabwidget->reload();
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_S && ke->modifiers() == Qt::ControlModifier ){
      m_tabwidget->tab()->showSearchBar(SCUT_SEARCH_ONLINE);
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_T && ke->modifiers() == Qt::ControlModifier ) {
      m_tabwidget->newWebTab(tr("NEW"));
      return QWidget::event(event);
    }
    else if (ke->key() == Qt::Key_Z && ke->modifiers() == Qt::AltModifier ) {
      toggleSidePane();
      return QWidget::event(event);
    }
  }
  return QWidget::event(event);
}

void MainWindow::linkHovered ( const QString &one, const QString &two, const QString &three ){
  statusBar()->showMessage(one); 
}

} // namespace scutum
