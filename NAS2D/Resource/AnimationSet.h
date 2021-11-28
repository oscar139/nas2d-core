// ==================================================================================
// = NAS2D
// = Copyright © 2008 - 2020 New Age Software
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// =
// = Acknowledgment of your use of NAS2D is appreciated but is not required.
// ==================================================================================

#pragma once

#include "Image.h"
#include "../Math/Vector.h"
#include "../Math/Rectangle.h"

#include <map>
#include <vector>
#include <string>


namespace NAS2D
{

	class AnimationSet
	{
	public:
		struct Frame
		{
			const Image& image;
			Rectangle<int> bounds;
			Vector<int> anchorOffset;
			unsigned int frameDelay;

			bool isStopFrame() const;
		};

		using ImageSheetMap = std::map<std::string, std::string>;
		using ActionsMap = std::map<std::string, std::vector<Frame>>;


		AnimationSet(std::string fileName);
		AnimationSet(std::string fileName, ImageSheetMap imageSheetMap, ActionsMap actions);

		std::vector<std::string> actionNames() const;
		const std::vector<Frame>& frames(const std::string& actionName) const;

	private:
		std::string mFileName;
		ImageSheetMap mImageSheetMap;
		ActionsMap mActions;
	};

} // namespace
