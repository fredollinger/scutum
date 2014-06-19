/*
 * Scutum
 * 
 * ScutString:
 * 
 * Over rides QString especially for the stupid api breaking qt5
 *
 * Copyright (C) 2012-2014 Frederick Ollinger
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

#include <QtGlobal>
#include <QString>

#ifndef __SCUT_STRING__
#define __SCUT_STRING__

namespace scutum{
class ScutString: public QString{

public:
ScutString(QByteArray qb){
	this->insert(0, qb.constData());
}

ScutString(QString qb){
	this->insert(0, qb);
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#if 0
QByteArray toAscii (const QString &qs){
	return qs.toLatin1();	
}
#endif
QByteArray toAscii (void){
	return this->toLatin1();	
}
#else
// Do nothing for now
#endif

}; // END class ScutString
} // END namespace scutum

#endif //  __SCUT_STRING__
