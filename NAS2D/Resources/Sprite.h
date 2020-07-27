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

#include "Image.h"
#include "../Signal.h"
#include "../Timer.h"
#include "../Utility.h"
#include "../Filesystem.h"
#include "../Renderer/Color.h"
#include "../Renderer/Rectangle.h"
#include "../Renderer/Renderer.h"

#include <map>
#include <string>
#include <vector>

namespace NAS2D {

extern const std::string SPRITE_VERSION;

/**
 * \class Sprite
 * \brief Sprite Resource.
 *
 * The Sprite Class is a self-contained group of Image Resource's that displays
 * Image's at a specified screen coordinate in sequence to display an animation.
 */
class Sprite
{
public:
	using Callback = Signals::Signal<>; /**< Signal used when action animations complete. */

	explicit Sprite(const std::string& filePath);
	Sprite(const Sprite& sprite) = default;
	Sprite& operator=(const Sprite& rhs) = default;
	~Sprite() = default;

	Vector<int> size() const;
	Point<int> origin(Point<int> point) const;

	StringList actions() const;

	void play(const std::string& action);
	void pause();
	void resume();

	void setFrame(std::size_t frameIndex);
	void incrementFrame();
	void decrementFrame();

	void update(Point<float> position);

	void rotation(float angle);
	float rotation() const;

	void alpha(uint8_t alpha);
	uint8_t alpha() const;
	void color(const Color& color);
	const Color& color() const;

	Callback& frameCallback();

protected:
	const std::string& name() const;

private:
	struct SpriteFrame
	{
		const Image& image;
		Rectangle<int> bounds;
		Vector<int> anchorOffset;
		unsigned int frameDelay;
	};

	struct SpriteAnimations
	{
		std::map<std::string, Image> imageSheets;
		std::map<std::string, std::vector<SpriteFrame>> actions;
	};


	using FrameList = std::vector<SpriteFrame>;

	void processXml(const std::string& filePath);
	std::map<std::string, Image> processImageSheets(const void* root);
	std::map<std::string, FrameList> processActions(const std::map<std::string, Image>& imageSheets, const void* root);
	FrameList processFrames(const std::map<std::string, Image>& imageSheets, const std::string& action, const void* node);


	SpriteAnimations mSpriteAnimations;

	std::string mSpriteName;
	std::string mCurrentAction{"default"};

	bool mPaused{false};
	Timer mTimer;
	std::size_t mCurrentFrame{0};
	Callback mAnimationCompleteCallback;

	Color mColor{Color::Normal}; /**< Color tint to use for drawing the sprite. */
	float mRotationAngle{0.0f}; /**< Angle of rotation in degrees. */
};

} // namespace
