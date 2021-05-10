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
} Transform;


/*-----------------------------------------*/
/*--------------- CONSTANTS ---------------*/
/*-----------------------------------------*/
const float DEG2RAD = 3.14159265 / 180.0f;


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

// Object 1
unsigned int air_conditioner_tex_id;
int AIR_CONDITIONER_VERTEX_COUNT;
Vec3 AIR_CONDITIONER_VERTICES[MAX_VERTICES];
Vec3 AIR_CONDITIONER_NORMALS[MAX_VERTICES];
Vec2 AIR_CONDITIONER_TEX_COORDS[MAX_VERTICES];

// Object 2
unsigned int doors_tex_id;
int main_door_angle = 0;
int open_main_door = -1;
int DOOR_VERTEX_COUNT;
Vec3 DOOR_VERTICES[MAX_VERTICES];
Vec3 DOOR_NORMALS[MAX_VERTICES];
Vec2 DOOR_TEX_COORDS[MAX_VERTICES];

// Object 3
int side_door_angle = 0;
int open_side_door = -1;
int SECONDARY_DOOR_VERTEX_COUNT;
Vec3 SECONDARY_DOOR_VERTICES[MAX_VERTICES];
Vec3 SECONDARY_DOOR_NORMALS[MAX_VERTICES];
Vec2 SECONDARY_DOOR_TEX_COORDS[MAX_VERTICES];

// Object 4
int BUNKBED_VERTEX_COUNT;
Vec3 BUNKBED_VERTICES[MAX_VERTICES];
Vec3 BEUNKBED_NORMALS[MAX_VERTICES];
Vec2 BUNKBED_TEX_COORDS[MAX_VERTICES];

// Object 5
unsigned int windows_tex_id;
int open_windows = -1;
int window_angle = 0;
int LEFT_WINDOW_VERTEX_COUNT;
Vec3 LEFT_WINDOW_VERTICES[MAX_VERTICES];
Vec3 LEFT_WINDOW_NORMALS[MAX_VERTICES];
Vec2 LEFT_WINDOW_TEX_COORDS[MAX_VERTICES];

// Object 6
int RIGHT_WINDOW_VERTEX_COUNT;
Vec3 RIGHT_WINDOW_VERTICES[MAX_VERTICES];
Vec3 RIGHT_WINDOW_NORMALS[MAX_VERTICES];
Vec2 RIGHT_WINDOW_TEX_COORDS[MAX_VERTICES];

// Object 7
unsigned int table_tex_id;
int TABLE_VERTEX_COUNT;
Vec3 TABLE_VERTICES[MAX_VERTICES];
Vec3 TABLE_NORMALS[MAX_VERTICES];
Vec2 TABLE_TEX_COORDS[MAX_VERTICES];

// Object 8
int BED_VERTEX_COUNT;
Vec3 BED_VERTICES[MAX_VERTICES];
Vec3 BED_NORMALS[MAX_VERTICES];
Vec2 BED_TEX_COORDS[MAX_VERTICES];

// Object 9
unsigned int creeper_tex_id;
int CREEPER_VERTEX_COUNT;
Vec3 CREEPER_VERTICES[MAX_VERTICES];
Vec3 CREEPER_NORMALS[MAX_VERTICES];
Vec2 CREEPER_TEX_COORDS[MAX_VERTICES];

// Object 10
unsigned int wardrobe_tex_id;
int WARDROBE_VERTEX_COUNT;
Vec3 WARDROBE_VERTICES[MAX_VERTICES];
Vec3 WARDROBE_NORMALS[MAX_VERTICES];
Vec2 WARDROBE_TEX_COORDS[MAX_VERTICES];

// Object 11
unsigned int monitor1_tex_id;
int MONITOR1_VERTEX_COUNT;
Vec3 MONITOR1_VERTICES[MAX_VERTICES];
Vec3 MONITOR1_NORMALS[MAX_VERTICES];
Vec2 MONITOR1_TEX_COORDS[MAX_VERTICES];

// Object 12
unsigned int monitor2_tex_id;
int MONITOR2_VERTEX_COUNT;
Vec3 MONITOR2_VERTICES[MAX_VERTICES];
Vec3 MONITOR2_NORMALS[MAX_VERTICES];
Vec2 MONITOR2_TEX_COORDS[MAX_VERTICES];

// Object 13
int MOUSE_VERTEX_COUNT;
Vec3 MOUSE_VERTICES[MAX_VERTICES];
Vec3 MOUSE_NORMALS[MAX_VERTICES];
Vec2 MOUSE_TEX_COORDS[MAX_VERTICES];

// Object 14
unsigned int mousepad_tex_id;
int MOUSEPAD_VERTEX_COUNT;
Vec3 MOUSEPAD_VERTICES[MAX_VERTICES];
Vec3 MOUSEPAD_NORMALS[MAX_VERTICES];
Vec2 MOUSEPAD_TEX_COORDS[MAX_VERTICES];

// Object 15
unsigned int pc_tex_id;
int PC_VERTEX_COUNT;
Vec3 PC_VERTICES[MAX_VERTICES];
Vec3 PC_NORMALS[MAX_VERTICES];
Vec2 PC_TEX_COORDS[MAX_VERTICES];

// Object 16
unsigned int shelf_tex_id;
int SHELF_VERTEX_COUNT;
Vec3 SHELF_VERTICES[MAX_VERTICES];
Vec3 SHELF_NORMALS[MAX_VERTICES];
Vec2 SHELF_TEX_COORDS[MAX_VERTICES];

// Object 17
int ROOM_VERTEX_COUNT;
Vec3 ROOM_VERTICES[MAX_VERTICES];
Vec3 ROOM_NORMALS[MAX_VERTICES];
Vec2 ROOM_TEX_COORDS[MAX_VERTICES];

// Object 18
int KEYBOARD_VERTEX_COUNT;
Vec3 KEYBOARD_VERTICES[MAX_VERTICES];
Vec3 KEYBOARD_NORMALS[MAX_VERTICES];
Vec2 KEYBOARD_TEX_COORDS[MAX_VERTICES];

// Object 19
unsigned int tnt_tex_id;
int TNT_VERTEX_COUNT;
Vec3 TNT_VERTICES[MAX_VERTICES];
Vec3 TNT_NORMALS[MAX_VERTICES];
Vec2 TNT_TEX_COORDS[MAX_VERTICES];

// Object 20
int fan_speed = 3;
int FAN_VERTEX_COUNT;
Vec3 FAN_VERTICES[MAX_VERTICES];
Vec3 FAN_NORMALS[MAX_VERTICES];
Vec2 FAN_TEX_COORDS[MAX_VERTICES];

// Object 21
int TABLE_LAMP_VERTEX_COUNT;
Vec3 TABLE_LAMP_VERTICES[MAX_VERTICES];
Vec3 TABLE_LAMP_NORMALS[MAX_VERTICES];
Vec2 TABLE_LAMP_TEX_COORDS[MAX_VERTICES];

// Object 22
unsigned int painting_tex_id;
int PAINTING_VERTEX_COUNT;
Vec3 PAINTING_VERTICES[MAX_VERTICES];
Vec3 PAINTING_NORMALS[MAX_VERTICES];
Vec2 PAINTING_TEX_COORDS[MAX_VERTICES];

// Object 23
unsigned int fan_base_tex_id;
int FAN_BASE_VERTEX_COUNT;
Vec3 FAN_BASE_VERTICES[MAX_VERTICES];
Vec3 FAN_BASE_NORMALS[MAX_VERTICES];
Vec2 FAN_BASE_TEX_COORDS[MAX_VERTICES];

// Object 24
unsigned int chair_tex_id;
int CHAIR_VERTEX_COUNT;
Vec3 CHAIR_VERTICES[MAX_VERTICES];
Vec3 CHAIR_NORMALS[MAX_VERTICES];
Vec2 CHAIR_TEX_COORDS[MAX_VERTICES];


/*---------------------------------------------*/
/*-------------- SETUP FUNCTIONS --------------*/
/*---------------------------------------------*/
void init_gl();
void setup_lighting();
int load_obj(const char* path, int object);
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
                    AIR_CONDITIONER_VERTICES[AIR_CONDITIONER_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    AIR_CONDITIONER_TEX_COORDS[AIR_CONDITIONER_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    AIR_CONDITIONER_NORMALS[AIR_CONDITIONER_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    AIR_CONDITIONER_VERTEX_COUNT++;
                }
                else if(object == 2) // Main door
                {
                    DOOR_VERTICES[DOOR_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    DOOR_TEX_COORDS[DOOR_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    DOOR_NORMALS[DOOR_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    DOOR_VERTEX_COUNT++;
                }
                else if(object == 3) // Secondary door
                {
                    SECONDARY_DOOR_VERTICES[SECONDARY_DOOR_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    SECONDARY_DOOR_TEX_COORDS[SECONDARY_DOOR_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    SECONDARY_DOOR_NORMALS[SECONDARY_DOOR_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    SECONDARY_DOOR_VERTEX_COUNT++;
                }
                else if(object == 4) // Door window
                {
                    BUNKBED_VERTICES[BUNKBED_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    BUNKBED_TEX_COORDS[BUNKBED_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    BEUNKBED_NORMALS[BUNKBED_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    BUNKBED_VERTEX_COUNT++;
                }
                else if(object == 5) // Left window
                {
                    LEFT_WINDOW_VERTICES[LEFT_WINDOW_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    LEFT_WINDOW_TEX_COORDS[LEFT_WINDOW_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    LEFT_WINDOW_NORMALS[LEFT_WINDOW_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    LEFT_WINDOW_VERTEX_COUNT++;
                }
                else if(object == 6) // Right window
                {
                    RIGHT_WINDOW_VERTICES[RIGHT_WINDOW_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    RIGHT_WINDOW_TEX_COORDS[RIGHT_WINDOW_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    RIGHT_WINDOW_NORMALS[RIGHT_WINDOW_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    RIGHT_WINDOW_VERTEX_COUNT++;
                }
                else if(object == 7) // Table
                {
                    TABLE_VERTICES[TABLE_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    TABLE_TEX_COORDS[TABLE_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    TABLE_NORMALS[TABLE_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    TABLE_VERTEX_COUNT++;
                }
                else if(object == 8) // Bed
                {
                    BED_VERTICES[BED_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    BED_TEX_COORDS[BED_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    BED_NORMALS[BED_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    BED_VERTEX_COUNT++;
                }
                else if(object == 9) // Creeper
                {
                    CREEPER_VERTICES[CREEPER_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    CREEPER_TEX_COORDS[CREEPER_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    CREEPER_NORMALS[CREEPER_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    CREEPER_VERTEX_COUNT++;
                }
                else if(object == 10) // Wardrobe
                {
                    WARDROBE_VERTICES[WARDROBE_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    WARDROBE_TEX_COORDS[WARDROBE_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    WARDROBE_NORMALS[WARDROBE_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    WARDROBE_VERTEX_COUNT++;
                }
                else if(object == 11) // Monitor 1
                {
                    MONITOR1_VERTICES[MONITOR1_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    MONITOR1_TEX_COORDS[MONITOR1_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    MONITOR1_NORMALS[MONITOR1_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    MONITOR1_VERTEX_COUNT++;
                }
                else if(object == 12) // Monitor 2
                {
                    MONITOR2_VERTICES[MONITOR2_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    MONITOR2_TEX_COORDS[MONITOR2_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    MONITOR2_NORMALS[MONITOR2_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    MONITOR2_VERTEX_COUNT++;
                }
                else if(object == 13) // Mouse
                {
                    MOUSE_VERTICES[MOUSE_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    MOUSE_TEX_COORDS[MOUSE_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    MOUSE_NORMALS[MOUSE_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    MOUSE_VERTEX_COUNT++;
                }
                else if(object == 14) // Mousepad
                {
                    MOUSEPAD_VERTICES[MOUSEPAD_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    MOUSEPAD_TEX_COORDS[MOUSEPAD_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    MOUSEPAD_NORMALS[MOUSEPAD_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    MOUSEPAD_VERTEX_COUNT++;
                }
                else if(object == 15) // PC
                {
                    PC_VERTICES[PC_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    PC_TEX_COORDS[PC_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    PC_NORMALS[PC_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    PC_VERTEX_COUNT++;
                }
                else if(object == 16) // Shelf
                {
                    SHELF_VERTICES[SHELF_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    SHELF_TEX_COORDS[SHELF_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    SHELF_NORMALS[SHELF_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    SHELF_VERTEX_COUNT++;
                }
                else if(object == 17) // Room
                {
                    ROOM_VERTICES[ROOM_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    ROOM_TEX_COORDS[ROOM_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    ROOM_NORMALS[ROOM_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    ROOM_VERTEX_COUNT++;
                }
                else if(object == 18) // Keyboard
                {
                    KEYBOARD_VERTICES[KEYBOARD_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    KEYBOARD_TEX_COORDS[KEYBOARD_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    KEYBOARD_NORMALS[KEYBOARD_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    KEYBOARD_VERTEX_COUNT++;
                }
                else if(object == 19) // TNT
                {
                    TNT_VERTICES[TNT_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    TNT_TEX_COORDS[TNT_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    TNT_NORMALS[TNT_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    TNT_VERTEX_COUNT++;
                }
                else if(object == 20) // Fan
                {
                    FAN_VERTICES[FAN_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    FAN_TEX_COORDS[FAN_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    FAN_NORMALS[FAN_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    FAN_VERTEX_COUNT++;
                }
                else if(object == 21) // Table lamp
                {
                    TABLE_LAMP_VERTICES[TABLE_LAMP_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    TABLE_LAMP_TEX_COORDS[TABLE_LAMP_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    TABLE_LAMP_NORMALS[TABLE_LAMP_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    TABLE_LAMP_VERTEX_COUNT++;
                }
                else if(object == 22) // Painting
                {
                    PAINTING_VERTICES[PAINTING_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    PAINTING_TEX_COORDS[PAINTING_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    PAINTING_NORMALS[PAINTING_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    PAINTING_VERTEX_COUNT++;
                }
                else if(object == 23) // Fan base
                {
                    FAN_BASE_VERTICES[FAN_BASE_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    FAN_BASE_TEX_COORDS[FAN_BASE_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    FAN_BASE_NORMALS[FAN_BASE_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    FAN_BASE_VERTEX_COUNT++;
                }
                else if(object == 24) // Chair
                {
                    CHAIR_VERTICES[CHAIR_VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                    CHAIR_TEX_COORDS[CHAIR_VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                    CHAIR_NORMALS[CHAIR_VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                    CHAIR_VERTEX_COUNT++;
                }
            }
        }
    }

    fclose(fp);

    return 1;
}

int load_all_objects()
{
    if(!load_obj("objects/Ar.obj", 1))
    {
        perror("Erro ao abrir o arquivo 'Ar'!");
        return -1;
    }
    if(!load_obj("objects/portaPrincipal.obj", 2))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/portaSecundaria.obj", 3))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/beliche.obj", 4))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Janela1.obj", 5))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Janela2.obj", 6))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/biro.obj", 7))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Cama.obj", 8))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/creeper.obj", 9))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/GuardaRoupa.obj", 10))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Monitor1.obj", 11))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Monitor2.obj", 12))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/mouse.obj", 13))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/mousepad.obj", 14))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/PC.obj", 15))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/prateleira.obj", 16))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Quarto.obj", 17))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/teclado.obj", 18))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/tnt.obj", 19))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/ventilador.obj", 20))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/luminaria.obj", 21))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/Quadro.obj", 22))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/ventiladorBase.obj", 23))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    if(!load_obj("objects/cadeira.obj", 24))
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
}

unsigned int load_texture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if(data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        perror("Texture failed to load");
        stbi_image_free(data);
    }
    return textureID;
}

void load_all_textures()
{
    air_conditioner_tex_id = load_texture("textures/ArFront.jpg");
	doors_tex_id = load_texture("textures/portas.jpg");
    windows_tex_id = load_texture("textures/janela.jpg");
    table_tex_id = load_texture("textures/biro.jpg");
    creeper_tex_id = load_texture("textures/creeper.png");
    wardrobe_tex_id = load_texture("textures/armario.jpg");
    monitor1_tex_id = load_texture("textures/Tela1.png");
    monitor2_tex_id = load_texture("textures/Tela2.png");
    mousepad_tex_id = load_texture("textures/mousepad.png");
    pc_tex_id = load_texture("textures/PC.png");
    shelf_tex_id = load_texture("textures/prateleira.jpg");
    tnt_tex_id = load_texture("textures/tnt.png");
    painting_tex_id = load_texture("textures/NoiteEstrelada2.jpg");
    fan_base_tex_id = load_texture("textures/preto.jpg");
    chair_tex_id = load_texture("textures/AssentoCadeira.jpeg");
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
    glBindTexture(GL_TEXTURE_2D, air_conditioner_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < AIR_CONDITIONER_VERTEX_COUNT; i++)
    {
        glNormal3f(AIR_CONDITIONER_NORMALS[i].x, AIR_CONDITIONER_NORMALS[i].y, AIR_CONDITIONER_NORMALS[i].z);
        glTexCoord2f(AIR_CONDITIONER_TEX_COORDS[i].x, AIR_CONDITIONER_TEX_COORDS[i].y);
        glVertex3f(AIR_CONDITIONER_VERTICES[i].x, AIR_CONDITIONER_VERTICES[i].y, AIR_CONDITIONER_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the main door
    glBindTexture(GL_TEXTURE_2D, doors_tex_id);
    glPushMatrix();
    glTranslatef(-0.192099, -0.052135, -8.332047);
    glRotatef(main_door_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.192099, 0.052135, 8.332047);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < DOOR_VERTEX_COUNT; i++)
    {
        glNormal3f(DOOR_NORMALS[i].x, DOOR_NORMALS[i].y, DOOR_NORMALS[i].z);
        glTexCoord2f(DOOR_TEX_COORDS[i].x, DOOR_TEX_COORDS[i].y);
        glVertex3f(DOOR_VERTICES[i].x, DOOR_VERTICES[i].y, DOOR_VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();

    // Draw the side door
    glPushMatrix();
    glTranslatef(-1.743257, -0.122533, 7.634487);
    glRotatef(side_door_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.743257, 0.122533, -7.634487);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < SECONDARY_DOOR_VERTEX_COUNT; i++)
    {
        glNormal3f(SECONDARY_DOOR_NORMALS[i].x, SECONDARY_DOOR_NORMALS[i].y, SECONDARY_DOOR_NORMALS[i].z);
        glTexCoord2f(SECONDARY_DOOR_TEX_COORDS[i].x, SECONDARY_DOOR_TEX_COORDS[i].y);
        glVertex3f(SECONDARY_DOOR_VERTICES[i].x, SECONDARY_DOOR_VERTICES[i].y, SECONDARY_DOOR_VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the bunkbed
    glBegin(GL_TRIANGLES);
    for(i = 0; i < BUNKBED_VERTEX_COUNT; i++)
    {
        glNormal3f(BEUNKBED_NORMALS[i].x, BEUNKBED_NORMALS[i].y, BEUNKBED_NORMALS[i].z);
        glTexCoord2f(BUNKBED_TEX_COORDS[i].x, BUNKBED_TEX_COORDS[i].y);
        glVertex3f(BUNKBED_VERTICES[i].x, BUNKBED_VERTICES[i].y, BUNKBED_VERTICES[i].z);
    }
    glEnd();


    // Draw the left window
    glBindTexture(GL_TEXTURE_2D, windows_tex_id);
    glPushMatrix();
    glTranslatef(14.902783, 3.648618, -1.792326);
    glRotatef(window_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-14.902783, -3.648618, 1.792326);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < LEFT_WINDOW_VERTEX_COUNT; i++)
    {
        glNormal3f(LEFT_WINDOW_NORMALS[i].x, LEFT_WINDOW_NORMALS[i].y, LEFT_WINDOW_NORMALS[i].z);
        glTexCoord2f(LEFT_WINDOW_TEX_COORDS[i].x, LEFT_WINDOW_TEX_COORDS[i].y);
        glVertex3f(LEFT_WINDOW_VERTICES[i].x, LEFT_WINDOW_VERTICES[i].y, LEFT_WINDOW_VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();

    // Draw the right window
    glPushMatrix();
    glTranslatef(14.903056, 3.648618, 3.201038);
    glRotatef(-window_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-14.903056, -3.648618, -3.201038);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < RIGHT_WINDOW_VERTEX_COUNT; i++)
    {
        glNormal3f(RIGHT_WINDOW_NORMALS[i].x, RIGHT_WINDOW_NORMALS[i].y, RIGHT_WINDOW_NORMALS[i].z);
        glTexCoord2f(RIGHT_WINDOW_TEX_COORDS[i].x, RIGHT_WINDOW_TEX_COORDS[i].y);
        glVertex3f(RIGHT_WINDOW_VERTICES[i].x, RIGHT_WINDOW_VERTICES[i].y, RIGHT_WINDOW_VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the table
    glBindTexture(GL_TEXTURE_2D, table_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < TABLE_VERTEX_COUNT; i++)
    {
        glNormal3f(TABLE_NORMALS[i].x, TABLE_NORMALS[i].y, TABLE_NORMALS[i].z);
        glTexCoord2f(TABLE_TEX_COORDS[i].x, TABLE_TEX_COORDS[i].y);
        glVertex3f(TABLE_VERTICES[i].x, TABLE_VERTICES[i].y, TABLE_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the bed
    glBegin(GL_TRIANGLES);
    for(i = 0; i < BED_VERTEX_COUNT; i++)
    {
        glNormal3f(BED_NORMALS[i].x, BED_NORMALS[i].y, BED_NORMALS[i].z);
        glTexCoord2f(BED_TEX_COORDS[i].x, BED_TEX_COORDS[i].y);
        glVertex3f(BED_VERTICES[i].x, BED_VERTICES[i].y, BED_VERTICES[i].z);
    }
    glEnd();
    
    // Draw the creeper
    glBindTexture(GL_TEXTURE_2D, creeper_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < CREEPER_VERTEX_COUNT; i++)
    {
        glNormal3f(CREEPER_NORMALS[i].x, CREEPER_NORMALS[i].y, CREEPER_NORMALS[i].z);
        glTexCoord2f(CREEPER_TEX_COORDS[i].x, CREEPER_TEX_COORDS[i].y);
        glVertex3f(CREEPER_VERTICES[i].x, CREEPER_VERTICES[i].y, CREEPER_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the wardrobe
    glBindTexture(GL_TEXTURE_2D, wardrobe_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < WARDROBE_VERTEX_COUNT; i++)
    {
        glNormal3f(WARDROBE_NORMALS[i].x, WARDROBE_NORMALS[i].y, WARDROBE_NORMALS[i].z);
        glTexCoord2f(WARDROBE_TEX_COORDS[i].x, WARDROBE_TEX_COORDS[i].y);
        glVertex3f(WARDROBE_VERTICES[i].x, WARDROBE_VERTICES[i].y, WARDROBE_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the monitor 1
    glBindTexture(GL_TEXTURE_2D, monitor1_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MONITOR1_VERTEX_COUNT; i++)
    {
        glNormal3f(MONITOR1_NORMALS[i].x, MONITOR1_NORMALS[i].y, MONITOR1_NORMALS[i].z);
        glTexCoord2f(MONITOR1_TEX_COORDS[i].x, MONITOR1_TEX_COORDS[i].y);
        glVertex3f(MONITOR1_VERTICES[i].x, MONITOR1_VERTICES[i].y, MONITOR1_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the monitor 2
    glBindTexture(GL_TEXTURE_2D, monitor2_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MONITOR2_VERTEX_COUNT; i++)
    {
        glNormal3f(MONITOR2_NORMALS[i].x, MONITOR2_NORMALS[i].y, MONITOR2_NORMALS[i].z);
        glTexCoord2f(MONITOR2_TEX_COORDS[i].x, MONITOR2_TEX_COORDS[i].y);
        glVertex3f(MONITOR2_VERTICES[i].x, MONITOR2_VERTICES[i].y, MONITOR2_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the mouse
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MOUSE_VERTEX_COUNT; i++)
    {
        glNormal3f(MOUSE_NORMALS[i].x, MOUSE_NORMALS[i].y, MOUSE_NORMALS[i].z);
        glTexCoord2f(MOUSE_TEX_COORDS[i].x, MOUSE_TEX_COORDS[i].y);
        glVertex3f(MOUSE_VERTICES[i].x, MOUSE_VERTICES[i].y, MOUSE_VERTICES[i].z);
    }
    glEnd();

    // Draw the mousepad
    glBindTexture(GL_TEXTURE_2D, mousepad_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < MOUSEPAD_VERTEX_COUNT; i++)
    {
        glNormal3f(MOUSEPAD_NORMALS[i].x, MOUSEPAD_NORMALS[i].y, MOUSEPAD_NORMALS[i].z);
        glTexCoord2f(MOUSEPAD_TEX_COORDS[i].x, MOUSEPAD_TEX_COORDS[i].y);
        glVertex3f(MOUSEPAD_VERTICES[i].x, MOUSEPAD_VERTICES[i].y, MOUSEPAD_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the PC
    glBindTexture(GL_TEXTURE_2D, pc_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < PC_VERTEX_COUNT; i++)
    {
        glNormal3f(PC_NORMALS[i].x, PC_NORMALS[i].y, PC_NORMALS[i].z);
        glTexCoord2f(PC_TEX_COORDS[i].x, PC_TEX_COORDS[i].y);
        glVertex3f(PC_VERTICES[i].x, PC_VERTICES[i].y, PC_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the shelf
    glBindTexture(GL_TEXTURE_2D, shelf_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < SHELF_VERTEX_COUNT; i++)
    {
        glNormal3f(SHELF_NORMALS[i].x, SHELF_NORMALS[i].y, SHELF_NORMALS[i].z);
        glTexCoord2f(SHELF_TEX_COORDS[i].x, SHELF_TEX_COORDS[i].y);
        glVertex3f(SHELF_VERTICES[i].x, SHELF_VERTICES[i].y, SHELF_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the room
    glBegin(GL_TRIANGLES);
    for(i = 0; i < ROOM_VERTEX_COUNT; i++)
    {
        glNormal3f(ROOM_NORMALS[i].x, ROOM_NORMALS[i].y, ROOM_NORMALS[i].z);
        glTexCoord2f(ROOM_TEX_COORDS[i].x, ROOM_TEX_COORDS[i].y);
        glVertex3f(ROOM_VERTICES[i].x, ROOM_VERTICES[i].y, ROOM_VERTICES[i].z);
    }
    glEnd();
    
    // Draw the keyboard
    glBegin(GL_TRIANGLES);
    for(i = 0; i < KEYBOARD_VERTEX_COUNT; i++)
    {
        glNormal3f(KEYBOARD_NORMALS[i].x, KEYBOARD_NORMALS[i].y, KEYBOARD_NORMALS[i].z);
        glTexCoord2f(KEYBOARD_TEX_COORDS[i].x, KEYBOARD_TEX_COORDS[i].y);
        glVertex3f(KEYBOARD_VERTICES[i].x, KEYBOARD_VERTICES[i].y, KEYBOARD_VERTICES[i].z);
    }
    glEnd();
    
    // Draw the tnt
    glBindTexture(GL_TEXTURE_2D, tnt_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < TNT_VERTEX_COUNT; i++)
    {
        glNormal3f(TNT_NORMALS[i].x, TNT_NORMALS[i].y, TNT_NORMALS[i].z);
        glTexCoord2f(TNT_TEX_COORDS[i].x, TNT_TEX_COORDS[i].y);
        glVertex3f(TNT_VERTICES[i].x, TNT_VERTICES[i].y, TNT_VERTICES[i].z);
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
    for(i = 0; i < FAN_VERTEX_COUNT; i++)
    {
        glNormal3f(FAN_NORMALS[i].x, FAN_NORMALS[i].y, FAN_NORMALS[i].z);
        glTexCoord2f(FAN_TEX_COORDS[i].x, FAN_TEX_COORDS[i].y);
        glVertex3f(FAN_VERTICES[i].x, FAN_VERTICES[i].y, FAN_VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();

    // Draw the fan base
    glBindTexture(GL_TEXTURE_2D, fan_base_tex_id);
    glPushMatrix();
    glTranslatef(1.220647, 2.604736, 2.619632);
    glRotatef(-40, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.220647, -2.604736, -2.619632);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < FAN_BASE_VERTEX_COUNT; i++)
    {
        glNormal3f(FAN_BASE_NORMALS[i].x, FAN_BASE_NORMALS[i].y, FAN_BASE_NORMALS[i].z);
        glTexCoord2f(FAN_BASE_TEX_COORDS[i].x, FAN_BASE_TEX_COORDS[i].y);
        glVertex3f(FAN_BASE_VERTICES[i].x, FAN_BASE_VERTICES[i].y, FAN_BASE_VERTICES[i].z);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the table lamp
    glBegin(GL_TRIANGLES);
    for(i = 0; i < TABLE_LAMP_VERTEX_COUNT; i++)
    {
        glNormal3f(TABLE_LAMP_NORMALS[i].x, TABLE_LAMP_NORMALS[i].y, TABLE_LAMP_NORMALS[i].z);
        glTexCoord2f(TABLE_LAMP_TEX_COORDS[i].x, TABLE_LAMP_TEX_COORDS[i].y);
        glVertex3f(TABLE_LAMP_VERTICES[i].x, TABLE_LAMP_VERTICES[i].y, TABLE_LAMP_VERTICES[i].z);
    }
    glEnd();

    // Draw the paiting
    glBindTexture(GL_TEXTURE_2D, painting_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < PAINTING_VERTEX_COUNT; i++)
    {
        glNormal3f(PAINTING_NORMALS[i].x, PAINTING_NORMALS[i].y, PAINTING_NORMALS[i].z);
        glTexCoord2f(PAINTING_TEX_COORDS[i].x, PAINTING_TEX_COORDS[i].y);
        glVertex3f(PAINTING_VERTICES[i].x, PAINTING_VERTICES[i].y, PAINTING_VERTICES[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw the chair
    glBindTexture(GL_TEXTURE_2D, chair_tex_id);
    glBegin(GL_TRIANGLES);
    for(i = 0; i < CHAIR_VERTEX_COUNT; i++)
    {
        glNormal3f(CHAIR_NORMALS[i].x, CHAIR_NORMALS[i].y, CHAIR_NORMALS[i].z);
        glTexCoord2f(CHAIR_TEX_COORDS[i].x, CHAIR_TEX_COORDS[i].y);
        glVertex3f(CHAIR_VERTICES[i].x, CHAIR_VERTICES[i].y, CHAIR_VERTICES[i].z);
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
