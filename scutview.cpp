/*
 * Scutum
 *
 * ScutView:
 * 
 * Over rides QWebView
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

#include "scutview.hpp"
#include <QAction>
#include <QDebug>
#include <QWebView>

namespace scutum{
ScutView::ScutView(QWidget* pParent) 
	: QWebView(pParent)
{}

ScutView::~ScutView(){}

void ScutView::contextMenuEvent ( QContextMenuEvent * ev ){
	qDebug() << __PRETTY_FUNCTION__;
	return;
}

} // namespace scutum

