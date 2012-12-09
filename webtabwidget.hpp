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


#ifndef __WEB_TAB_WIDGET__
#define __WEB_TAB_WIDGET__

#include <QTabWidget>
#include <QWebView>

namespace scutum{
class WebTab;
class WebTabWidget : public QTabWidget {
Q_OBJECT
// BEGIN WEBTAB PUBLIC
public:
    WebTabWidget(QWidget* pParent = 0);
    ~WebTabWidget();
    void findNext(void);
    void findPrevious(void);
    void reload(void);
    bool ensureBookmarks(void);

    QString shortUrl(const QUrl& url);
    WebTab* tab(void);
// END WEBTAB PUBLIC

public slots:
    void decreaseFontSize(void);
    void adjustTitle(WebTab*);
    void copyHighlightedText(void);
    void closeTab(int);
    void increaseFontSize(void);
    void loadTabView(QUrl url);
    void loadTabView(QUrl url, const QString &title);
    void loadTabView(const QString&, const QString&);
    bool newBookmark(void);
    void newWebTab(const QString&);
    void viewBookmarks(void);
};

} // namespace scutum
#endif // __WEB_TAB_WIDGET__
// Fri Dec  7 10:21:08 PST 2012
