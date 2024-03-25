#pragma once

#include "NAS2D/State.h"
#include "NAS2D/EventHandler.h"
#include "NAS2D/Resource/Image.h"
#include "NAS2D/Renderer/Renderer.h"

#include <vector>

#include "Observable.h"
#include "Observer.h"


class TestToolTipPrototype : public NAS2D::State, public Observable
{
public:
	TestToolTipPrototype();
	~TestToolTipPrototype() override;
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notifyObservers();

protected:
	void initialize() override;
	NAS2D::State* update() override;

	void onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod, bool repeat);
	void onMouseMove(NAS2D::Point<int> position, NAS2D::Vector<int> change);
	void onMouseDown(NAS2D::EventHandler::MouseButton button, NAS2D::Point<int> position);

	void onWindowResized(int w, int h);

private:
	NAS2D::Image mDxImage;
	NAS2D::Image mOglImage;
	NAS2D::Renderer& r;
	std::vector<Observer*> mObservers;
};
