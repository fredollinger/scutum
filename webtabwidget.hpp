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
public:
    WebTabWidget(QWidget* pParent = 0);
    ~WebTabWidget();
    void increaseFontSize(void);
    void decreaseFontSize(void);
    void loadTabView(QUrl url);
    QString shortUrl(const QUrl& url);
    void newWebTab(void);
public slots:
    void adjustTitle(WebTab*);
};

} // namespace scutum
#endif // __WEB_TAB_WIDGET__
// Sun Oct  9 16:49:32 PDT 2011
