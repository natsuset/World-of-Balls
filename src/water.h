#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int allLeft,allRight,allTop,allDown;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed_x;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // WATER_H
