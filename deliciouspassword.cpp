/*
 * Scutum
 *
 * DeliciousPassword:
 * 
 * Dialog to get a username and password for delicious
 *
 * Copyright (C) 2012 Fred Ollinger
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
// BEGIN QT INCLUDES
#include <qdebug.h>
#include <QDialog>
// END QT INCLUDES

#include "deliciouspassword.hpp"

namespace scutum{
DeliciousPassword::DeliciousPassword(QWidget* pParent, const char* szName) 
{
	setupUi(this);

  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

DeliciousPassword::~DeliciousPassword()
{
}
} // namespace scutum
