#include "../../scututil.hpp"
#include <QDebug>
#include <QFile>

using namespace scutum;

int main(){

  QString qs="chrome://bob.joe";
  qDebug() <<  scutum::authority(qs);
  qs="me";
  qDebug() <<  scutum::authority(qs);
  return 0;
}
