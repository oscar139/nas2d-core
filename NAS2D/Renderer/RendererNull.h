// ==================================================================================
// = NAS2D
// = Copyright © 2008 - 2019 New Age Software
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// =
// = Acknowledgement of your use of NAS2D is appriciated but is not required.
// ==================================================================================
#pragma once

#include "Renderer.h"

namespace NAS2D {

class RendererNull : public Renderer
{
public:
	RendererNull() = default;

	~RendererNull() override {}

	std::vector<DisplayDesc> getDisplayModes() const override { return {}; }
	DisplayDesc getClosestMatchingDisplayMode(const DisplayDesc&) const override { return{}; }
	Vector<int> getWindowClientArea() const noexcept override { return {}; }

	void drawImage(Image&, Point<float>, float = 1.0, Color = Color::Normal) override {}

	void drawSubImage(Image&, Point<float>, Rectangle<float>, Color = Color::Normal) override {}
	void drawSubImageRotated(Image&, Point<float>, Rectangle<float>, float, Color = Color::Normal) override {}

	void drawImageRotated(Image&, Point<float>, float, Color = Color::Normal, float = 1.0f) override {}
	void drawImageStretched(Image&, Rectangle<float>, Color = Color::Normal) override {}

	void drawImageRepeated(Image&, Rectangle<float>) override {}
	void drawSubImageRepeated(Image&, const Rectangle<float>&, const Rectangle<float>&) override {}

	void drawImageToImage(Image&, Image&, const Point<float>&) override {}

	void drawPoint(Point<float>, Color = Color::White) override {}
	void drawLine(float, float, float, float, uint8_t, uint8_t, uint8_t, uint8_t, int) override {}
	void drawBox(float, float, float, float, uint8_t, uint8_t, uint8_t, uint8_t) override {}
	void drawBoxFilled(float, float, float, float, uint8_t, uint8_t, uint8_t, uint8_t) override {}
	void drawCircle(float, float, float, uint8_t, uint8_t, uint8_t, uint8_t, int, float, float) override {}

	void drawGradient(float, float, float, float, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t) override {}

	void drawText(const Font&, std::string_view, float, float, uint8_t, uint8_t, uint8_t, uint8_t) override {}

	void showSystemPointer(bool) override {}
	void addCursor(const std::string&, int, int, int) override {}
	void setCursor(int) override {}

	void clearScreen(uint8_t, uint8_t, uint8_t) override {}

	float width() const override { return 0.0f; }
	float height() const override { return 0.0f; }

	void size(int, int) override {}
	void minimum_size(int, int) override {}

	void fullscreen(bool, bool = false) override {}
	bool fullscreen() const override { return false; }

	void resizeable(bool) override {}
	bool resizeable() const override { return false; }

	void clipRect(float, float, float, float) final override {}

	void window_icon(const std::string&) override {}

	void update() override {}

	void setViewport(const Rectangle<int>&) override {}
	void setOrthoProjection(const Rectangle<float>&) override {}
};

} // namespace
