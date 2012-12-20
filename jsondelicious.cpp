/*
 * Scutum
 *
 * JsonDelicous:
 * 
 * Parses JSON Data For Delicious
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

#include "jsondelicious.hpp"
#include <QDebug>
#include <QStringList>

namespace scutum{

JsonDelicious::JsonDelicious(const QString &json) {
  parse(json);
}

JsonDelicious::~JsonDelicious() {}

QStringList JsonDelicious::list(const QString &json) {
  QStringList qlist = json.split("}");
  return qlist;
}

QString JsonDelicious::element(const QString &element, const QString &line) {
  QString res;
  QString f = "\""+element+"\": \"";
  QStringList qsl = line.split(f);

  if (qsl.size() < 2) return res;

  qsl = qsl[1].split("\"");

  res = qsl[0];
  qDebug() << res;

  // TODO: Get out the element here

  return res;
}

void JsonDelicious::parse(const QString &text) {
  QStringList qlist = list(text);
  foreach (QString line, qlist){
          Json json;
          json.title = element("d", line);
          json.url = QUrl(element("u", line));
          m_jsonlist.append(json);
  }
}

const QStringList JsonDelicious::titles(){
	QStringList qsl;
  foreach (Json json, m_jsonlist){
		qsl.append(json.title);
	}
	return qsl;
}

/* Given a title, return a Url */
const QUrl JsonDelicious::url(const QString &title){
  QUrl url;
  foreach (Json json, m_jsonlist){
    if ( json.title == title ) return json.url;
  }
  return url; 
}

} // namespace scutum
// Wed Dec 19 19:08:34 PST 2012
