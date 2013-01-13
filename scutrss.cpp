/*
 * Scutum
 *
 * ScutRSS:
 * 
 * Parses RSS Data 
 *
 * Copyright (C) 2013 Fred Ollinger
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

#include "scutrss.hpp"
#include <QDebug>
#include <QStringList>

namespace scutum{

ScutRSS::ScutRSS() {
}

ScutRSS::~ScutRSS() {
}

static bool ScutRSS::isRSS(const QString &text) {
  return true;
}

} // namespace scutum
// Sat Jan 12 16:46:40 PST 2013
