#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Input.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	void DemoUpdate(aie::Input* input, float deltaTime);
	
	virtual void draw();
	void DemoDraw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	float m_timer;
};
