﻿#include "MFDSYSControl.h"

#include "Tools/Console.h"

auto MFDSYSControl::render() -> void {
	MFDBaseControl::render();
	nvgBeginPath(getContext());
	{
		nvgFillColor(getContext(), nvgRGB(255, 0, 0));
		nvgRect(getContext(), 0, 0, 200, 200);
		nvgFill(getContext());
	}
	nvgClosePath(getContext());
}

auto MFDINFOControl::render() -> void {
	MFDBaseControl::render();
	nvgBeginPath(getContext());
	{
		nvgFillColor(getContext(), nvgRGB(0, 255, 0));
		nvgRect(getContext(), 50, 50, 200, 200);
		nvgFill(getContext());
	}
	nvgClosePath(getContext());
}

auto MFDCOMMControl::render() -> void {
	MFDBaseControl::render();
	nvgBeginPath(getContext());
	{
		nvgFillColor(getContext(), nvgRGB(255, 255, 0));
		nvgRect(getContext(), 0, 0, 200, 200);
		nvgFill(getContext());
	}
	nvgClosePath(getContext());
}

auto MFDTest6Control::render() -> void {
	MFDBaseControl::render();
	nvgBeginPath(getContext());
	{
		nvgFillColor(getContext(), nvgRGB(255, 255, 255));
		nvgRect(getContext(), 0, 0, 200, 200);
		nvgFill(getContext());
	}
	nvgClosePath(getContext());
}