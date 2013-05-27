#include "../../scutrss.hpp"
#include <QDebug>
#include <QFile>

using namespace scutum;

void testIsRss(const QString &fn){
  QFile file(fn);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
  QString text = QString(file.readAll());
  if ( ScutRSS::isRSS(text) ) {
    QString qs = ScutRSS::parseXml(text);
    qDebug() << fn << " is rss " << qs;
  }
  else
    qDebug() << fn << " is NOT rss ";

  return;
}

int main(){
  
  testIsRss("feed.xml");
  //testIsRss("feed.rss");
  //testIsRss("index.html");

  return 0;
}
