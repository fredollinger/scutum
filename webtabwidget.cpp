/*
 * Scutum
 *
 * WebTabWidget:
 * 
 * A wrapper for QTabWidget, which manages web pages 
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

#include "webtabwidget.hpp"

namespace scutum{
/**
 * Class constructor.
 * @param	pParent	The parent widget
 */
WebTabWidget::WebTabWidget(QWidget* pParent) 
	: QTabWidget(pParent)
{
}

/**
 * Class destructor.
 */
WebTabWidget::~WebTabWidget(){} 

} // namespace scutum

// Fri Nov 23 14:52:19 PST 2012
