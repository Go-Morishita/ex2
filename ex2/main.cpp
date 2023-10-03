//
//  main.cpp
//
//  Created by Yonghao Yue on 2019/09/28.
//  Updated: 2021/10/06
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

/*
* 青山学院大学 理工学部情報テクノロジー学科
* デジタルメディア設計演習第2回課題
* 共同制作 森下剛・堀田大智・中江智弘
* 解答は関数drewCG_1～4内で作成
*/

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <unistd.h>
#else
#include <GL/freeglut.h>
#include <Windows.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "Camera.h"

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

int width = 640;
int height = 480;
int mx, my;

Camera g_Camera;

/*カメラの中心にある最初の三角形の座標vertexの値は
* glVertex3f(0.0, 0.8, 0.0);				
* glVertex3f(-0.8, -0.8, 0.0);
* glVertex3f(0.8, -0.8, 0.0);
*/

//演習問題1
void drawCG_1() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.3, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.6, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.3, 0.4, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(6.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(3.0, 4.0, 0.0);
	glEnd();
}

void drawCG_2() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.8, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.8, -0.8, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.8, -0.8, 0.0);
	glEnd();
}

void drawCG_3() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.8, 0.0);
	glColor3f(0.0, 1.0, 0.0);				
	glVertex3f(-0.8, -0.8, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.8, -0.8, 0.0);
	glEnd();
}

void drawCG_4() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.8, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.8, -0.8, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.8, -0.8, 0.0);
	glEnd();
}

void idle()
{
#ifdef __APPLE__
  usleep( 1000.0 * 1000.0 / 60.0 ); // in microseconds
#else
  Sleep(1000.0/60.0); // in milliseconds
#endif
  glutPostRedisplay();
}

void projection_and_modelview( const Camera& in_Camera )
{
  const double fovy_deg = ( 2.0 * 180.0 / M_PI ) * atan( 0.024 * 0.5 / in_Camera.getFocalLength() );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fovy_deg, double( width ) / double( height ), 0.01 * in_Camera.getFocalLength(), 1000.0 );
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  const Eigen::Vector3d lookAtPoint = in_Camera.getLookAtPoint();
  gluLookAt( in_Camera.getEyePoint().x(), in_Camera.getEyePoint().y(), in_Camera.getEyePoint().z(), lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z(), in_Camera.getYVector().x(), in_Camera.getYVector().y(), in_Camera.getYVector().z() );
}

void drawFloor() {
	glBegin(GL_TRIANGLES);
	for (int j = -20; j < 20; j++) {
		for (int i = -20; i < 20; i++) {
			int cheaker_bw = (i + j) % 2;
			if (cheaker_bw == 0)
			{
				glColor3f(0.3, 0.3, 0.3);

				glVertex3f(i * 0.5, 0.0, j * 0.5);
				glVertex3f(i * 0.5, 0.0, (j+1) * 0.5);
				glVertex3f((i+1) * 0.5, 0.0, j * 0.5);

				glVertex3f(i * 0.5, 0.0, (j+1) * 0.5);
				glVertex3f((i+1) * 0.5, 0.0, (j+1) * 0.5);
				glVertex3f((i+1) * 0.5, 0.0, j * 0.5);
			} 
		}
	}
}

void display()
{
  glViewport( 0, 0, width * g_FrameSize_WindowSize_Scale_x, height * g_FrameSize_WindowSize_Scale_y );
  
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  projection_and_modelview( g_Camera );
  
  glEnable( GL_DEPTH_TEST );

  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_BLEND );
  glEnable( GL_POINT_SMOOTH );
  glEnable( GL_LINE_SMOOTH );
  glEnable( GL_POLYGON_SMOOTH);
  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
  glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
  glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

  drawFloor();

  drawCG_1();

  drawCG_2();

  drawCG_3();

  drawCG_4();
  
  glutSwapBuffers();
}

void resize( int w, int h )
{
  width = w;
  height = h;
}

void mouseDrag(int x, int y) {
	const int _dx = x - mx;
	mx = x;
	my = y;

	const double dx = double(_dx) / double(width);
	const double scale = 2.0;

	g_Camera.rotateCameraInLocalFrameFixLookAt(dx * scale);
	glutPostRedisplay();
}

void mouseDown(int x, int y) {
	mx = x;
	my = y;
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT && state == GLUT_DOWN)
		mouseDown(x, y);
}

int main( int argc, char* argv[] )
{
  g_Camera.setEyePoint( Eigen::Vector3d{ 0.0, 1.0, 3.0 } );
  g_Camera.lookAt( Eigen::Vector3d{ 0.0, 0.0, 0.0 }, Eigen::Vector3d{ 0.0, 1.0, 0.0} );
  
  glutInit( &argc, argv );
  glutInitWindowSize( width, height );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE );
  
  glutCreateWindow( "Hello world!!" );
  
  // With retina display, frame buffer size is twice the window size.
  // Viewport size should be set on the basis of the frame buffer size, rather than the window size.
  // g_FrameSize_WindowSize_Scale_x and g_FrameSize_WindowSize_Scale_y account for this factor.
  GLint dims[4] = {0};
  glGetIntegerv(GL_VIEWPORT, dims);
  g_FrameSize_WindowSize_Scale_x = double( dims[2] ) / double( width );
  g_FrameSize_WindowSize_Scale_y = double( dims[3] ) / double( height );
  
  glutDisplayFunc( display );
  glutIdleFunc( idle );
  glutReshapeFunc( resize );
  glutMouseFunc(mouse);
  glutMotionFunc(mouseDrag);


  glutMainLoop();
  return 0;
}
