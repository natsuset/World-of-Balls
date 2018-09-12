#include "boost.h"
#include "main.h"

#define PI 3.1415926535898


Boost::Boost(float x, float y, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
   // this->radius = r;
    //this->score = 0;
    this->color = color;
    speed = 0;
    allDown = 0;
    allLeft = 0;
    allRight = 0;
    allTop = 0;
    this->speed_x = 0.05;
  //  GLfloat g_vertex_buffer_data[3240] = {};//color_t color_vertex_buffer_data[3240] = {};
    //   double angle = 0.0;
     //  int i,j=0;

    static const GLfloat vertex_buffer_data[] = {
        -0.3, -0.3, 0, // vertex 1
        0.3,  -0.3, 0, // vertex 2
        0.3,  0.3, 0, // vertex 3

        0.3,  0.3, 0, // vertex 3
        -0.3, 0.3, 0, // vertex 4
        -0.3, -0.3, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Boost::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boost::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boost::tick() {
//    this->position.x -= speed;
}

bounding_box_t Boost::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.6, 0.6 };
    return bbox;
}
