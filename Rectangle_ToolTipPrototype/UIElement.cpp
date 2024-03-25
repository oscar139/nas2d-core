#include "UIElement.h"


UIElement::UIElement(NAS2D::Rectangle<int> box)
{
	auto& eventHandler = NAS2D::Utility<NAS2D::EventHandler>::get();
	eventHandler.mouseMotion().connect({this, &UIElement::onMouseMove});
	mBox = box;
}

void UIElement::onMouseMove(NAS2D::Point<int> position, NAS2D::Vector<int> change)
{
	if (mBox.contains(position))
	{
		mBoxColor = NAS2D::Color::Green;
	}
	else
	{
		mBoxColor = NAS2D::Color::Red;
	}
	change==change;
	// Do nothing
}

void UIElement::update()
{
	this->draw();
}

void UIElement::draw()
{
	auto& r = NAS2D::Utility<NAS2D::Renderer>::get();
	r.drawBoxFilled(mBox, mBoxColor);
}