#include "../scutrss.hpp"
#include <QDebug>
#include <QFile>

using namespace scutum;

int main(){
  QFile file("test.json");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return -1;
  
  QString text = QString(file.readAll());
//  qDebug() << text;

  JsonDelicious *json = new JsonDelicious(text);
  return 0;
}
