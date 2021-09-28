#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include <GL/gl.h>
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_VERTICES 60000

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

typedef struct ObjectMesh {
    unsigned int tex_id;
    int VERTEX_COUNT;
    Vec3 VERTICES[MAX_VERTICES];
    Vec3 NORMALS[MAX_VERTICES];
    Vec2 TEX_COORDS[MAX_VERTICES];
} ObjectMesh;


/*-----------------------------------------*/
/*--------------- CONSTANTS ---------------*/
/*-----------------------------------------*/
const float DEG2RAD = 3.14159265 / 180.0f;


/*-----------------------------------------*/
/*--------------- FUNCTIONS ---------------*/
/*-----------------------------------------*/
int load_obj(const char* path, ObjectMesh *object);
unsigned int load_texture(const char* path);


int load_obj(const char* path, ObjectMesh *object)
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
                object->VERTICES[object->VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
                object->TEX_COORDS[object->VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
                object->NORMALS[object->VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
                object->VERTEX_COUNT++;
            }
        }
    }

    fclose(fp);

    return 1;
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
