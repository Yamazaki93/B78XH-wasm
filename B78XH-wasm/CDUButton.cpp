//    B78XH-wasm
//    Copyright (C) 2022  Heavy Division
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "CDUButton.h"
#include "fmt/core.h"

void CDUButton::setContext(NVGcontext* context) {
	this->context = context;
}

void CDUButton::draw() {
	if(this->context != nullptr) {
		drawBackBorders();
		drawBackground();
		drawTitle();
		drawButtonBorders();
	} else {
		fmt::print(stderr, "BUTTON -> Missing context");
	}
}

void CDUButton::drawBackground() {
	
	nvgFillColor(this->context, nvgRGB(106, 107, 120));
	nvgBeginPath(this->context);
	{
		nvgRect(this->context, this->x, this->y, this->width, this->height);
	}
	nvgClosePath(this->context);
	nvgFill(this->context);
}

bool CDUButton::isInFocus() {
	this->calculateBounds();

	if(this->mouseMoveResolver.positionX >= this->bounds[0] && this->mouseMoveResolver.positionX <= this->bounds[1] &&
		this->mouseMoveResolver.positionY >= this->bounds[2] && this->mouseMoveResolver.positionY <= this->bounds[3]) {
		return true;
	}
	return false;
}

void CDUButton::shouldTriggerEvent() {
	this->calculateBounds();
	if(this->mouseClickResolver.positionX >= this->bounds[0] && this->mouseClickResolver.positionX <= this->bounds[1] &&
		this->mouseClickResolver.positionY >= this->bounds[2] && this->mouseClickResolver.positionY <= this->bounds[
			3]) {
		if(this->event) {
			this->mouseClickResolver.reset();
			this->event();
		}
	}
}


/**
 * Calculates bounds of object
 * {x1, x2, y1, y2}
 */
void CDUButton::calculateBounds() {
	this->bounds[0] = this->x;
	this->bounds[1] = this->x + this->width;
	this->bounds[2] = this->y;
	this->bounds[3] = this->y + this->height;
}

void CDUButton::drawTitle() {
	if(this->title != nullptr && this->title2 == nullptr) {
		const double textX = this->x + (this->width / 2);
		const double textY = this->y + (this->height / 2);
		nvgTextAlign(this->context, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
		nvgFillColor(this->context, nvgRGB(255, 255, 255));
		nvgBeginPath(this->context);
		{
			nvgText(this->context, textX, textY, this->title, nullptr);
		}
		nvgClosePath(this->context);
		nvgFill(this->context);
	} else if(this->title != nullptr && this->title2 != nullptr) {
		const double textX = this->x + (this->width / 2);
		const double textY = this->y + (this->height / 2) - 7;
		const double text2Y = this->y + (this->height / 2) + 7;
		nvgTextAlign(this->context, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
		nvgFillColor(this->context, nvgRGB(255, 255, 255));
		nvgBeginPath(this->context);
		{
			nvgText(this->context, textX, textY, this->title, nullptr);
			nvgText(this->context, textX, text2Y, this->title2, nullptr);
		}
		nvgClosePath(this->context);
		nvgFill(this->context);
	}
}

void CDUButton::drawButtonBorders() {

	/*
	 * TOP
	 */
	nvgFillColor(this->context, nvgRGB(185, 175, 196));
	nvgBeginPath(this->context);
	{
		nvgMoveTo(this->context, this->x, this->y);
		nvgLineTo(this->context, (this->x + this->width), (this->y));
		nvgLineTo(this->context, (this->x + this->width - this->borderWidth), (this->y + this->borderWidth));
		nvgLineTo(this->context, (this->x + this->borderWidth), (this->y + this->borderWidth));
		nvgLineTo(this->context, this->x, this->y);
	}
	nvgClosePath(this->context);
	nvgFill(this->context);

	/*
	 * RIGHT
	 */
	nvgFillColor(this->context, nvgRGB(35, 34, 36));
	nvgBeginPath(this->context);
	{
		nvgMoveTo(this->context, (this->x + this->width), (this->y));
		nvgLineTo(this->context, (this->x + this->width), (this->y + this->height) + 1);
		nvgLineTo(this->context, (this->x + this->width - this->borderWidth),
		          (this->y + this->height - this->borderWidth) + 1);
		nvgLineTo(this->context, (this->x + this->width - this->borderWidth), (this->y + this->borderWidth));
		nvgLineTo(this->context, (this->x + this->width), (this->y));
	}
	nvgClosePath(this->context);
	nvgFill(this->context);

	/*
	 * BOTTOM
	 */
	nvgFillColor(this->context, nvgRGB(26, 25, 28));
	nvgBeginPath(this->context);
	{
		nvgMoveTo(this->context, this->x, this->y + this->height);
		nvgLineTo(this->context, (this->x + this->width), (this->y + this->height));
		nvgLineTo(this->context, (this->x + this->width - this->borderWidth),
		          (this->y + this->height - this->borderWidth));
		nvgLineTo(this->context, (this->x + this->borderWidth), (this->y + this->height - this->borderWidth));
		nvgLineTo(this->context, this->x, this->y + this->height);
	}
	nvgClosePath(this->context);
	nvgFill(this->context);


	/*
	 * LEFT
	 */

	nvgFillColor(this->context, nvgRGB(196, 176, 200));
	nvgBeginPath(this->context);
	{
		nvgMoveTo(this->context, this->x, this->y);
		nvgLineTo(this->context, this->x + this->borderWidth, this->y + this->borderWidth);
		nvgLineTo(this->context, this->x + this->borderWidth, this->y + this->height - this->borderWidth);
		nvgLineTo(this->context, this->x, this->y + this->height);
		nvgLineTo(this->context, this->x, this->y);
	}
	nvgClosePath(this->context);
	nvgFill(this->context);
}

void CDUButton::drawBackBorders(NVGcolor color) {
	nvgStrokeWidth(this->context, 2);
	nvgStrokeColor(this->context, color);
	nvgBeginPath(this->context);
	{
		nvgRoundedRect(this->context, this->x - 1, this->y - 1, this->width + 2, this->height + 2, 2.0f);
	}
	nvgClosePath(this->context);
	nvgStroke(this->context);
}