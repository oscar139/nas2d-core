#pragma once
#include "Observer.h"
#include "NAS2D/Renderer/Renderer.h"
#include "NAS2D/Math/Rectangle.h"
#include "ToolTip.h"

class UIElement : public Observer
{
	public:
		UIElement(NAS2D::Rectangle<int> box);
		void update();
		void draw();

	protected:
		void onMouseMove(NAS2D::Point<int> position, NAS2D::Vector<int> change);

	private:
		ToolTip mToolTip;
		NAS2D::Rectangle<int> mBox;
};