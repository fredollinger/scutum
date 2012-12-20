/*
 * Scutum
 *
 * JsonDelicious:
 * 
 * Parses delicious json files
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

#ifndef __JSON_DELICIOUS__
#define __JSON_DELICIOUS__

#include <QDateTime>
#include <QList>
#include <QString>
#include <QUrl>

namespace scutum{
class JsonDelicious {
public:
  JsonDelicious(const QString&);
  ~JsonDelicious();

  /* From a line, get an element */
  QString element(const QString &element, const QString &line);

  /* Given a QString, put this into a JsonList Struct */
  void parse(const QString&);

  /* Given a QString, break into a QString List */
  QStringList list(const QString&);

  const QUrl url(const QString &title);

	const QStringList titles(void);
private:
  struct Json{
    QString title;
    QString tag;
    QUrl url;
    QDateTime dt;
  };
  typedef QList<Json> JsonList;
  JsonList m_jsonlist;
};

} // namespace scutum
#endif // __JSON_DELICIOUS__
// Mon Dec 17 18:13:13 PST 2012
