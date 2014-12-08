// OpenGL - Primitives.cpp : Defines the entry point for the console application.
//

//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

//Taking a x and y
void drawbox(double x, double y, sf::Vector3f colour)
{
	glBegin(GL_QUADS);

	glColor3f(colour.x, colour.y, colour.z);

	glVertex2d(-(x / 2), -(y / 2));

	glVertex2d(+(x / 2), -(y / 2));

	glVertex2d(+(x / 2), +(y / 2));

	glVertex2d(-(x / 2), +(y / 2));

	glEnd();

}

//Taking a sf::Vector2f
void drawbox(sf::Vector2f position, sf::Vector3f colour)
{
	glBegin(GL_QUADS);

	glColor3f(colour.x, colour.y, colour.z);

	glVertex2d(-(position.x / 2), -(position.y / 2));

	glVertex2d(+(position.x / 2), -(position.y / 2));

	glVertex2d(+(position.x / 2), +(position.y / 2));

	glVertex2d(-(position.x / 2), +(position.y / 2));

	glEnd();

}		
void MoveClaw(float clawPosition)
{
	//glPushMatrix();
	//glLoadIdentity();
	clawPosition -= 0.1f;
	glTranslatef(clawPosition, 0.0f, 0.0f);
	//glPopMatrix();
}
void Move(float boxPosition)
{
	//glPushMatrix();
	//glLoadIdentity();
	
	glTranslatef(boxPosition, -0.5f, 0.0f);
	//glPopMatrix();
}

int _tmain(int argc, _TCHAR* argv[])
{
	sf::RenderWindow window(sf::VideoMode(600, 600, 32), "Bouncing Balls");

	//Box
	sf::Vector2f box = sf::Vector2f(0.3f, 0.3f);
	float boxPosition = 0;

	//UpperArm
	sf::Vector2f upperArm = sf::Vector2f(0.1f, 0.5f);
	float upperArmRotation = 0;

	//LowerArm
	sf::Vector2f lowerArm = sf::Vector2f(0.1f, 0.3f);
	float lowerArmRotation = 0;

	//Claw
	sf::Vector2f claw = sf::Vector2f(0.05f, 0.2f);
	float clawRotation = 0;
	float clawPosition = .1;

	//glTranslatef(0.0f, -0.01f, 0.0f);

	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))	{ clawRotation++; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))	{ clawRotation--; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))	{ lowerArmRotation++; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	{ lowerArmRotation--; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	{ upperArmRotation++; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	{ upperArmRotation--; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))	{ boxPosition -= 0.05;}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))	{ boxPosition += 0.05;}

		}
		//prepare frame
		window.clear();
		window.setFramerateLimit(500);

		sf::Vector3f colour;
		colour = sf::Vector3f(1, 0, 0);

		glMatrixMode(GL_MODELVIEW);		//Selects current matrix
		
		//Draw Box
		Move(boxPosition);
		drawbox(box, colour);		//Square Drawing

		//Draw UpperArm
		colour = sf::Vector3f(0, 1, 0);

		glTranslatef(0.0f, 0.15f, 0.0f);		//move to rotate position
		glRotatef(upperArmRotation, 0, 0, 5);	//rotate
		glTranslatef(0.0f, 0.25f, 0.0f);		//move to final position

		drawbox(upperArm, colour);

		//Draw LowerArm
		colour = sf::Vector3f(0, 0, 1);

		glTranslatef(0.0f, 0.25f, 0.0f);
		glRotatef(lowerArmRotation, 0, 0, 1);
		glTranslatef(0.0f, 0.15f, 0.0f);

		drawbox(lowerArm, colour);

		//Draw Claw
		colour = sf::Vector3f(1, 1, 0);

		glPushMatrix();
		MoveClaw(clawPosition);
		glTranslatef(0.05f, 0.1f, 0.0f);
		glRotatef(clawRotation, 0, 0, 1);
		glTranslatef(0.0f, 0.5f, 0.0f);

		drawbox(claw, colour);

		glPopMatrix();
		MoveClaw(clawPosition);
		glTranslatef(-0.05f, 0.1f, 0.0f);
		glRotatef(clawRotation, 0, 0, 1);
		glTranslatef(0.0f, 0.05f, 0.0f);

		drawbox(claw, colour);

		glLoadIdentity();		//Resets the Matrix
		window.display();
	}
	return EXIT_SUCCESS;
}


//Notes :

//glLoadIdentity();		//Resets the Matrix
//glPushMatrix()	copy the current modelView
//glPopMatrix()		removes the matrix off the top of the stack
//glTranslated(GLdouble x, GLdouble y, GLdouble z);
//glScaled(GLdouble x, GLdouble y, GLdouble z);
//glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);