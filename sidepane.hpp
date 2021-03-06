
/*
 * Scutum
 *
 * SidePane:
 * 
 * Side Panel
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


#ifndef __SIDE_PANE__
#define __SIDE_PANE__

#include <QWidget>
#include "ui_sidepane.h"

class QNetworkReply;
class QNetworkAccessManager;

namespace scutum{

class JsonDelicious;

class SidePane : public QWidget, public Ui::SidePane
{
    Q_OBJECT

enum SCUTUM_DELICIOUS_MODE{
SCUTUM_DELICIOUS_MODE_RECENT,
SCUTUM_DELICIOUS_MODE_RSS,
SCUTUM_DELICIOUS_MODE_NEW_BOOKMARK,
};

public:
  SidePane(QWidget *pParent);
  void addItems(JsonDelicious*);

private:
  QNetworkAccessManager *m_net;
  JsonDelicious *m_links; 
  JsonDelicious *m_latest;
  JsonDelicious *m_rss;
  int m_query_mode;
  bool m_refresh;

public slots:
  void getBookmarks(void);
  void getRSS(void);
  void refresh(void);
  void replyFinished(QNetworkReply*);
  void newBookmark(const QString&, const QString&, const QString&);
};
} // namespace scutum
#endif
