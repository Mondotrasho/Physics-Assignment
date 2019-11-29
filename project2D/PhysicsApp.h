#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Input.h"
#include <glm/vec2.hpp>

class Object
{
protected:
	glm::vec2 position;
	float radius;
public:
	void draw(aie::Renderer2D*);
};

struct Newtonian
{
	glm::vec2 position;
	glm::vec2 velocity;

	void update(float dt)
	{
		position += velocity * dt;
	}

	void accelerate(glm::vec2 a, float dt)
	{
		velocity += a * dt;
	}
};

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	void DemoUpdate(aie::Input* input, float deltaTime);
	
	virtual void draw();
	void brickbreakdraw();
	void DemoDraw();

protected:
	Newtonian obj;
	std::vector<std::vector<glm::vec2 >> positions;
	
	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	float m_timer;
};
