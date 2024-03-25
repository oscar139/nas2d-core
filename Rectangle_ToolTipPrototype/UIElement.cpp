#include "UIElement.h"
#include "NAS2D/Utility.h"

UIElement::UIElement(NAS2D::Rectangle<int> box)
{
	mBox = box;
}

void UIElement::onMouseMove(NAS2D::Point<int> position, NAS2D::Vector<int> change)
{
	position == position;
	change == change;
	// Do nothing
}

void UIElement::update()
{
	this->draw();
}

void UIElement::draw()
{
	auto& r = NAS2D::Utility<NAS2D::Renderer>::get();
	r.drawBoxFilled(mBox, NAS2D::Color::Red);
}