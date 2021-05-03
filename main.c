/*-------------------------------------------*/
/*------------ STANDARD INCLUDES ------------*/
/*-------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


/*------------------------------------------*/
/*------------------ MATH ------------------*/
/*------------------------------------------*/
#define ORIGIN 0.0f, 0.0f, 0.0f
#define RIGHT 1.0f, 0.0f, 0.0f
#define UP 0.0f, 1.0f, 0.0f
#define FORWARD 0.0f, 0.0f, -1.0f


/*------------------------------------------*/
/*--------------- DATA TYPES ---------------*/
/*------------------------------------------*/
typedef struct Vec2 {
	float x, y;
} Vec2;

typedef struct Vec3 {
	float x, y, z;
} Vec3;

typedef struct Transform {
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
} Transform;


/*-----------------------------------------*/
/*--------------- CONSTANTS ---------------*/
/*-----------------------------------------*/
const float DEG2RAD = 3.14159265 / 180.0f;
const float RAD2DEG = 180.0f / 3.14159265;


/*------------------------------------------*/
/*------------ GLOBAL VARIABLES ------------*/
/*------------------------------------------*/
Vec2 WINDOW_SIZE = {1280, 960};
Vec2 WINDOW_CENTER = {640, 480};
float FOVY = 75.0f;
float ZNEAR = 10e-3;
float ZFAR = 10e3;
Transform CAM;
int KEYBOARD[128] = {0};
Vec2 MOTION;


/*-------------------------------------------*/
/*-------------- OBJ MESH DATA --------------*/
/*-------------------------------------------*/
#define MAX_VERTICES 60000
int VERTEX_COUNT;
Vec3 VERTICES[MAX_VERTICES];
Vec3 NORMALS[MAX_VERTICES];
Vec2 TEX_COORDS[MAX_VERTICES];

float x_max = -100000;
int DOOR_VERTEX_COUNT;
Vec3 DOOR_VERTICES[MAX_VERTICES];
Vec3 DOOR_NORMALS[MAX_VERTICES];
Vec2 DOOR_TEX_COORDS[MAX_VERTICES];

int WINDOWED_DOOR_VERTEX_COUNT;
Vec3 WINDOWED_DOOR_VERTICES[MAX_VERTICES];
Vec3 WINDOWED_DOOR_NORMALS[MAX_VERTICES];
Vec2 WINDOWED_DOOR_TEX_COORDS[MAX_VERTICES];

int WINDOW_VERTEX_COUNT;
Vec3 WINDOW_VERTICES[MAX_VERTICES];
Vec3 WINDOW_NORMALS[MAX_VERTICES];
Vec2 WINDOW_TEX_COORDS[MAX_VERTICES];


/*---------------------------------------------*/
/*-------------- SETUP FUNCTIONS --------------*/
/*---------------------------------------------*/
void init_gl();
void setup_lighting();
int load_obj(const char* path, int object);


/*---------------------------------------------*/
/*------------- CALLBACK FUNCIONS -------------*/
/*---------------------------------------------*/
void display();
void idle();
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void reshape(int width, int height);


/*---------------------------------------------*/
/*------------- DRAWING FUNCTIONS -------------*/
/*---------------------------------------------*/
void draw_grid(int n);


/*--------------------------------------------*/
/*-------------- MATH FUNCTIONS --------------*/
/*--------------------------------------------*/
Vec3 forward(Transform* t);
Vec3 right(Transform* t);
Vec3 up(Transform* t);
void move_door();


/*-------------------------------------------*/
/*-------------- MAIN FUNCTION --------------*/
/*-------------------------------------------*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// Setting the window size, display mode, window name and placing the mouse pointer to the center of the screen
	glutInitWindowSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Room");
	glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);	

	// Setting the callback functions
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutReshapeFunc(reshape);

	// Initializing some options of OpenGL and lighting
	init_gl();

	// Setting initial camera position outside the room and facing the door
	CAM.position = (Vec3) {2.0f, 4.0f, -15.0f};
	CAM.rotation = (Vec3) {0.0f, 90.0f, 0.0f};

	// Loading the object files
	if(!load_obj("objects/QuartoFinal.obj", 1))
    {
		perror("Erro ao abrir o arquivo");
		return -1;
	}
	if(!load_obj("objects/portaPrincipal.obj", 2))
    {
		perror("Erro ao abrir o arquivo");
		return -1;
	}
	if(!load_obj("objects/portaJanela.obj", 3))
    {
		perror("Erro ao abrir o arquivo");
		return -1;
	}
	if(!load_obj("objects/Janelas.obj", 4))
    {
		perror("Erro ao abrir o arquivo");
		return -1;
	}
	
	// Initializing main loop
	glutMainLoop();

	return 0;
}

/*-----------------------------------------------------------*/
/*--------------------- SETUP FUNCTIONS ---------------------*/
/*-----------------------------------------------------------*/
void init_gl()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_COLOR_MATERIAL);
	setup_lighting();
}

void setup_lighting()
{  
	float mat_specular[] = {1.0f, 1.0f, 1.0f};
	float mat_shininess[] = {80.0f};
	float light_diffuse[] = {0.75f, 0.75f, 0.75f};
	float light_position[] = {2.0f, 4.0f, 0.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int load_obj(const char* path, int object)
{
	FILE *fp = fopen(path, "r");

	if(!fp) return 0;

	char buffer[512] = "";
	int vertex_count = 0;
	int normal_count = 0;
	int tex_coord_count = 0;

	Vec3 vertices[MAX_VERTICES];
    Vec3 normals[MAX_VERTICES];
	Vec2 tex_coords[MAX_VERTICES];

	while(fgets(buffer, 512, fp))
	{
		// Comment
		if(buffer[0] == '#') continue;
		
		char* token = strtok(buffer, " ");
	
		if(strcmp(token, "v") == 0)
		{
			// Parse vertex
			vertices[vertex_count].x = atof(strtok(NULL, " "));
			vertices[vertex_count].y = atof(strtok(NULL, " "));
			vertices[vertex_count].z = atof(strtok(NULL, " "));
			vertex_count++;
		}
		else if(strcmp(token, "vn") == 0)
		{
			// Parse normal vector
			normals[normal_count].x = atof(strtok(NULL, " "));
			normals[normal_count].y = atof(strtok(NULL, " "));
			normals[normal_count].z = atof(strtok(NULL, " "));
			normal_count++;
		}
		else if(strcmp(token, "vt") == 0)
		{
			// Parse texture coordinate
			tex_coords[tex_coord_count].x = atof(strtok(NULL, " "));
			tex_coords[tex_coord_count].y = -atof(strtok(NULL, " "));
			tex_coord_count++;
		}
		else if(strcmp(token, "f") == 0)
		{
			// Parse face
			int i;
			for(i = 0; i < 3; i++)
			{
				if(object == 1) // Room
				{
					VERTICES[VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
					TEX_COORDS[VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
					NORMALS[VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
					VERTEX_COUNT++;
				}
				else if(object == 2) // Door
				{
					DOOR_VERTICES[DOOR_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
					DOOR_TEX_COORDS[DOOR_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
					DOOR_NORMALS[DOOR_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
					DOOR_VERTEX_COUNT++;
				}
				else if(object == 3) // Windowed door
				{
					WINDOWED_DOOR_VERTICES[WINDOWED_DOOR_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
					WINDOWED_DOOR_TEX_COORDS[WINDOWED_DOOR_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
					WINDOWED_DOOR_NORMALS[WINDOWED_DOOR_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
					WINDOWED_DOOR_VERTEX_COUNT++;
				}
				else // Windows
				{
					WINDOW_VERTICES[WINDOW_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
					WINDOW_TEX_COORDS[WINDOW_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
					WINDOW_NORMALS[WINDOW_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
					WINDOW_VERTEX_COUNT++;
				}
			}
		}
	}

	fclose(fp);

	return 1;
}


/*-----------------------------------------------------------*/
/*-------------------- CALLBACK FUNCIONS --------------------*/
/*-----------------------------------------------------------*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// View matrix
	Vec3 fwd = forward(&CAM);
	Vec3 u = up(&CAM);
	Vec3 eye = CAM.position;
	Vec3 center = {eye.x + fwd.x, eye.y + fwd.y, eye.z + fwd.z};

	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, u.x, u.y, u.z); 

	draw_grid(25);

	int i, j, k;
	glBegin(GL_TRIANGLES);
	for(i = 0; i < VERTEX_COUNT; i++)
	{
		glNormal3f(NORMALS[i].x, NORMALS[i].y, NORMALS[i].z);
		glTexCoord2f(TEX_COORDS[i].x, TEX_COORDS[i].y);
		glVertex3f(VERTICES[i].x, VERTICES[i].y, VERTICES[i].z);
	}
	for(i = 0; i < DOOR_VERTEX_COUNT; i++)
	{
		if(DOOR_VERTICES[i].x >= x_max)
			x_max = DOOR_VERTICES[i].x;
		glNormal3f(DOOR_NORMALS[i].x, DOOR_NORMALS[i].y, DOOR_NORMALS[i].z);
		glTexCoord2f(DOOR_TEX_COORDS[i].x, DOOR_TEX_COORDS[i].y);
		glVertex3f(DOOR_VERTICES[i].x, DOOR_VERTICES[i].y, DOOR_VERTICES[i].z);
	}
	for(i = 0; i < WINDOWED_DOOR_VERTEX_COUNT; i++)
	{
		glNormal3f(WINDOWED_DOOR_NORMALS[i].x, WINDOWED_DOOR_NORMALS[i].y, WINDOWED_DOOR_NORMALS[i].z);
		glTexCoord2f(WINDOWED_DOOR_TEX_COORDS[i].x, WINDOWED_DOOR_TEX_COORDS[i].y);
		glVertex3f(WINDOWED_DOOR_VERTICES[i].x, WINDOWED_DOOR_VERTICES[i].y, WINDOWED_DOOR_VERTICES[i].z);
	}
	for(i = 0; i < WINDOW_VERTEX_COUNT; i++)
	{
		glNormal3f(WINDOW_NORMALS[i].x, WINDOW_NORMALS[i].y, WINDOW_NORMALS[i].z);
		glTexCoord2f(WINDOW_TEX_COORDS[i].x, WINDOW_TEX_COORDS[i].y);
		glVertex3f(WINDOW_VERTICES[i].x, WINDOW_VERTICES[i].y, WINDOW_VERTICES[i].z);
	}
	glEnd();
	
	glutSwapBuffers();
}

void idle()
{
	// Forward movement
	int move_forward = KEYBOARD['w'] - KEYBOARD['s'];
	Vec3 fwd = forward(&CAM);
	
	if(KEYBOARD['1'])
		printf("%d\n", x_max);
	fwd.x *= KEYBOARD['c'] ? move_forward * 2 : move_forward;
	fwd.y = 0.0f; // Projects fwd in the xz plane
	fwd.z *= KEYBOARD['c'] ? move_forward * 2 : move_forward;

	// Lateral movement
	int move_right = KEYBOARD['d'] - KEYBOARD['a'];
	Vec3 rgt = right(&CAM);

	rgt.x *= move_right;
	rgt.z *= move_right;
	
	CAM.position.x += 0.1f * (fwd.x + rgt.x);
	CAM.position.z += 0.1f * (fwd.z + rgt.z);

	glutPostRedisplay();
}

void motion(int x, int y)
{ 
	static int wrap = 0;
	Vec2 delta;
	
    if (!wrap)
	{
        delta.x = x - WINDOW_CENTER.x;
        delta.y = y - WINDOW_CENTER.y;

		// If delta.y > 0 -> camera moving down
		// If delta.y < 0 -> camera moving up
		CAM.rotation.x += delta.y > 0 ? 1.0f : (delta.y < 0 ? -1.0f : 0.0f);
		// If delta.x > 0 -> camera moving left
		// If delta.x < 0 -> camera moving right
		CAM.rotation.y -= delta.x > 0 ? 1.0f : (delta.x < 0 ? -1.0f : 0.0f);

        wrap = 1;
		// Maintaing the mouse pointer in the middle
        glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);
    }
	else
	{
        wrap = 0;
    }
}

void keyboard(unsigned char key, int x, int y)
{
	// Escape key
	if(key == 27)
		glutLeaveMainLoop();

	// Setting the key as pressed
	KEYBOARD[tolower(key)] = 1;
}

void keyboard_up(unsigned char key, int x, int y)
{
	// Resetting the key as not pressed
	KEYBOARD[tolower(key)] = 0;
}

void reshape(int width, int height)
{
	float aspect = (float) width / (float) height;
	WINDOW_SIZE.x = width;
	WINDOW_SIZE.y = height;
	WINDOW_CENTER.x = width / 2;
	WINDOW_CENTER.y = height / 2;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, aspect, ZNEAR, ZFAR);
}


/*---------------------------------------------------------*/
/*------------------- DRAWING FUNCTIONS -------------------*/
/*---------------------------------------------------------*/
void draw_grid(int n)
{
	int i;

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for(i = -n;i < n;i++){
		float d = (float) i;
		// Parallel to x-axis 
		glVertex3f(-n, 0.0f, d);
		glVertex3f(n, 0.0f, d);
		// Parallel to z-axis
		glVertex3f(d, 0.0f, -n);
		glVertex3f(d, 0.0f, n);
	}
	glEnd();
}


/*--------------------------------------------------------*/
/*-------------------- MATH FUNCTIONS --------------------*/
/*--------------------------------------------------------*/
Vec3 forward(Transform* t) {
	Vec3 v;
	float a = t->rotation.x * DEG2RAD * 2;
	float b = t->rotation.y * DEG2RAD * 2;
	float c = t->rotation.z * DEG2RAD * 2;

	// Euler angles?
	v.x = -(sin(c) * sin(a) + cos(c) * sin(b) * cos(a));
	v.y = (-cos(c) * sin(a) + sin(c) * sin(b) * cos(a));
	v.z = -(cos(b) * cos(a));

	return v;
}

Vec3 up(Transform* t) {
	Vec3 v;
	float a = t->rotation.x * DEG2RAD * 2;
	float b = t->rotation.y * DEG2RAD * 2;
	float c = t->rotation.z * DEG2RAD * 2;

	// More euler angles?
	v.x = -sin(c) * cos(a) + cos(c) * sin(b) * sin(a);
	v.y = cos(c) * cos(a) + sin(c) * sin(b) * sin(a);
	v.z = cos(b) * sin(a);
	
	return v;
}

Vec3 right(Transform* t) {
	Vec3 v;
	float a = t->rotation.x * DEG2RAD * 2;
	float b = t->rotation.y * DEG2RAD * 2;
	float c = t->rotation.z * DEG2RAD * 2;

	v.x = cos(c) * cos(b);
	v.y = sin(c) * cos(b);
	v.z = -sin(b);

	return v;
}

/*
Porta Principal: 
X 1.4266
Y 8.3678
Z 2.736
Porta Janela:
X -1.6858
Y -6.401
Z 2.7345
Janelas:
X -1.6813
Y -6.4363
Z 2.9417
*/