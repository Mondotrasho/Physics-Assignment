#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm/ext.hpp>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();



	static const glm::vec4 colours[] = {
		glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1),
glm::vec4(0,1,1,1)
	};

	static const int rows = 5;
	static const int columns = 10;
	static const int hSpace = 1;
	static const int vSpace = 1;

	static const glm::vec2 scrExtents(100, 50);
	static const glm::vec2 boxExtents(7, 3);
	static const glm::vec2 startPos(
		-(columns >> 1) * ((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f),
		scrExtents.y - ((boxExtents.y * 2) + hSpace));

	// draw the grid of blocks
	glm::vec2 pos;
	for (int y = 0; y < rows; y++) {
		pos = glm::vec2(startPos.x, startPos.y - (y * ((boxExtents.y * 2) + hSpace)));
		for (int x = 0; x < columns; x++) {
			aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]);
			pos.x += (boxExtents.x * 2) + vSpace;
		}
	}

	// draw the ball
	aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));
	// draw the player’s paddle
	aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2),
		glm::vec4(1, 0, 1, 1));


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::DemoUpdate(aie::Input* input,float deltaTime)
{
		// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);
	
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;
	
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;
	
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;
	
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;
	
	m_2dRenderer->setCameraPos(camPosX, camPosY);
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::DemoDraw()
{

	//// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);
	//
	//// demonstrate spinning sprite
	//m_2dRenderer->setUVRect(0,0,1,1);
	//m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);
	//
	//// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);
	//
	//// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);
	//
	//// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);
	//
	//// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
}