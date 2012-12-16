#ifndef _DELICIOUS_H
#define _DELICIOUS_H

#include <QDialog>
#include "ui_delicious.h"

namespace scutum{
class Delicious : public QDialog, public Ui::Delicious
{
	Q_OBJECT
public:
	Delicious(QWidget* pParent = NULL, const char* szName = NULL);
	~Delicious();

}; // class Delicious
} // namespace scutum
#endif // _DELICIOUS_H
