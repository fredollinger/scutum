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

#include "scutrss.hpp"
#include <QDebug>
#include <QStringList>

namespace scutum{

ScutRSS::ScutRSS() {
}

ScutRSS::~ScutRSS() {
}

bool ScutRSS::isRSS(const QString &text) {
  return text.contains("type=\"application/rss+xml\"");
}

void ScutRSS::parseXml()
 {

     while (!xml.atEnd()) {
         xml.readNext();
         if (xml.isStartElement()) {

             if (xml.name() == "item"){

                 if (titleString!=""){
                    feed = new QTreeWidgetItem;
                    feed->setText(0, titleString);
                    feed->setText(2, linkString);
                    //ui->treeWidget->addTopLevelItem(feed);

                 }

                 linkString.clear();
                 titleString.clear();
                 dateString.clear();
             }

             currentTag = xml.name().toString();
         } else if (xml.isEndElement()) {
              if (xml.name() == "item") {

                 QTreeWidgetItem *item = new QTreeWidgetItem(feed);
                 item->setText(0, titleString);
                 item->setText(1, dateString);
                 item->setText(2, linkString);
                 //ui->treeWidget->addTopLevelItem(item);

                 titleString.clear();
                 linkString.clear();
                 dateString.clear();
             }

         } else if (xml.isCharacters() && !xml.isWhitespace()) {
             if (currentTag == "title")
                 titleString += xml.text().toString();
             else if (currentTag == "link")
                 linkString += xml.text().toString();
             else if (currentTag == "pubDate")
                 dateString += xml.text().toString();
         }
     }
     if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
         qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
         http.abort();
     }
 }

} // namespace scutum
// Sun Mar 31 14:00:21 PDT 2013
