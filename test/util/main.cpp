#include "../../scututil.hpp"
#include <QDebug>
#include <QFile>

using namespace scutum;

int main(){

  QString qs="http%3A%2F%2Fentzulearen.tumblr.com%2Frss";
  qDebug() <<  scutum::uri2string(qs);
  return 0;
}
