#ifndef __DELICIOUS_PASSWORD_HPP__
#define __DELICIOUS_PASSWORD_HPP__

#include <QDialog>
#include "ui_deliciouspassword.h"

namespace scutum{
class DeliciousPassword : public QDialog, public Ui::DeliciousPassword
{
	Q_OBJECT
public:
	DeliciousPassword(QWidget* pParent = NULL, const char* szName = NULL);
	~DeliciousPassword();

}; // class DeliciousPassword
} // namespace scutum
#endif // __DELICIOUS_PASSWORD_HPP__
