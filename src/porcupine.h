#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine {
public:
    Porcupine() {}
    Porcupine(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int allLeft,allRight,allTop,allDown;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
//    void Porcupine_delete();
    double speed,speed_x;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
