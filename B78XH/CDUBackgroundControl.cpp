﻿#include "CDUBackgroundControl.h"

auto CDUBackgroundControl::render() -> void {
	Control::render();

	nvgBeginPath(getContext());
	{
		nvgFillColor(getContext(), nvgRGB(97, 100, 127));
		nvgRect(getContext(), 0, 0, getRelativePosition().getWidth(), getRelativePosition().getHeight());
		nvgFill(getContext());
	}
	nvgClosePath(getContext());
}