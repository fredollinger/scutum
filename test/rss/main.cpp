#include "../../scutrss.hpp"
#include <QDebug>
#include <QFile>

using namespace scutum;

int main(){
  QFile file("feed.rss");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return -1;
  
  QString text = QString(file.readAll());

  if ( ScutRSS::isRSS(text) ) {
    qDebug() << " feed.rss is rss ";
  }
  else
    qDebug() << " feed.rss is NOT rss ";

  return 0;
}
