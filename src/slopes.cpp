#include "slopes.h"
#include "main.h"

#define PI 3.1415926535898


Slopes::Slopes(float x, float y,float temp, int angle,color_t color) {
    this->position = glm::vec3(x, y-0.1-temp, 0);
    this->rotation = angle;
    this->radius = temp;
   // printf("\n%fslopes\n",temp);
    speed = 0;
    allDown = 0;
    allLeft = 0;
    allRight = 0;
    allTop = 0;
    this->speed_x = 0.05;
    //printf("aaaaaaaaaaaaaaaaaaa%f\n",y-0.2-temp);
    static const GLfloat vertex_buffer_data[] = {
        -0.8, -0.1+0.1+temp, 0, // vertex 1
        0.8,  -0.1+0.1+temp, 0, // vertex 2
        0.8,  0.1+0.1+temp, 0, // vertex 3

        0.8,  0.1+0.1+temp, 0, // vertex 3
        -0.8, 0.1+0.1+temp, 0, // vertex 4
        -0.8, -0.1+0.1+temp, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Slopes::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Slopes::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slopes::tick() {
//    this->position.x -= speed;
     //this->position.y -= speed;

    /*
    if(this->position.y >= -2.25)
        this->speed += 0.01;
    else
        this->position.y = -2.25;
    if(  (3.5-0.8  < this->position.x && this->position.x < 3.5+0.8)){
        if(  this->position.y <= -1.5){
        this->position.y = -1.5;
        this->speed = -0.2;
        //flagg = 0;
        }
    }*/
}

bounding_box_t Slopes::bounding_slope() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t slopes = { x, y+0.1+this->radius, 0.8, 0.2  };
    return slopes;
}
