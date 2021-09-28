/*-------------------------------------------*/
/*------------ STANDARD INCLUDES ------------*/
/*-------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "utilities.h"


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

// Object 1
ObjectMesh AIR_CONDITIONER;

// Object 2
int main_door_angle = 0;
int open_main_door = -1;
ObjectMesh DOOR;

// Object 3
int side_door_angle = 0;
int open_side_door = -1;
ObjectMesh SECONDARY_DOOR;

// Object 4
ObjectMesh BUNKBED;

// Object 5
int open_windows = -1;
int window_angle = 0;
ObjectMesh LEFT_WINDOW;

// Object 6
ObjectMesh RIGHT_WINDOW;

// Object 7
ObjectMesh TABLE;

// Object 8
ObjectMesh BED;

// Object 9
ObjectMesh CREEPER;

// Object 10
ObjectMesh WARDROBE;

// Object 11
ObjectMesh MONITOR1;

// Object 12
ObjectMesh MONITOR2;

// Object 13
ObjectMesh MOUSE;

// Object 14
ObjectMesh MOUSEPAD;

// Object 15
ObjectMesh PC;

// Object 16
ObjectMesh SHELF;

// Object 17
ObjectMesh ROOM;

// Object 18
ObjectMesh KEYBOARD_OBJ;

// Object 19
ObjectMesh TNT;

// Object 20
int fan_speed = 3;
ObjectMesh FAN;

// Object 21
ObjectMesh TABLE_LAMP;

// Object 22
ObjectMesh PAINTING;

// Object 23
ObjectMesh FAN_BASE;

// Object 24
ObjectMesh CHAIR;


/*---------------------------------------------*/
/*-------------- SETUP FUNCTIONS --------------*/
/*---------------------------------------------*/
void init_gl();
void setup_lighting();
int load_all_objects();
unsigned int load_texture(const char* path);
void load_all_textures();


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
void main_door();
void side_door();
void windows();
void move_fan();


/*--------------------------------------------*/
/*-------------- MATH FUNCTIONS --------------*/
/*--------------------------------------------*/
Vec3 forward(Transform* t);
Vec3 right(Transform* t);
Vec3 up(Transform* t);


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

    // Setting initial camera position outside the room and facing the main door
    CAM.position = (Vec3) {2.0f, 4.0f, -15.0f};
    CAM.rotation = (Vec3) {0.0f, 90.0f, 0.0f};

    // Loading the object files
    load_all_objects();

	load_all_textures();

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
    glEnable(GL_TEXTURE_2D);
    // setup_lighting();
}

void setup_lighting()
{
    float mat_shininess[] = {80.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    float light_diffuse[] = {1.0f, 1.0f, 1.0f};
    float light_position[] = {2.0f, 4.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    float light_specular[] = {0.0f, 1.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    float light_spot_direction[] = {1.0f, 0.0f, 0.0f};
    float light_spot_diffuse[] = {1.0f, 0.0f, 1.0f};
    float light_spot_position[] = {-1.3f, 4.342580f, -0.310794f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light_spot_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_spot_diffuse);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_direction);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

int load_all_objects()
{
    ObjectMesh *ptr = &AIR_CONDITIONER;
    if(!load_obj("objects/Ar.obj", ptr))
    {
        perror("Erro ao abrir o arquivo 'Ar'!");
        return -1;
    }
    ptr = &DOOR;
    if(!load_obj("objects/portaPrincipal.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &SECONDARY_DOOR;
    if(!load_obj("objects/portaSecundaria.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &BUNKBED;
    if(!load_obj("objects/beliche.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &LEFT_WINDOW;
    if(!load_obj("objects/Janela1.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &RIGHT_WINDOW;
    if(!load_obj("objects/Janela2.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &TABLE;
    if(!load_obj("objects/biro.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &BED;
    if(!load_obj("objects/Cama.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &CREEPER;
    if(!load_obj("objects/creeper.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &WARDROBE;
    if(!load_obj("objects/GuardaRoupa.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &MONITOR1;
    if(!load_obj("objects/Monitor1.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &MONITOR2;
    if(!load_obj("objects/Monitor2.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &MOUSE;
    if(!load_obj("objects/mouse.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &MOUSEPAD;
    if(!load_obj("objects/mousepad.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &PC;
    if(!load_obj("objects/PC.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &SHELF;
    if(!load_obj("objects/prateleira.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &ROOM;
    if(!load_obj("objects/Quarto.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &KEYBOARD_OBJ;
    if(!load_obj("objects/teclado.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &TNT;
    if(!load_obj("objects/tnt.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &FAN;
    if(!load_obj("objects/ventilador.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &TABLE_LAMP;
    if(!load_obj("objects/luminaria.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &PAINTING;
    if(!load_obj("objects/Quadro.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &FAN_BASE;
    if(!load_obj("objects/ventiladorBase.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    ptr = &CHAIR;
    if(!load_obj("objects/cadeira.obj", ptr))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
}

void load_all_textures()
{
    AIR_CONDITIONER.tex_id = load_texture("textures/ArFront.jpg");
	DOOR.tex_id = load_texture("textures/portas.jpg");
    LEFT_WINDOW.tex_id = load_texture("textures/janela.jpg");
    TABLE.tex_id = load_texture("textures/biro.jpg");
    CREEPER.tex_id = load_texture("textures/creeper.png");
    WARDROBE.tex_id = load_texture("textures/armario.jpg");
    MONITOR1.tex_id = load_texture("textures/Tela1.png");
    MONITOR2.tex_id = load_texture("textures/Tela2.png");
    MOUSEPAD.tex_id = load_texture("textures/mousepad.png");
    PC.tex_id = load_texture("textures/PC.png");
    SHELF.tex_id = load_texture("textures/prateleira.jpg");
    TNT.tex_id = load_texture("textures/tnt.png");
    PAINTING.tex_id = load_texture("textures/NoiteEstrelada2.jpg");
    FAN_BASE.tex_id = load_texture("textures/preto.jpg");
    CHAIR.tex_id = load_texture("textures/AssentoCadeira.jpeg");
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
    setup_lighting();

    draw_grid(25);

    int i;
    // Draw the air conditioner
    glBindTexture(GL_TEXTURE_2D, AIR_CONDITIONER.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < AIR_CONDITIONER.VERTEX_COUNT; i++)
    {
        glNormal3f(AIR_CONDITIONER.NORMALS[i].x, AIR_CONDITIONER.NORMALS[i].y, AIR_CONDITIONER.NORMALS[i].z);
        glTexCoord2f(AIR_CONDITIONER.TEX_COORDS[i].x, AIR_CONDITIONER.TEX_COORDS[i].y);
        glVertex3f(AIR_CONDITIONER.VERTICES[i].x, AIR_CONDITIONER.VERTICES[i].y, AIR_CONDITIONER.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the main door
    glBindTexture(GL_TEXTURE_2D, DOOR.tex_id);
    glPushMatrix();
    glTranslatef(-0.192099, -0.052135, -8.332047);
    glRotatef(main_door_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.192099, 0.052135, 8.332047);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < DOOR.VERTEX_COUNT; i++)
    {
        glNormal3f(DOOR.NORMALS[i].x, DOOR.NORMALS[i].y, DOOR.NORMALS[i].z);
        glTexCoord2f(DOOR.TEX_COORDS[i].x, DOOR.TEX_COORDS[i].y);
        glVertex3f(DOOR.VERTICES[i].x, DOOR.VERTICES[i].y, DOOR.VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();

    // Draw the side door
    glPushMatrix();
    glTranslatef(-1.743257, -0.122533, 7.634487);
    glRotatef(side_door_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.743257, 0.122533, -7.634487);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < SECONDARY_DOOR.VERTEX_COUNT; i++)
    {
        glNormal3f(SECONDARY_DOOR.NORMALS[i].x, SECONDARY_DOOR.NORMALS[i].y, SECONDARY_DOOR.NORMALS[i].z);
        glTexCoord2f(SECONDARY_DOOR.TEX_COORDS[i].x, SECONDARY_DOOR.TEX_COORDS[i].y);
        glVertex3f(SECONDARY_DOOR.VERTICES[i].x, SECONDARY_DOOR.VERTICES[i].y, SECONDARY_DOOR.VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the bunkbed
    glBegin(GL_TRIANGLES);
    for(i = 0; i < BUNKBED.VERTEX_COUNT; i++)
    {
        glNormal3f(BUNKBED.NORMALS[i].x, BUNKBED.NORMALS[i].y, BUNKBED.NORMALS[i].z);
        glTexCoord2f(BUNKBED.TEX_COORDS[i].x, BUNKBED.TEX_COORDS[i].y);
        glVertex3f(BUNKBED.VERTICES[i].x, BUNKBED.VERTICES[i].y, BUNKBED.VERTICES[i].z);
    }
    glEnd();


    // Draw the left window
    glBindTexture(GL_TEXTURE_2D, LEFT_WINDOW.tex_id);
    glPushMatrix();
    glTranslatef(14.902783, 3.648618, -1.792326);
    glRotatef(window_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-14.902783, -3.648618, 1.792326);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < LEFT_WINDOW.VERTEX_COUNT; i++)
    {
        glNormal3f(LEFT_WINDOW.NORMALS[i].x, LEFT_WINDOW.NORMALS[i].y, LEFT_WINDOW.NORMALS[i].z);
        glTexCoord2f(LEFT_WINDOW.TEX_COORDS[i].x, LEFT_WINDOW.TEX_COORDS[i].y);
        glVertex3f(LEFT_WINDOW.VERTICES[i].x, LEFT_WINDOW.VERTICES[i].y, LEFT_WINDOW.VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();

    // Draw the right window
    glPushMatrix();
    glTranslatef(14.903056, 3.648618, 3.201038);
    glRotatef(-window_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-14.903056, -3.648618, -3.201038);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < RIGHT_WINDOW.VERTEX_COUNT; i++)
    {
        glNormal3f(RIGHT_WINDOW.NORMALS[i].x, RIGHT_WINDOW.NORMALS[i].y, RIGHT_WINDOW.NORMALS[i].z);
        glTexCoord2f(RIGHT_WINDOW.TEX_COORDS[i].x, RIGHT_WINDOW.TEX_COORDS[i].y);
        glVertex3f(RIGHT_WINDOW.VERTICES[i].x, RIGHT_WINDOW.VERTICES[i].y, RIGHT_WINDOW.VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the table
    glBindTexture(GL_TEXTURE_2D, TABLE.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < TABLE.VERTEX_COUNT; i++)
    {
        glNormal3f(TABLE.NORMALS[i].x, TABLE.NORMALS[i].y, TABLE.NORMALS[i].z);
        glTexCoord2f(TABLE.TEX_COORDS[i].x, TABLE.TEX_COORDS[i].y);
        glVertex3f(TABLE.VERTICES[i].x, TABLE.VERTICES[i].y, TABLE.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the bed
    glBegin(GL_TRIANGLES);
    for(i = 0; i < BED.VERTEX_COUNT; i++)
    {
        glNormal3f(BED.NORMALS[i].x, BED.NORMALS[i].y, BED.NORMALS[i].z);
        glTexCoord2f(BED.TEX_COORDS[i].x, BED.TEX_COORDS[i].y);
        glVertex3f(BED.VERTICES[i].x, BED.VERTICES[i].y, BED.VERTICES[i].z);
    }
    glEnd();
    
    // Draw the creeper
    glBindTexture(GL_TEXTURE_2D, CREEPER.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < CREEPER.VERTEX_COUNT; i++)
    {
        glNormal3f(CREEPER.NORMALS[i].x, CREEPER.NORMALS[i].y, CREEPER.NORMALS[i].z);
        glTexCoord2f(CREEPER.TEX_COORDS[i].x, CREEPER.TEX_COORDS[i].y);
        glVertex3f(CREEPER.VERTICES[i].x, CREEPER.VERTICES[i].y, CREEPER.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the wardrobe
    glBindTexture(GL_TEXTURE_2D, WARDROBE.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < WARDROBE.VERTEX_COUNT; i++)
    {
        glNormal3f(WARDROBE.NORMALS[i].x, WARDROBE.NORMALS[i].y, WARDROBE.NORMALS[i].z);
        glTexCoord2f(WARDROBE.TEX_COORDS[i].x, WARDROBE.TEX_COORDS[i].y);
        glVertex3f(WARDROBE.VERTICES[i].x, WARDROBE.VERTICES[i].y, WARDROBE.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the monitor 1
    glBindTexture(GL_TEXTURE_2D, MONITOR1.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MONITOR1.VERTEX_COUNT; i++)
    {
        glNormal3f(MONITOR1.NORMALS[i].x, MONITOR1.NORMALS[i].y, MONITOR1.NORMALS[i].z);
        glTexCoord2f(MONITOR1.TEX_COORDS[i].x, MONITOR1.TEX_COORDS[i].y);
        glVertex3f(MONITOR1.VERTICES[i].x, MONITOR1.VERTICES[i].y, MONITOR1.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the monitor 2
    glBindTexture(GL_TEXTURE_2D, MONITOR2.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MONITOR2.VERTEX_COUNT; i++)
    {
        glNormal3f(MONITOR2.NORMALS[i].x, MONITOR2.NORMALS[i].y, MONITOR2.NORMALS[i].z);
        glTexCoord2f(MONITOR2.TEX_COORDS[i].x, MONITOR2.TEX_COORDS[i].y);
        glVertex3f(MONITOR2.VERTICES[i].x, MONITOR2.VERTICES[i].y, MONITOR2.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the mouse
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MOUSE.VERTEX_COUNT; i++)
    {
        glNormal3f(MOUSE.NORMALS[i].x, MOUSE.NORMALS[i].y, MOUSE.NORMALS[i].z);
        glTexCoord2f(MOUSE.TEX_COORDS[i].x, MOUSE.TEX_COORDS[i].y);
        glVertex3f(MOUSE.VERTICES[i].x, MOUSE.VERTICES[i].y, MOUSE.VERTICES[i].z);
    }
    glEnd();

    // Draw the mousepad
    glBindTexture(GL_TEXTURE_2D, MOUSEPAD.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MOUSEPAD.VERTEX_COUNT; i++)
    {
        glNormal3f(MOUSEPAD.NORMALS[i].x, MOUSEPAD.NORMALS[i].y, MOUSEPAD.NORMALS[i].z);
        glTexCoord2f(MOUSEPAD.TEX_COORDS[i].x, MOUSEPAD.TEX_COORDS[i].y);
        glVertex3f(MOUSEPAD.VERTICES[i].x, MOUSEPAD.VERTICES[i].y, MOUSEPAD.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the PC
    glBindTexture(GL_TEXTURE_2D, PC.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < PC.VERTEX_COUNT; i++)
    {
        glNormal3f(PC.NORMALS[i].x, PC.NORMALS[i].y, PC.NORMALS[i].z);
        glTexCoord2f(PC.TEX_COORDS[i].x, PC.TEX_COORDS[i].y);
        glVertex3f(PC.VERTICES[i].x, PC.VERTICES[i].y, PC.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the shelf
    glBindTexture(GL_TEXTURE_2D, SHELF.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < SHELF.VERTEX_COUNT; i++)
    {
        glNormal3f(SHELF.NORMALS[i].x, SHELF.NORMALS[i].y, SHELF.NORMALS[i].z);
        glTexCoord2f(SHELF.TEX_COORDS[i].x, SHELF.TEX_COORDS[i].y);
        glVertex3f(SHELF.VERTICES[i].x, SHELF.VERTICES[i].y, SHELF.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the room
    glBegin(GL_TRIANGLES);
    for(i = 0; i < ROOM.VERTEX_COUNT; i++)
    {
        glNormal3f(ROOM.NORMALS[i].x, ROOM.NORMALS[i].y, ROOM.NORMALS[i].z);
        glTexCoord2f(ROOM.TEX_COORDS[i].x, ROOM.TEX_COORDS[i].y);
        glVertex3f(ROOM.VERTICES[i].x, ROOM.VERTICES[i].y, ROOM.VERTICES[i].z);
    }
    glEnd();
    
    // Draw the keyboard
    glBegin(GL_TRIANGLES);
    for(i = 0; i < KEYBOARD_OBJ.VERTEX_COUNT; i++)
    {
        glNormal3f(KEYBOARD_OBJ.NORMALS[i].x, KEYBOARD_OBJ.NORMALS[i].y, KEYBOARD_OBJ.NORMALS[i].z);
        glTexCoord2f(KEYBOARD_OBJ.TEX_COORDS[i].x, KEYBOARD_OBJ.TEX_COORDS[i].y);
        glVertex3f(KEYBOARD_OBJ.VERTICES[i].x, KEYBOARD_OBJ.VERTICES[i].y, KEYBOARD_OBJ.VERTICES[i].z);
    }
    glEnd();
    
    // Draw the tnt
    glBindTexture(GL_TEXTURE_2D, TNT.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < TNT.VERTEX_COUNT; i++)
    {
        glNormal3f(TNT.NORMALS[i].x, TNT.NORMALS[i].y, TNT.NORMALS[i].z);
        glTexCoord2f(TNT.TEX_COORDS[i].x, TNT.TEX_COORDS[i].y);
        glVertex3f(TNT.VERTICES[i].x, TNT.VERTICES[i].y, TNT.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the fan
    glPushMatrix();
    glTranslatef(1.220647, 2.604736, 2.619632);
    glRotatef(-40, 0.0f, 1.0f, 0.0f);
    glRotatef(fan_speed, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.220647, -2.604736, -2.619632);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < FAN.VERTEX_COUNT; i++)
    {
        glNormal3f(FAN.NORMALS[i].x, FAN.NORMALS[i].y, FAN.NORMALS[i].z);
        glTexCoord2f(FAN.TEX_COORDS[i].x, FAN.TEX_COORDS[i].y);
        glVertex3f(FAN.VERTICES[i].x, FAN.VERTICES[i].y, FAN.VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();

    // Draw the fan base
    glBindTexture(GL_TEXTURE_2D, FAN_BASE.tex_id);
    glPushMatrix();
    glTranslatef(1.220647, 2.604736, 2.619632);
    glRotatef(-40, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.220647, -2.604736, -2.619632);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < FAN_BASE.VERTEX_COUNT; i++)
    {
        glNormal3f(FAN_BASE.NORMALS[i].x, FAN_BASE.NORMALS[i].y, FAN_BASE.NORMALS[i].z);
        glTexCoord2f(FAN_BASE.TEX_COORDS[i].x, FAN_BASE.TEX_COORDS[i].y);
        glVertex3f(FAN_BASE.VERTICES[i].x, FAN_BASE.VERTICES[i].y, FAN_BASE.VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the table lamp
    glBegin(GL_TRIANGLES);
    for(i = 0; i < TABLE_LAMP.VERTEX_COUNT; i++)
    {
        glNormal3f(TABLE_LAMP.NORMALS[i].x, TABLE_LAMP.NORMALS[i].y, TABLE_LAMP.NORMALS[i].z);
        glTexCoord2f(TABLE_LAMP.TEX_COORDS[i].x, TABLE_LAMP.TEX_COORDS[i].y);
        glVertex3f(TABLE_LAMP.VERTICES[i].x, TABLE_LAMP.VERTICES[i].y, TABLE_LAMP.VERTICES[i].z);
    }
    glEnd();

    // Draw the paiting
    glBindTexture(GL_TEXTURE_2D, PAINTING.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < PAINTING.VERTEX_COUNT; i++)
    {
        glNormal3f(PAINTING.NORMALS[i].x, PAINTING.NORMALS[i].y, PAINTING.NORMALS[i].z);
        glTexCoord2f(PAINTING.TEX_COORDS[i].x, PAINTING.TEX_COORDS[i].y);
        glVertex3f(PAINTING.VERTICES[i].x, PAINTING.VERTICES[i].y, PAINTING.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the chair
    glBindTexture(GL_TEXTURE_2D, CHAIR.tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < CHAIR.VERTEX_COUNT; i++)
    {
        glNormal3f(CHAIR.NORMALS[i].x, CHAIR.NORMALS[i].y, CHAIR.NORMALS[i].z);
        glTexCoord2f(CHAIR.TEX_COORDS[i].x, CHAIR.TEX_COORDS[i].y);
        glVertex3f(CHAIR.VERTICES[i].x, CHAIR.VERTICES[i].y, CHAIR.VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glutSwapBuffers();
}

void idle()
{
    // Forward movement
    int move_forward = KEYBOARD['w'] - KEYBOARD['s'];
    Vec3 fwd = forward(&CAM);

    fwd.x *= KEYBOARD['c'] ? move_forward * 2 : move_forward;
    fwd.y = 0.0f; // Projects fwd in the xz plane
    fwd.z *= KEYBOARD['c'] ? move_forward * 2 : move_forward;

    main_door();
    side_door();
    windows();
    move_fan();

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

    if(tolower(key) == '1' || tolower(key) == 'e')
        open_main_door *= -1;
    if(tolower(key) == '2')
        open_side_door *= -1;
    if(tolower(key) == '3')
        open_windows *= -1;
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

void main_door()
{
    if(open_main_door == 1)
    {
        if(main_door_angle > -110)
            main_door_angle -= 3;
        else
            main_door_angle = -110;
    }
    else if(open_main_door == -1)
    {
        if(main_door_angle < 0)
            main_door_angle += 3;
        else
            main_door_angle = 0;
    }
}

void side_door()
{
    if(open_side_door == 1)
    {
        if(side_door_angle > -95)
            side_door_angle -= 3;
        else
            side_door_angle = -95;
    }
    else if(open_side_door == -1)
    {
        if(side_door_angle < 0)
            side_door_angle += 3;
        else
            side_door_angle = 0;
    }
}

void windows()
{
    if(open_windows == 1)
    {
        if(window_angle > -145)
            window_angle -= 3;
        else
            window_angle = -145;
    }
    else
    {
        if(window_angle < 0)
            window_angle += 3;
        else
            window_angle = 0;
    }
}

void move_fan()
{
    if(fan_speed > 360)
        fan_speed = 0;
    
    fan_speed += 3;
}


/*--------------------------------------------------------*/
/*-------------------- MATH FUNCTIONS --------------------*/
/*--------------------------------------------------------*/
Vec3 forward(Transform* t) {
    Vec3 v;
    float a = t->rotation.x * DEG2RAD * 2;
    float b = t->rotation.y * DEG2RAD * 2;
    float c = t->rotation.z * DEG2RAD * 2;

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

    v.x = -sin(c) * cos(a) + cos(c) * sin(b) * sin(a);
    v.y = cos(c) * cos(a) + sin(c) * sin(b) * sin(a);
    v.z = cos(b) * sin(a);

    return v;
}

Vec3 right(Transform* t) {
    Vec3 v;
    float b = t->rotation.y * DEG2RAD * 2;
    float c = t->rotation.z * DEG2RAD * 2;

    v.x = cos(c) * cos(b);
    v.y = sin(c) * cos(b);
    v.z = -sin(b);

    return v;
}
