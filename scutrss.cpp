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

QString ScutRSS::parseXml(const QString &data){
     QString titleString;
     QString currentTag;
     QString dateString;
     QString linkString;
     QString description;
     QString html = "<html><h1>RSS Reader!!</h1>";

     QXmlStreamReader xml;
     xml.addData(data);

     while (!xml.atEnd()) {
         xml.readNext();
         if (xml.isStartElement()) {

             if (xml.name() == "item"){

                 if (titleString!=""){
                    //feed = new QTreeWidgetItem;
                    //feed->setText(0, titleString);
                    //feed->setText(2, linkString);
                    //ui->treeWidget->addTopLevelItem(feed);

                    //qDebug() << __PRETTY_FUNCTION__<< " title: " << titleString << " linkString: " << linkString;
                 }

                 description.clear();
                 linkString.clear();
                 titleString.clear();
                 dateString.clear();
             }

             currentTag = xml.name().toString();
             //qDebug() << __PRETTY_FUNCTION__<< " current tag: " << currentTag;
         } else if (xml.isEndElement()) {
              if (xml.name() == "item") {

               //qDebug() << __PRETTY_FUNCTION__<< " title: " << titleString << " linkString: " << linkString;
               html = html + "<p><h2><a href=\"" + linkString +"\">" + titleString + "</a></h2></p>";

               html = html + "<p><h3>" + description + "<h3></p>";

                 //QTreeWidgetItem *item = new QTreeWidgetItem(feed);
                 //item->setText(0, titleString);
                 //item->setText(1, dateString);
                 //item->setText(2, linkString);
                 //ui->treeWidget->addTopLevelItem(item);

                 titleString.clear();
                 linkString.clear();
                 dateString.clear();
             }

         } else if (xml.isCharacters() && !xml.isWhitespace()) {
            if (currentTag == "channel"){
                 qDebug() << __PRETTY_FUNCTION__<< " channel: " << currentTag;
                 //titleString += xml.text().toString();
             }
            if (currentTag == "description"){
                 qDebug() << __PRETTY_FUNCTION__<< " description: " << xml.text();
                 description += xml.text().toString();
             }
             else if (currentTag == "title"){
                 //qDebug() << __PRETTY_FUNCTION__<< " current tag: " << currentTag;
                 titleString += xml.text().toString();
             }
             else if (currentTag == "link"){
                 linkString += xml.text().toString();
                 //qDebug() << __PRETTY_FUNCTION__<< " current link: " << currentTag;
             }
             else if (currentTag == "pubDate"){
                 dateString += xml.text().toString();
                 //qDebug() << __PRETTY_FUNCTION__<< " current date: " << currentTag;
             }
         }
     }
     if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
         qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
         //http.abort();
     }

 html = html + "</html>";
 return html;
 } // QString ScutRSS::parseXml(const QString &data);

} // namespace scutum
// Sun Mar 31 14:00:21 PDT 2013
