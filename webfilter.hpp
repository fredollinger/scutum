/*
 * Scutum
 *
 * WebFilter:
 * 
 * Loads and filters web content
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

#ifndef __WEB_FILTER__
#define __WEB_FILTER__

#include <QNetworkAccessManager>
#include <QWidget>
#include <QUrl>

namespace scutum{
class WebFilter : QWidget{
public:

  Q_OBJECT
  WebFilter(QWidget* pParent = 0);
  ~WebFilter();
  void load(const QUrl&);

signals:
  void finished(QString&);

private:
  QNetworkAccessManager *manager;
};

} // namespace scutum
#endif // __WEB_FILTER__
// Sun Nov 25 12:07:13 PST 2012
