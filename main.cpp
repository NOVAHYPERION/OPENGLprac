#ifdef _WINDOWS
	#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ShaderProgram.h"
#include "Matrix.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#ifdef _WINDOWS
	#define RESOURCE_FOLDER ""
#else
	#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

SDL_Window* displayWindow;



struct gameObj
{
	float verts[12] = {  -0.125f, -.5f, -0.125f, .5f, .125f, .5f, -0.125f, -.5f, 0.125f, -.5f, .125f, .5f };
	//float verts[12] = { 0.0f, -1.0f, 0.0f, 1.0f, .5f, 1.0f, 0.0f, -1.0f, 0.5f, -1.0f, .5f, 1.0f };
	Matrix model;
	Matrix view;
	float x = 0.0f;
	float y = 0.0f;
	float width = .25f;
	float height = 1.0f;
	float max = 1.5f;
	float velx = 10.0f;
	void right()
	{
		x = 3;
	}
	void left()
	{
		x = -3;
	}
	void movepadel(float elapsed, float dir)
	{
		float tmp = y + velx*dir*elapsed;
		if (abs(tmp) <= max)
		{
			y += velx * dir*elapsed;
		}
		else if (abs(tmp) < abs(y))
		{
			y += velx*dir*elapsed;
		}
		//if (abs(tmp) < max)
		//{
		//	y = tmp;
		//
	}
	void draw(ShaderProgram* program)
	{
		model.Identity();
		model.Translate(x, y, 0.0f);
		program->SetModelMatrix(model);
		program->SetViewMatrix(view);
		glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, verts);
		glEnableVertexAttribArray(program->positionAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};

struct ball
{
	ball(Matrix modelM, Matrix viewM)
	{
		width = 0.1;
		height = 0.1;
		model = modelM;
		view = viewM;

	}
	Matrix model;
	Matrix view;
	float width  = .1f;
	float height = .1f;
	float y = 0.0f;
	float x = 0.0f;
	float max = 1.9f;
	float maxx = 3.8f;
	float verts[12] = { -0.05f, -0.05f, -0.05f, .05f, .05f, .05f, 0.05f, 0.05f, -0.05f, -0.05f, .05f, -0.05f };
	float flipy = 1.0f;
	float flipx = 1.0f;
	void collisiondetect(gameObj* obj)
	{
		/*if (obj->y + (obj->height / 2) >= (x + (height/2) && (x - (height/2)) >= (obj->y - (obj->height/2))))
		{
			
		}*/
		bool rightpadde = obj->x == 3;
		bool leftpaddle = obj->x <= -3;
		float  paddleroof = obj->y + (obj->height / 2.0f);
		float paddlefloor = obj->y - (obj->height / 2.0f);
		float paddleleft = obj->x - (obj->width / 2.0f);
		float paddleright = obj->x + (obj->width / 2);

		float ballroof = y + (height / 2);
		float ballfloor = y - (height / 2);
		float ballright = x + (width/ 2);
		float ballleft = x - (width / 2);
		bool ballxpaddle = ((ballright >= paddleleft && ballleft <= paddleright) || (ballright >= paddleleft && ballleft < paddleleft) || (ballleft <= paddleright && ballright > paddleright));
		bool undertest = (ballroof >= paddlefloor && ballxpaddle && paddleroof > ballroof && paddlefloor > ballfloor);
		bool overtest = (ballfloor <= paddleroof && ballxpaddle && paddlefloor <= ballfloor && paddleroof < ballroof);
		bool inrange = (ballfloor <= paddleroof && ballxpaddle && ballroof >= paddlefloor);
		/*if (leftpaddle && (ballroof >= paddlefloor && ballxpaddle && paddleroof >= ballfloor))
		{
			flipy = -1.0f;
		}
		if (leftpaddle && ballfloor <= paddleroof && ballxpaddle && paddlefloor <= ballroof)
		{
			flipy = 1.0f;
		}
		if (rightpadde && undertest)
		{
			flipy = -1.0f;
		}
		if (rightpadde && overtest)
		{
			flipy = 1.0f;
		}*/
		if (leftpaddle && inrange)
		{
			flipx = 1.0f;
		}
		if (rightpadde && inrange)
		{
			flipx = -1.0f;
		}
		/*if ((obj->x <= -3 && obj->x + (obj->width / 2) - .1f >= (x - (width / 2))) && (obj->y + (obj->height / 2) >= (y - (height / 2))) && (obj->y - (obj->height / 2) <= (y - (height / 2))))
		
			flipy = 1.0f;
		}
		if ((obj->x <= -3 && obj->x + (obj->width / 2) - .1f >= (x - (width / 2))) && (obj->y - (obj->height / 2) >= (y + (height / 2))) && (obj->y + (obj->height / 2) <= (y + (height / 2))))
		{
			flipy = -1.0f;
		}

		if ((obj->x == 3 && (obj->x - (obj->width / 2)) + .25f <= (x + (width / 2))) && (obj->y+ (obj->height / 2) <= (y - (height / 2))) && (obj->y - (obj->height / 2) <= (y - (height / 2))))
		{
			flipy = 1.0f;
		}

		if ((obj->x == 3 && (obj->x - (obj->width / 2)) + .25f <= (x + (width / 2))) && (obj->y - (obj->height / 2) >= (y + (height / 2))) && (obj->y + (obj->height / 2) <= (y + (height / 2))))
		{
			flipy = -1.0f;
		}
		*/
		/*if ((obj->x <= -3 && obj->x + (obj->width / 2) - .1f >= (x - (width / 2))) 
			&& 
			((obj->y + (obj->height / 2.0f) >= y - (height / 2))) && (y + (height / 2.0f) >= obj->y - (obj->height / 2.0f)))
		{
			flipx = 1.0f;
		}

		if ((obj->x == 3 && (obj->x - (obj->width / 2)) + .25f <= (x + (width / 2)))
			&&
			((obj->y + (obj->height / 2.0f) >= y - (height / 2))) && (y + (height / 2.0f) >= obj->y - (obj->height / 2.0f)))
		{
			flipx = -1.0f;
		}*/	
	}

	void reset()
	{
		x = 0;
		y = 0;
	}
	void go(gameObj* obj, float elapsed)
	{
		float tmpx = x + 2.5 * flipx*elapsed;
		float tmpy = y + 2.5 * flipy*elapsed;
		float  paddleroof = obj->y + (obj->height / 2.0f);
		float paddlefloor = obj->y - (obj->height / 2.0f);
		float paddleleft = obj->x - (obj->width / 2.0f);
		float paddleright = obj->x + (obj->width / 2.0f);

		float tmpballroof = tmpy + (height / 2.0f);
		float tmpballfloor = tmpy - (height / 2.0f);
		float tmpballright = tmpx + (width / 2.0f);
		float tmpballleft = tmpx - (width / 2.0f);
		float ballright = x + (width / 2.0f);
		float ballleft = x - (width / 2.0f);
		bool ballxpaddle = ((ballright >= paddleleft && ballleft <= paddleright) || (ballright >= paddleleft && ballleft < paddleleft) || (ballleft <= paddleright && ballright > paddleright));
		bool undertest = (tmpballroof >= paddlefloor && ballxpaddle && paddleroof > tmpballroof && paddlefloor > tmpballfloor);
		bool overtest = (tmpballfloor <= paddleroof && ballxpaddle && paddlefloor <= tmpballfloor && paddleroof < tmpballroof);
		if (abs(tmpy) < max)
		{
			if (undertest || overtest)
			{
				flipy = -1.0f;
				y = y + .0005 * flipy;
			}
		}

		if (tmpy < 0)
		{
			if (abs(tmpy) < max)
			{
				y = tmpy;
			}
			else
			{
				flipy = 1;
			}
		}
		else
		{
			if (tmpy < max)
			{
				y = tmpy;
			}

			else
			{
				flipy = -1.0f;
			}
		}
		if (tmpx < 0)
		{
			if (abs(tmpx) < maxx)
			{
				x = tmpx;
			}
			else
			{
				reset();
			}
		}
		else
		{
			if (tmpx < maxx)
			{
				x = tmpx;
			}
			else
			{
				reset();
			}
		}
	}
	void draw(ShaderProgram* program)
	{
		model.Identity();
		model.Translate(x, y, 0.0f);
		program->SetModelMatrix(model);
		program->SetViewMatrix(view);
		glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, verts);
		glEnableVertexAttribArray(program->positionAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif

	SDL_Event event;
	bool done = false;
	glClearColor(.4f, .22f,.4f, 1.0f);
	ShaderProgram program;
	program.Load(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl");
	Matrix projectionMatrix;
	projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
	float lastFrameTicks = 0.0f;
	gameObj leftpadel;
	gameObj rightpadel;

	Matrix leftModel;
	Matrix leftView;
	Matrix rightModel;
	Matrix rightView;
	Matrix ballModel;
	Matrix ballView;
	leftModel.Translate(0.0f, .6f, 0.0f);

	leftpadel.model = leftModel;
	leftpadel.view = leftView;
	rightpadel.model = rightModel;
	rightpadel.view = rightView;
	ball ball(ballModel, ballView);

	leftpadel.left();
	rightpadel.right();


	int growmaybe = 0;
	bool indeedgrow = true;
	glUseProgram(program.programID);
	glClearColor(.4f, .9f, .4f, 1.0f);
	while (!done) {
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
		/*if (event.type == SDL_KEYDOWN)
		{*/
		if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_UP])
		{
			leftpadel.movepadel(elapsed, 1);
			rightpadel.movepadel(elapsed, 1);
		}
		else if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_DOWN])
				{
					leftpadel.movepadel(elapsed, -1);
					rightpadel.movepadel(elapsed, -1);
				}
				else if (keys[SDL_SCANCODE_W])
				{
					leftpadel.movepadel(elapsed, 1);
				}
				else if (keys[SDL_SCANCODE_UP])
				{
					rightpadel.movepadel(elapsed, 1);
				}
				else if (keys[SDL_SCANCODE_S])
				{
					leftpadel.movepadel(elapsed, -1);
				}
				else if (keys[SDL_SCANCODE_DOWN])
				{
					rightpadel.movepadel(elapsed, -1);
				}
			//}
				
		glClear(GL_COLOR_BUFFER_BIT);

		ball.go(&leftpadel,elapsed);
		ball.go(&rightpadel,elapsed);
		ball.collisiondetect(&leftpadel);
		ball.collisiondetect(&rightpadel);
		leftpadel.draw(&program);
		rightpadel.draw(&program);
		ball.draw(&program);
		program.SetProjectionMatrix(projectionMatrix);
		glDisableVertexAttribArray(program.positionAttribute);
		
		
		SDL_GL_SwapWindow(displayWindow);
	}
	SDL_Quit();
	return 0;
}
