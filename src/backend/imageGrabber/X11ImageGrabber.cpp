/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "X11ImageGrabber.h"

X11ImageGrabber::X11ImageGrabber() : AbstractImageGrabber(new LinuxSnippingArea), mX11Wrapper(new X11Wrapper)
{
	addSupportedCaptureMode(CaptureModes::RectArea);
	addSupportedCaptureMode(CaptureModes::FullScreen);
	addSupportedCaptureMode(CaptureModes::CurrentScreen);
	addSupportedCaptureMode(CaptureModes::ActiveWindow);
}

X11ImageGrabber::~X11ImageGrabber()
{
    delete mX11Wrapper;
}

bool X11ImageGrabber::isSnippingAreaBackgroundTransparent() const
{
	return mX11Wrapper->isCompositorActive() && AbstractImageGrabber::isSnippingAreaBackgroundTransparent();
}

QRect X11ImageGrabber::activeWindowRect() const
{
	return mX11Wrapper->getActiveWindowRect();
}

QRect X11ImageGrabber::fullScreenRect() const
{
	return mX11Wrapper->getFullScreenRect();
}

ImageWithPosition X11ImageGrabber::getCursorWithPosition() const
{
	return mX11Wrapper->getCursorWithPosition();
}
