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


#ifndef __WEB_TAB__
#define __WEB_TAB__

#include <QHBoxLayout>
#include <QTabWidget>
#include <QToolBar>
#include <QWebView>

namespace scutum{
class WebTab: public QHBoxLayout{
Q_OBJECT
public:
    WebTab(QWidget* pParent = 0);
    ~WebTab();
    void loadUrl(QUrl url);
private:
	QToolBar *m_tool;
	QWebView *m_view;
};

} // namespace scutum
#endif // __WEB_TAB__
// Sun Oct  9 16:49:32 PDT 2011
