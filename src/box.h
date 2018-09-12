#include "main.h"

#ifndef BOX_H
#define BOX_H


class Box {
public:
    Box() {}
    Box(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    int allLeft,allRight,allTop,allDown;
    void draw(glm::mat4 VP);
    //void set_position(float x, float y);
    //void tick();
    //double speed;
    //bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
