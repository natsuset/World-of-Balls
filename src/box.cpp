#include "box.h"
#include "main.h"

#define PI 3.1415926535898


Box::Box(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    //speed = 0;
//    allDown = 0;
//    allLeft = 0;
//    allRight = 0;
//    allTop = 0;

   //  GLfloat g_vertex_buffer_data[3240] = {};
   //     double angle = 0.0;
   //     int i;
   // for(i=0;i<3240;i+=9){
   //     g_vertex_buffer_data[i] = cos(angle) * 0.5;
   //     g_vertex_buffer_data[i + 1] = sin(angle) * 0.5;
   //     g_vertex_buffer_data[i + 2] = 0;

   //     g_vertex_buffer_data[i + 3] = cos(angle + PI /180) * 0.5;
   //     g_vertex_buffer_data[i + 4] = sin(angle + PI / 180) * 0.5;
   //     g_vertex_buffer_data[i + 5] = 0;

   //     g_vertex_buffer_data[i + 6] = 0;
   //     g_vertex_buffer_data[i + 7] = 0;
   //     g_vertex_buffer_data[i + 8] = 0;

   //     angle = PI / 180 +angle;
   //  }

    static const GLfloat g_vertex_buffer_data[] = {
        5, 0.75, 0, // vertex 1
        5,  -0.75, 0, // vertex 2
        -5,  -0.75, 0, // vertex 3

        5,  0.75, 0, // vertex 3
        -5, -0.75, 0, // vertex 4
        -5, 0.75, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Box::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

// void Ball::set_position(float x, float y) {
//     this->position = glm::vec3(x, y, 0);
// }

// void Ball::tick() {
// //    this->position.x -= speed;
//      this->position.y -= speed;
// }

// bounding_box_t Ball::bounding_box() {
//     float x = this->position.x, y = this->position.y;
//     bounding_box_t bbox = { x, y, 0.4, 0.4 };
//     return bbox;
// }
