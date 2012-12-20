
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

public:
  SidePane(QWidget *pParent);
  void getBookmarks();
  void addItems(JsonDelicious*);

private:
  QNetworkAccessManager *m_net;
  JsonDelicious *m_latest;

public slots:
  void replyFinished(QNetworkReply*);

};
} // namespace scutum
#endif
