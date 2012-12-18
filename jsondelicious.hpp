/*
 * Scutum
 *
 * JsonDelicious:
 * 
 * Parses delicious json files
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

#ifndef __JSON_DELICIOUS__
#define __JSON_DELICIOUS__

#include <QString>

namespace scutum{
class JsonDelicious {
public:
  JsonDelicious(const QString&);
  ~JsonDelicious();
};

} // namespace scutum
#endif // __JSON_DELICIOUS__
// Mon Dec 17 18:13:13 PST 2012
