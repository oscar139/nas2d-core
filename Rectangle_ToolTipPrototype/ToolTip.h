#pragma once

#include "NAS2D/Renderer/Renderer.h"
#include "NAS2D/EventHandler.h"
#include "NAS2D/Utility.h"
#include "NAS2D/Math/Rectangle.h"
#include <NAS2D/Resource/Font.h>

#include <string.h>
#include <vector>

class ToolTip
{
	public:
		ToolTip();
		void draw();

	private:
		std::string mTitle;
		std::vector<std::string> mDescription;
		NAS2D::Rectangle<int> mBox;
		NAS2D::Font mFont;
};
