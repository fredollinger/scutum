/*
 * Scutum
 *
 * ScutRSS:
 * 
 * Parses RSS Data
 *
 * Copyright (C) 2013 Fred Ollinger
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

#ifndef __SCUT_RSS__
#define __SCUT_RSS__

#include <QDateTime>
#include <QHttp>
#include <QList>
#include <QString>
#include <QUrl>
#include <QXmlStreamReader>
#include <QTreeWidgetItem>

namespace scutum{
class ScutRSS {
public:
  ScutRSS(void);
  ~ScutRSS(void);
  static bool isRSS(const QString&);
  static void parseXml(const QString&);

protected:
    //QHttp http;
};
} // namespace scutum
#endif // __SCUT_RSS__
// Sun May 26 18:42:02 PDT 2013
