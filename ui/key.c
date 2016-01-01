//key.c
//Erstellt: 01.01.2016

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

static int stdin_fd = -1;
static struct termios original;

bool keyPressed(int *character)
{
	int characters_buffered = 0;
	bool pressed;
	int c;

	if (stdin_fd == -1)
	{
		stdin_fd = fileno(stdin);
		tcgetattr(stdin_fd, &original);
		struct termios term;
		memcpy(&term, &original, sizeof(term));
		term.c_lflag &= ~(ICANON|ECHO);
	        tcsetattr(stdin_fd, TCSANOW, &term);
		setbuf(stdin, NULL);
	}

	ioctl(stdin_fd, FIONREAD, &characters_buffered);
	pressed = (characters_buffered != 0);

	if (characters_buffered == 1)
	{
		c = fgetc(stdin);
		if (character != NULL)
	        {
			*character = c;
	        }
	}
	else if (characters_buffered > 1)
	{
		while (characters_buffered)
		{
			fgetc(stdin);
			characters_buffered--;
		}
	}

	return pressed;
}

void keyboardReset()
{
	if (stdin_fd != -1)
	{		
		tcsetattr(stdin_fd, TCSANOW, &original);
	}
}
