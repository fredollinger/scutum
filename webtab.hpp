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

#include <QGroupBox>
#include <QLineEdit>
#include <QToolBar>

#include "scutview.hpp"

namespace scutum{
//class WebTab: public QGridLayout{
//class WebTab: public QWidget{
class WebTab: public QGroupBox{
Q_OBJECT
public:
  WebTab(QWidget* pParent = 0);
  ~WebTab();
  QString title(void);
	QToolBar *m_find;
	QToolBar *m_tool;
	ScutView *m_view;
	QLineEdit *m_findEdit;
	QLineEdit *m_locationEdit;
  void decreaseFontSize(void);
  void increaseFontSize(void);
  void load(QUrl url);
  void reload(void);
	ScutView* view(void);
public slots:
  void adjustLocation(void);
  void adjustTitle(void);
  void changeLocation(void);
  void hideSearchBar(void);
  void searchPage(void);
  void showSearchBar(void);
signals:
  void titleChanged(WebTab*);

};

} // namespace scutum
#endif // __WEB_TAB__
// Sun Nov 25 12:07:13 PST 2012
