#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float r, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    color_t color;
    int allLeft,allRight,allTop,allDown;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int score;
    double speed,speed_x;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
