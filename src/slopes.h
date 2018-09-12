#include "main.h"

#ifndef SLOPES_H
#define SLOPES_H


class Slopes {
public:
    Slopes() {}
    Slopes(float x, float y, float temp, int angle, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    int allLeft,allRight,allTop,allDown;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed_x;
    bounding_box_t bounding_slope();
private:
    VAO *object;
};

#endif // BALL_H
