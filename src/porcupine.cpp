#include "porcupine.h"
#include "main.h"

#define PI 3.1415926535898


Porcupine::Porcupine(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = -0.01;
    allDown = 0;
    allLeft = 0;
    allRight = 0;
    allTop = 0;
    this->speed_x = 0;
   //  GLfloat g_vertex_buffer_data[6] = {};//color_t color_vertex_buffer_data[3240] = {};
 

   static const GLfloat g_vertex_buffer_data[] = {
       -1, -2.8, 0, // vertex 1
       -0.5,  -2.8, 0, // vertex 2
       -0.75,  -2.5, 0, // vertex 3


       0, -2.8, 0, // vertex 1
       -0.5,  -2.8, 0, // vertex 2
       -0.25,  -2.5, 0, // vertex 3

       0.5,  -2.8, 0, // vertex 3
       0, -2.8, 0, // vertex 4
       0.25, -2.5, 0, // vertex 1

       1,  -2.8, 0, // vertex 3
       0.5, -2.8, 0, // vertex 4
       0.75, -2.5, 0 // vertex 1
   };

    this->object = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data, color, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porcupine::tick() {
//    this->position.x -= speed;
     //this->position.y -= this->speed;
    //this->speed_x += 0.05;
    this->position.x += this->speed_x;
    this->speed_x += this->speed;
    if(this->speed_x >= 0.1 || this->speed_x <= -0.1){
        this->speed = -this->speed;
    }
    else{
       // if(this->speed_x > 0)
            //this->speed_x += 0.005;
       // else
       //     this->speed_x -= 0.005;
    }


}

bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y-2.5, 1, 0.5 };
    return bbox;
}