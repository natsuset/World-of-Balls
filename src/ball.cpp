#include "ball.h"
#include "main.h"

#define PI 3.1415926535898


Ball::Ball(float x, float y, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = r;
    this->score = 0;
    this->color = color;
    speed = 0;
    allDown = 0;
    allLeft = 0;
    allRight = 0;
    allTop = 0;
    this->speed_x = 0.05;
    GLfloat g_vertex_buffer_data[3240] = {};//color_t color_vertex_buffer_data[3240] = {};
       double angle = 0.0;
       int i,j=0;
   for(i=0;i<3240;i+=9){
       g_vertex_buffer_data[i] = cos(angle) * r;
       g_vertex_buffer_data[i + 1] = sin(angle) * r;
       g_vertex_buffer_data[i + 2] = 0;

       g_vertex_buffer_data[i + 3] = cos(angle + PI /180) * r;
       g_vertex_buffer_data[i + 4] = sin(angle + PI / 180) * r;
       g_vertex_buffer_data[i + 5] = 0;

       g_vertex_buffer_data[i + 6] = 0;
       g_vertex_buffer_data[i + 7] = 0;
       g_vertex_buffer_data[i + 8] = 0;

       //color_vertex_buffer_data[j++] = COLOR_RED;
/*
       color_vertex_buffer_data[i + 1] = ;
       color_vertex_buffer_data[i + 2] = ;*/

//       color_vertex_buffer_data[i + 3] = ;
//       color_vertex_buffer_data[i + 4] = ;
//       color_vertex_buffer_data[i + 5] = ;

//       color_vertex_buffer_data[i + 6] = ;
//       color_vertex_buffer_data[i + 7] = ;
//       color_vertex_buffer_data[i + 8] = ;

       angle = PI / 180 +angle;
    }


//    static const GLfloat vertex_buffer_data[] = {
//        -0.2, -0.2, 0, // vertex 1
//        0.2,  -0.2, 0, // vertex 2
//        0.2,  0.2, 0, // vertex 3

//        0.2,  0.2, 0, // vertex 3
//        -0.2, 0.2, 0, // vertex 4
//        -0.2, -0.2, 0 // vertex 1
//    };

    this->object = create3DObject(GL_TRIANGLES, 1080, g_vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
//    this->position.x -= speed;
     this->position.y -= speed;
     if(this->position.x <= -4.75){
         this->speed_x = - this->speed_x;
     }

     if(this->position.x >= 4.75){
         this->speed_x = - this->speed_x;
     }
    if(this->position.x < 1 &&this->position.x > -1 && this->position.y <= -2.5){
       // printf("%f\n",this->speed);
    }
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

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.25, 0.25 };
    return bbox;
}
