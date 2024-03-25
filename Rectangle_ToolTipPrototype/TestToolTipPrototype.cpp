#include "TestToolTipPrototype.h"

#include <NAS2D/Utility.h>
#include <NAS2D/Renderer/Renderer.h>
#include <NAS2D/Math/Rectangle.h>

#include <functional>
#include <random>



TestToolTipPrototype::TestToolTipPrototype() :
	mDxImage{"Test_DirectX.png"},
	mOglImage{"Test_OpenGL.png"},
	r{NAS2D::Utility<NAS2D::Renderer>::get()}
{
}

TestToolTipPrototype::~TestToolTipPrototype()
{
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseMotion().disconnect({this, &TestToolTipPrototype::onMouseMove});
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseButtonDown().disconnect({this, &TestToolTipPrototype::onMouseDown});
	NAS2D::Utility<NAS2D::EventHandler>::get().keyDown().disconnect({this, &TestToolTipPrototype::onKeyDown});

}

void TestToolTipPrototype::initialize()
{
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseMotion().connect({this, &TestToolTipPrototype::onMouseMove});
	NAS2D::Utility<NAS2D::EventHandler>::get().mouseButtonDown().connect({this, &TestToolTipPrototype::onMouseDown});
	NAS2D::Utility<NAS2D::EventHandler>::get().keyDown().connect({this, &TestToolTipPrototype::onKeyDown});

	NAS2D::Utility<NAS2D::Renderer>::get().showSystemPointer(true);
	NAS2D::Utility<NAS2D::Renderer>::get().minimumSize({1600, 900});

	r.drawImage(mDxImage, {256, 256});
	r.drawImage(mOglImage, {768, 256});

	UIElement* boxElement = new UIElement(NAS2D::Rectangle{100, 100, 100, 100}.normalized());
	mObservers.push_back(boxElement);
}

NAS2D::State* TestToolTipPrototype::update()
{
	r.clearScreen(NAS2D::Color::Gray);
	notifyObservers();

	return this;
}

void TestToolTipPrototype::onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier /*mod*/, bool /*repeat*/)
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

void TestToolTipPrototype::onMouseMove(NAS2D::Point<int> /*position*/, NAS2D::Vector<int> /*change*/)
{}

void TestToolTipPrototype::onMouseDown(NAS2D::EventHandler::MouseButton /*button*/, NAS2D::Point<int> /*position*/)
{}

void TestToolTipPrototype::onWindowResized(int /*w*/, int /*h*/)
{}

void TestToolTipPrototype ::addObserver(Observer* observer)
{
		mObservers.push_back(observer);
}

void TestToolTipPrototype::removeObserver(Observer* observer)
{
	mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
}

void TestToolTipPrototype::notifyObservers()
{
	for (auto observer : mObservers)
	{
		observer->update();
	}
}