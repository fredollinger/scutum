/*
 * Scutum
 *
 * ScutUtil:
 * 
 * A collection of useful functions
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


#include "scututil.hpp"

#include <QDebug>
#include <QStringList>

/* http://doc.qt.digia.com/qt/qurl.html */

namespace scutum{

/* authority: returns the part of the url which is NOT the scheme.
 * given:
 *
 * chrome://sage/feeds/url=myrssfeed
 *
 * this returns:
 * 
 * sage/feeds/url=myrssfeed
 */
QString authority(const QString &qs){
        // Find the "://"
        QStringList qsl = qs.split("://");
        if (qsl.size() < 2) return qs;
        return qsl[1];
}

/*  uri2string(): 
 * get rid of the junk like slashes from the uri
 */
QString uri2string(const QString &uri){
  QString st = uri;
  st = st.replace("%2F", "/");
  st = st.replace("%2f", "/");
  st = st.replace("%3A", ":");
  st = st.replace("%3a", ":");

  return st; 
}

}//namespace scutum
