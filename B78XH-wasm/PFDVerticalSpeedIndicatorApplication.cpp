#include "PFDVerticalSpeedIndicatorApplication.h"

#include "Simplane.h"
#include "Tools.h"

using Colors = Tools::Colors;

void PFDVerticalSpeedIndicatorApplication::render(sGaugeDrawData* data) {
	drawBackground();
	drawGraduations();
	drawCursor();
	drawTargetPointer();
}

void PFDVerticalSpeedIndicatorApplication::drawBackground() {
	nvgSave(this->nvgContext);
	{
		nvgTranslate(this->nvgContext, 0, 161);
		{
			nvgFillColor(this->nvgContext, nvgRGBA(0, 0, 0, 100));
			nvgStrokeWidth(this->nvgContext, 1.0f);
			nvgStrokeColor(this->nvgContext, nvgRGBA(0, 0, 0, 250));

			nvgBeginPath(this->nvgContext);
			{
				nvgMoveTo(this->nvgContext, 0, -161);
				nvgLineTo(this->nvgContext, 26, -161);
				nvgLineTo(this->nvgContext, 54, -85);
				nvgLineTo(this->nvgContext, 54, 85);
				nvgLineTo(this->nvgContext, 26, 161);
				nvgLineTo(this->nvgContext, 0, 161);
				nvgLineTo(this->nvgContext, 0, 57);
				nvgLineTo(this->nvgContext, 16, 46);
				nvgLineTo(this->nvgContext, 16, -46);
				nvgLineTo(this->nvgContext, 0, -57);
			}
			nvgClosePath(this->nvgContext);
			nvgFill(this->nvgContext);
			nvgStroke(this->nvgContext);
		}
		nvgResetTransform(this->nvgContext);
	}
	nvgRestore(this->nvgContext);
}

void PFDVerticalSpeedIndicatorApplication::drawGraduations() {
	constexpr auto height = 2.0f;

	/*
	 * DEFINITION:
	 * {offset, width}
	 */
	constexpr int offsetsMajor[4][2] = { {0, 20}, {68, 8}, {116, 8}, {150, 8} };

	constexpr int offsetsMinor[3][2] = { {34, 8}, {92, 8}, {133, 8}, };
	nvgSave(this->nvgContext);
	{
		nvgTranslate(this->nvgContext, 14, 161);
		{

			nvgStrokeColor(this->nvgContext, Colors::white);
			/*
			 * Major
			 */

			nvgStrokeWidth(this->nvgContext, 3.0f);
			nvgShapeAntiAlias(this->nvgContext, false);

			nvgBeginPath(this->nvgContext);
			{
				for (int i = 0; i < 4; i++) {
					nvgMoveTo(this->nvgContext, 0, offsetsMajor[i][0]);
					nvgLineTo(this->nvgContext, offsetsMajor[i][1], offsetsMajor[i][0]);
					if (i == 0) {
						continue;
					}
					nvgMoveTo(this->nvgContext, 0, -offsetsMajor[i][0]);
					nvgLineTo(this->nvgContext, offsetsMajor[i][1], -offsetsMajor[i][0]);
				}
			}

			nvgStroke(this->nvgContext);

			/*
			 * Major Texts
			 */

			nvgFontFace(this->nvgContext, "roboto");
			nvgFontSize(this->nvgContext, 20.0f);
			nvgTextAlign(this->nvgContext, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
			nvgFillColor(this->nvgContext, Colors::white);
			nvgBeginPath(this->nvgContext);
			{
				nvgText(this->nvgContext, -2, offsetsMajor[1][0], "1", nullptr);
				nvgText(this->nvgContext, -2, -offsetsMajor[1][0], "1", nullptr);
				nvgText(this->nvgContext, -2, offsetsMajor[2][0], "2", nullptr);
				nvgText(this->nvgContext, -2, -offsetsMajor[2][0], "2", nullptr);
				nvgText(this->nvgContext, -2, offsetsMajor[3][0], "6", nullptr);
				nvgText(this->nvgContext, -2, -offsetsMajor[3][0], "6", nullptr);
			}
			nvgClosePath(this->nvgContext);
			nvgFill(this->nvgContext);

			/*
			 * Minor
			 */
			nvgStrokeWidth(this->nvgContext, 2.0f);
			nvgBeginPath(this->nvgContext);
			{
				for (int i = 0; i < 3; i++) {
					nvgMoveTo(this->nvgContext, 0, offsetsMinor[i][0]);
					nvgLineTo(this->nvgContext, offsetsMinor[i][1], offsetsMinor[i][0]);
					nvgMoveTo(this->nvgContext, 0, -offsetsMinor[i][0]);
					nvgLineTo(this->nvgContext, offsetsMinor[i][1], -offsetsMinor[i][0]);
				}
			}
			nvgClosePath(this->nvgContext);
			nvgStroke(this->nvgContext);
			nvgShapeAntiAlias(this->nvgContext, true);
		}
		nvgResetTransform(this->nvgContext);
	}
	nvgRestore(this->nvgContext);
}

void PFDVerticalSpeedIndicatorApplication::drawCursor() {
	namespace Aircraft = Simplane::aircraft;
	const double verticalSpeed = Aircraft::state::verticalSpeed();
	/*
	 * grad 1 -> 34px = 500 feet = 0.68 px per feet
	 * grad 2 -> 34px = 500 feet = 0.68 px per feet
	 * grad 3 -> 24px = 500 feet = 0.48 px per feet
	 * grad 4 -> 24px = 500 feet = 0.48 px per feet
	 * grad 5 -> 17px = 2000 feet = 0.085 px per feet
	 * grad 6 -> 17px = 2000 feet = 0.085 px per feet
	 */

	const bool isVerticalSpeedNegative = verticalSpeed < 0;
	const double absoluteVerticalSpeed = abs(verticalSpeed);
	const double numberOf2000 = absoluteVerticalSpeed / 2000;
	double offset = 0;

	if (numberOf2000 >= 3) {
		offset = 150;
	}
	else if (absoluteVerticalSpeed <= 1000) {
		offset = (absoluteVerticalSpeed * 0.068);
	}
	else if (absoluteVerticalSpeed <= 2000) {
		offset = ((absoluteVerticalSpeed - 1000) * 0.048) + 68;
	}
	else if (absoluteVerticalSpeed <= 6000) {
		offset = ((absoluteVerticalSpeed - 2000) * 0.0085) + 116;
	}

	offset = (isVerticalSpeedNegative ? offset : -offset);

	nvgSave(this->nvgContext);
	{
		nvgStrokeWidth(this->nvgContext, 3.0f);
		nvgStrokeColor(this->nvgContext, Colors::white);
		nvgLineCap(this->nvgContext, NVG_ROUND);
		nvgTranslate(this->nvgContext, 120, 161);
		{
			nvgScissor(this->nvgContext, -105, -160, 38, 320);
			nvgBeginPath(this->nvgContext);
			{
				nvgMoveTo(this->nvgContext, -25, 0);
				nvgLineTo(this->nvgContext, -100, offset);
			}
			nvgClosePath(this->nvgContext);
			nvgStroke(this->nvgContext);
			nvgResetScissor(this->nvgContext);
		}
		nvgResetTransform(this->nvgContext);
	}
	nvgRestore(this->nvgContext);
}

void PFDVerticalSpeedIndicatorApplication::drawTargetPointer() {
	namespace Autopilot = Simplane::autopilot;
	if (!Autopilot::verticalSpeed::verticalSpeedHold()) {
		return;
	}
	const double verticalSpeedSelected = Autopilot::verticalSpeed::verticalSpeedHoldVar();

	const bool isVerticalSpeedNegative = verticalSpeedSelected < 0;
	const double absoluteVerticalSpeed = abs(verticalSpeedSelected);
	const double numberOf2000 = absoluteVerticalSpeed / 2000;
	double offset = 0;

	if (numberOf2000 >= 3) {
		offset = 150;
	}
	else if (absoluteVerticalSpeed <= 1000) {
		offset = (absoluteVerticalSpeed * 0.068);
	}
	else if (absoluteVerticalSpeed <= 2000) {
		offset = ((absoluteVerticalSpeed - 1000) * 0.048) + 68;
	}
	else if (absoluteVerticalSpeed <= 6000) {
		offset = ((absoluteVerticalSpeed - 2000) * 0.0085) + 116;
	}

	offset = (isVerticalSpeedNegative ? offset : -offset);

	nvgSave(this->nvgContext);
	{
		nvgTranslate(this->nvgContext, 14, 161);
		{
			nvgStrokeWidth(this->nvgContext, 4);
			nvgStrokeColor(this->nvgContext, Colors::magenta);
			nvgBeginPath(this->nvgContext);
			{
				nvgMoveTo(this->nvgContext, 0, offset);
				nvgLineTo(this->nvgContext, 10, offset);
			}
			nvgClosePath(this->nvgContext);
			nvgStroke(this->nvgContext);
		}
		nvgResetTransform(this->nvgContext);
	}

	nvgRestore(this->nvgContext);
}