#include "../glut_lib/glut.h"
#include <iostream>
#include <vector>

#include "my_engine/my_3d_object_with_color.h"
#include "my_engine/my_3d_camera.h"
#include <thread>

void MyDrawFunction();

class MyGame
{
	// my 3D objects
	protected: std::vector<std::unique_ptr<My3D_ObjectWithColor>> m_arrPointers_ObjectWithColor;
	protected: My3D_Camera m_my3D_Camera;

	// functions
	public: void OnNextTick();
	public: void OnInitLevel();
	public: void DrawGraphic_OpenGL();
};

MyGame g_MyGame;
timespec _currentTime = timespec();
struct timespec _lastTime;
float TURN_TIMES_IN_SECONDS = 0.02f; // 50 times per second

void MyIdleFunction()
{
	// get current time
	_currentTime.tv_sec = _currentTime.tv_nsec = 0;
	::timespec_get(& _currentTime, TIME_UTC);

	// is ellapsed time
	if (((_currentTime.tv_sec - _lastTime.tv_sec) + (_currentTime.tv_nsec - _lastTime.tv_nsec) / 1000000000.f) >= TURN_TIMES_IN_SECONDS)
	{
		// set last time
		_lastTime.tv_sec = _currentTime.tv_sec;
		_lastTime.tv_nsec = _currentTime.tv_nsec;

		// next draw and logic
		MyDrawFunction();
		g_MyGame.OnNextTick();
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("2Proj_Flying_along_3D_pyramids");

	g_MyGame.OnInitLevel();

	// init OpenGL
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// for alpha color (transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable draw lines and colors
	glEnableClientState(GL_VERTEX_ARRAY);// allow to use glVertexPointer
	glEnableClientState(GL_COLOR_ARRAY); // allow to use glColorPointer

	glutDisplayFunc(MyDrawFunction);
	glutIdleFunc(MyIdleFunction);

	glutMainLoop();

	return 0;
}

void MyDrawFunction()
{
	g_MyGame.DrawGraphic_OpenGL();

	glFlush();
}

///////////// my game ///////////////
void MyGame::OnInitLevel()
{
	m_arrPointers_ObjectWithColor.clear();

	// add red Pyramid
	m_arrPointers_ObjectWithColor.push_back(std::unique_ptr<My3D_ObjectWithColor>(
		new My3D_PyramidWithColor(
			XYZ(4, 6, 60),
			12,
			RGBA(1, 0, 0, 1),
			RGBA(0.2, 0, 0, 1))
	));

	// add green Pyramid
	m_arrPointers_ObjectWithColor.push_back(std::unique_ptr<My3D_ObjectWithColor>(
		new My3D_PyramidWithColor(
			XYZ(0, 2.5f, 38),
			5,
			RGBA(0, 1, 0, 1),
			RGBA(0, 0.2, 0, 1))
	));

	// add yellow Pyramid
	m_arrPointers_ObjectWithColor.push_back(std::unique_ptr<My3D_ObjectWithColor>(
		new My3D_PyramidWithColor(
			XYZ(-6, 4, 120),
			8,
			RGBA(1, 1, 0, 1),
			RGBA(0.2, 0.2, 0, 1))
	));

	// add rectangle
	m_arrPointers_ObjectWithColor.push_back(std::unique_ptr<My3D_ObjectWithColor>(
		new My3D_RectWithColor(
			XYZ(0, 0, 140),
			50,
			280,
			RGBA(0, 0, 1, 1))
	));

	// init camera
	m_my3D_Camera.Init(0.1f, // zNear
		100.f, // zFar
		{ 0, 7, 0 },  // camera position
		{ 0, 7, 1 });  // camera look at
}

void MyGame::DrawGraphic_OpenGL()
{
	// draw background (green color)
	glClearColor(0.72f, 0.87f, 0.55f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// apply camera position to openGl matrix
	m_my3D_Camera.ApplyCameraPosition_to_OpenGLMatrix();

	// draw my 3D objects
	for (int i = 0; i < m_arrPointers_ObjectWithColor.size(); i++)
		m_arrPointers_ObjectWithColor[i]->RenderWithColor();
}

void MyGame::OnNextTick()
{
	m_my3D_Camera.MoveCamera(0, -0.007f, 0.2f);

	if (m_my3D_Camera.GetCameraPosition().Z > 120)
		OnInitLevel(); // start again
}