#include "TestGraphics.h"

#include <NAS2D/Utility.h>
#include <NAS2D/Renderer/Renderer.h>
#include <NAS2D/Math/Rectangle.h>

#include <functional>
#include <random>



TestGraphics::TestGraphics() :
	mDxImage{"Test_DirectX.png"},
	mOglImage{"Test_OpenGL.png"},
	r{NAS2D::Utility<NAS2D::Renderer>::get()}
{
}

TestGraphics::~TestGraphics()
{
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseMotion().disconnect({this, &TestGraphics::onMouseMove});
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseButtonDown().disconnect({this, &TestGraphics::onMouseDown});
	NAS2D::Utility<NAS2D::EventHandler>::get().keyDown().disconnect({this, &TestGraphics::onKeyDown});

}

void TestGraphics::initialize()
{
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseMotion().connect({this, &TestGraphics::onMouseMove});
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseButtonDown().connect({this, &TestGraphics::onMouseDown});
	NAS2D::Utility<NAS2D::EventHandler>::get().keyDown().connect({this, &TestGraphics::onKeyDown});

	NAS2D::Utility<NAS2D::Renderer>::get().showSystemPointer(true);
	NAS2D::Utility<NAS2D::Renderer>::get().minimumSize({1600, 900});

	r.drawImage(mDxImage, {256, 256});
	r.drawImage(mOglImage, {768, 256});
}

NAS2D::State* TestGraphics::update()
{
	r.clearScreen(NAS2D::Color::Gray);


	return this;
}

void TestGraphics::onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier /*mod*/, bool /*repeat*/)
{
	switch (key)
	{
	case NAS2D::EventHandler::KeyCode::KEY_ESCAPE:
		NAS2D::postQuitEvent();
		break;
	case NAS2D::EventHandler::KeyCode::KEY_F1:
	{
		auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();
		renderer.fullscreen(!renderer.fullscreen());
		break;
	}
	case NAS2D::EventHandler::KeyCode::KEY_F2:
	{
		auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();
		renderer.resizeable(!renderer.resizeable());
		break;
	}
	default:
		break;
	}
}

void TestGraphics::onMouseMove(NAS2D::Point<int> /*position*/, NAS2D::Vector<int> /*change*/)
{}

void TestGraphics::onMouseDown(NAS2D::EventHandler::MouseButton /*button*/, NAS2D::Point<int> /*position*/)
{}

void TestGraphics::onWindowResized(int /*w*/, int /*h*/)
{}
