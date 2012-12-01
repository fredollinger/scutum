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


#ifndef __SCUT_VIEW__
#define __SCUT_VIEW__

#include <QMenu>
#include <QWebView>

namespace scutum{
class ScutView: public QWebView{
Q_OBJECT
public:
  ScutView(QWidget* pParent = 0);
  ~ScutView();
  void showLinkMenu(void);
protected:
  bool m_isLinkHovered;

  QString m_link; 
  QString m_title; 
  QString m_textContent;


	void contextMenuEvent ( QContextMenuEvent * ev );
public slots:
  void linkHovered ( const QString & link, const QString & title, const QString & textContent );
  void openInNewTab(void);

signals:
  void sigOpenInNewTab(QUrl);

};
} // namespace scutum
#endif //  __SCUT_VIEW__
