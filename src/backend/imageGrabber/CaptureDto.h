/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_CAPTUREDTO_H
#define KSNIP_CAPTUREDTO_H

#include "CursorDto.h"

struct CaptureDto
{
	QPixmap screenshot;
	CursorDto cursor;

	CaptureDto(const QPixmap &screenshot) {
		this->screenshot = screenshot.copy();
	}

	bool isValid() const {
		return !screenshot.isNull();
	}

	bool isCursorValid() const {
		return cursor.isValid();
	}
};

#endif //KSNIP_CAPTUREDTO_H
