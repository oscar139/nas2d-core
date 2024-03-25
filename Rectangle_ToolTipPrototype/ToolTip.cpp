#include "ToolTip.h"

ToolTip::ToolTip() :mBox{0, 0, 0, 0}, mTitle{"Default Title"}, mFont{"../../data/fonts/opensans.ttf", 16}
{
	mDescription.push_back("Default Text Line 1");
	mDescription.push_back("Default Text Line 2");
}

void ToolTip::draw()
{
	auto& r = NAS2D::Utility<NAS2D::Renderer>::get();
	r.drawText(mFont, mTitle, NAS2D::Point{mBox.position.x + 5, mBox.position.y + 5}, NAS2D::Color::Red);
}