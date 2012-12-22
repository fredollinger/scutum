#ifndef __DELICIOUS_BOOKMARK_HPP__
#define __DELICIOUS_BOOKMARK_HPP__

#include <QDialog>
#include "ui_deliciousbookmark.h"

namespace scutum{
class DeliciousBookmark : public QDialog, public Ui::DeliciousBookmark
{
	Q_OBJECT
public:
	DeliciousBookmark(QWidget* pParent = NULL, const char* szName = NULL);
	~DeliciousBookmark();

}; // class DeliciousBookmark
} // namespace scutum
#endif //__DELICIOUS_BOOKMARK_HPP__
