#pragma once



void mouseMovePassive(int x, int y) 
{

}


void mouseClickMove(int x, int y)
{


}

void mouseClick(int key, int state, int x, int y) {

	int stat = glutGetModifiers();



	if (state == GLUT_DOWN)
	{
		switch (stat)
		{
		case 0:
			if (key == 0) //left click
			{

			}
			if (key == 1) { //middle click
	
			}

			if (key == 2) //right click
			{

			}

			if (key == 3) //scroll up
			{

			}

			if (key == 4) { //scroll down

			}

			break;

		case GLUT_ACTIVE_SHIFT:
			break;

		case GLUT_ACTIVE_ALT:

			break;
		default:
			break;
		}
	}

}
