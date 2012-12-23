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

JsonDelicious::JsonDelicious() {
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

const QMap<QString, QUrl> JsonDelicious::titlelinks(){
	QMap<QString, QUrl> map;
	foreach (Json json, m_jsonlist){
		//map.append(json->title, json->url);
    map[json.title] = json.url;
  }
  return map;
}

int JsonDelicious::size(){
  m_jsonlist.size();
}

void JsonDelicious::setData(const QString &json) {
  m_jsonlist.clear();
  parse(json);
}

} // namespace scutum
// Sat Dec 22 16:12:57 PST 2012
