// BEGIN QT INCLUDES
#include <qdebug.h>
#include <QDialog>
// END QT INCLUDES

#include "delicious.hpp"

namespace scutum{
Delicious::Delicious(QWidget* pParent, const char* szName) 
{
	setupUi(this);
}

Delicious::~Delicious()
{
}
} // namespace scutum
