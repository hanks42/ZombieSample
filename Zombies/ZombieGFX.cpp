#include ".\zombiegfx.h"

#include <stdlib.h>
#include <glut.h>	

ZombieGFX::ZombieGFX(void)
{
}

ZombieGFX::~ZombieGFX(void)
{
}

bool ZombieGFX::Init(int nWidth, int nHeight)
{
	// can't make a window of negative size
	if ((nWidth <= 0) || (nHeight <= 0))
		return false;

	m_nWinWidth = nWidth;
	m_nWinHeight = nHeight;

	/* Create the window and set it's properties */
	//glutInit("", "");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(m_nWinWidth, m_nWinHeight);
	glutInitWindowPosition(300,300);
	glutCreateWindow("Zombie Invasion!");
	gluOrtho2D(0, m_nWinWidth, 0, m_nWinHeight);

	// sweet success
	return true;
}

void ZombieGFX::ClearScreen()
{
	// back to black
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ZombieGFX::PostScreen()
{
	// we're using double buffering... thats double the brains!
	glutSwapBuffers();
	// make sure the display function is recalled next time
	glutPostRedisplay();
}

void ZombieGFX::DrawFullGrid()
{
	// draw the grid
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);

	// draw 10 by 10 grid
	for (int i = 0; i < 10; i++)
	{
		// horizontal lines
		glVertex2i(0, i*(m_nWinHeight/10));
		glVertex2i(m_nWinWidth, i*(m_nWinHeight/10));

		// vertical lines
		glVertex2i(i*(m_nWinWidth/10), 0);
		glVertex2i(i*(m_nWinWidth/10), m_nWinHeight);
	}

	glEnd();
	glPopMatrix();
}

void ZombieGFX::DrawZombie(int nXPos, int nYPos)
{
	// draw the zombie at that point
	// draw the grid
	glPushMatrix();
	glTranslatef(nXPos, nYPos, 0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);

		glVertex2i(-1,-1);
		glVertex2i(1,-1);
		glVertex2i(1,1);
		glVertex2i(-1,1);

	glEnd();
	glPopMatrix();
}

void ZombieGFX::DrawPerson(int nXPos, int nYPos)
{
	// draw the person at that point
	// draw the grid
	glPushMatrix();
	glTranslatef(nXPos, nYPos, 0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);

		glVertex2i(-1, -1);
		glVertex2i(1,-1);
		glVertex2i(1,1);
		glVertex2i(-1,1);

	glEnd();
	glPopMatrix();
}

void ZombieGFX::DrawPlayer(int nXPos, int nYPos)
{

	// draw the player
	glPushMatrix();
	glTranslatef(nXPos, nYPos, 0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);

	// draw a hexagon for the player
		glVertex2i(-2.5, -5);
		glVertex2i(2.5, -5);
		glVertex2i(5, 0);
		glVertex2i(2.5, 5);
		glVertex2i(-2.5, 5);
		glVertex2i(-5, 0);
		glVertex2i(-2.5, -5);

	glEnd();
	glPopMatrix();

}

void ZombieGFX::DrawScore(int nScore)
{
	// extract digits of the score and print them
	int nDigits[4];

	nDigits[0] = nScore/1000;
	nDigits[1] = (nScore/100)%10;
	nDigits[2] = (nScore/10)%10;
	nDigits[3] = nScore % 10;

	glColor3f(0.0, 1.0, 1.0);
	glRasterPos2i(0, 0);

	if (nScore < 0)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');

	for (int i = 0; i < 4; i++)
	{
		switch(abs(nDigits[i]))
		{
		case 0:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0');
			break;
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '5');
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
			break;
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '7');
			break;
		case 8:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '8');
			break;
		case 9:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '9');
			break;
		}
	}

}

void ZombieGFX::DrawBomb(int nXPos, int nYPos, float fRotation)
{
	// draw the bomb
	glPushMatrix();
	glTranslatef(nXPos, nYPos, 0);
	glRotatef(fRotation, 0, 0, 1);
	glColor3f(1.0, 1.0, 0);
	for (int r = 0; r < 4; r++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2i(0,0);
		glVertex2i(8,0);
		glVertex2i(15,15);
		glVertex2i(0,8);
		glEnd();
		glRotatef(90, 0, 0, 1);
	}
	glPopMatrix();
}

void ZombieGFX::DrawIntro()
{
	// white text
	glColor3f(0.0, 1.0, 0.0);

	// welcome to zombie invasion
	glRasterPos2i(50,300);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');

	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Z');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'b');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'v');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');

	// click to start
	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2i(120,200);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');

}


void ZombieGFX::DrawLossMessage()
{
	// red text
	glColor3f(1.0, 0, 0);

	// The city is lost! Click to play again!
	glRasterPos2i(120,300);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');

	glRasterPos2i(110,200);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');


}

void ZombieGFX::DrawFinalScore(int nScore)
{
	// Your final score is:

	// white text
	glColor3f(1.0, 1.0, 1.0);

	// The city is lost! Click to play again!
	glRasterPos2i(90,100);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'f');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');

	// extract digits of the score and print them
	int nDigits[4];

	nDigits[0] = nScore/1000;
	nDigits[1] = (nScore/100)%10;
	nDigits[2] = (nScore/10)%10;
	nDigits[3] = nScore % 10;


	if (nScore < 0)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');

	for (int i = 0; i < 4; i++)
	{
		switch(abs(nDigits[i]))
		{
		case 0:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0');
			break;
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '5');
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
			break;
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '7');
			break;
		case 8:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '8');
			break;
		case 9:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '9');
			break;
		}
	}


}

void ZombieGFX::DrawWinMessage()
{
	// red text
	glColor3f(1.0, 0, 1.0);

	// Hooray! You've saved the city!
	glRasterPos2i(50,300);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '\'');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'v');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'v');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');

	glRasterPos2i(110,200);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');
}