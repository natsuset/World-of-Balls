#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y,float r, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    int allLeft,allRight,allTop,allDown;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed_x;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
