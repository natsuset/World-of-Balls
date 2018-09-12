#include "main.h"
#include "timer.h"
#include "ball.h"
#include "box.h"
#include "water.h"
#include "trampoline.h"
#include "porcupine.h"
#include "slopes.h"
#include "magnet.h"
#include "boost.h"

//#include <chrono>
//#include <thread>
#define GLFW_RELEASE   0

#define PI 3.1415926535898

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1, ball2;
Box box,box2,box3,box4;
Water water;
Trampoline tramp;
Porcupine porcu,porcu1;
Magnet magnet,magnet1;
Boost boost,boost1,boost2,boost3;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0,tim = 0,allow = 0;
int flagg=0,count2 = 0,count1 = 0,flagg1=0,check =0,porcu_f = 0,porcu1_f = 0,slope_f = 0,timer_f = 0,magnet_f = 0;
int world2 = 0,y_1 = -2.5,Level = 1;
float pan = 0.0,pan1=0.0;
vector<Ball> balls;
vector<Slopes> slope;
Timer t60(1.0 / 60);
Timer t20(1.0 / 1.5);
Timer t5(10.0);
Timer t1(20.0);
Timer t2(40.0);
 static int oldState = GLFW_RELEASE;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(pan1/5, pan, 3), glm::vec3(pan1/5, pan, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    box.draw(VP);
    box2.draw(VP);
    box3.draw(VP);
    box4.draw(VP);
//    boost.draw(VP);
//    boost1.draw(VP);
//    boost2.draw(VP);
//    boost3.draw(VP);
    water.draw(VP);
    if((t5.processTick() || timer_f ) && ball1.score > 300){
        timer_f = 1;
        if(t1.processTick()){
            if(timer_f == 1)
                timer_f = 0;
        }
     magnet.draw(VP);
     magnet1.draw(VP);
    }
    ball1.draw(VP);
    //ball2.draw(VP);


    tramp.draw(VP);
    int i;
    for(i=0;i<count2;i++){
        balls[i].draw(VP);
    }

    for(i=0;i<count1;i++){
        slope[i].draw(VP);
    }
    if(porcu_f == 1){
        porcu.draw(VP);
        Level = 2;
    }
    if(porcu1_f == 1){
        Level = 4;
        porcu1.draw(VP);
    }
    //balls[0].draw(VP);
}


void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int zoom_in = glfwGetKey(window, GLFW_KEY_KP_ADD);
    int zoom_out = glfwGetKey(window, GLFW_KEY_KP_SUBTRACT);
    int One = glfwGetKey(window,GLFW_KEY_1);
    int Two = glfwGetKey(window,GLFW_KEY_2);
    if(One){
        pan1 += 0.1;
    }
    if(Two){
        pan1-= 0.1;
    }
    if (left) {
        if(ball1.position.x - 0.05 >= -4.75)
        {
            if(ball1.position.y > -2.5) ball1.speed_x = -0.05;

            if(ball1.position.x < 1 && ball1.position.x > -1){
                ball1.position.x -= 0.02;
            }
            else {
                ball1.position.x -= 0.05;
            }
        }
        else{
            ball1.position.x = -4.75;
        }
    }
    if (right) {

        if(ball1.position.x + 0.05 <= 4.75)
        {
            if(ball1.position.y > -2.5) ball1.speed_x = 0.05;

            if(ball1.position.x < 1 && ball1.position.x > -1){
                ball1.position.x += 0.02;
            }
            else {
            ball1.position.x += 0.05;
            }

            //ball1.speed_x = 0;
        }
        else{
            ball1.position.x = 4.75;
            //ball1.speed_x = -0.15;
        }
//        ball1.position.x += 0.05;
//        if(detect_collision(ball1.bounding_box(), ball2.bounding_box())){
//            ball1.position.x -= 0.05;
//            ball1.position.x = -2.4;
//        }
    }
    if (up) {
        oldState = GLFW_PRESS;
        //flagg = 1;
     }
    if(zoom_in){
        screen_zoom *= 1.01;
        reset_screen();
    }

    if(zoom_out){
        screen_zoom *= 0.99;
        reset_screen();
    }
}

void slopecollision() {
for (int i = 0; i < count1; i++)
    {
        if((detect_collision(ball1.bounding_box(), slope[i].bounding_slope())) && ball1.speed >= 0){
            double ang = slope[i].rotation * PI/180;
            //double ang = 45 * PI/180;
            ball1.speed_x = -ball1.speed*sin(ang);
            ball1.speed = -ball1.speed*cos(ang);
            // printf("COllision Occured\n");
            //bflg=1;
        }

    }
}


void tramp_func(){
//        if(ball1.position.y > -2.25)
//            ball1.speed += 0.5;
//        if(ball1.position.y <= -2.25){
//            ball1.speed = 0;
//            ball1.position.y = -2.25;
//        }
        if(  (3.5-0.8  < ball1.position.x && ball1.position.x < 3.5+0.8)){
            if(  ball1.position.y <= -1.5+0.25 && ball1.position.y != -2.5){
            ball1.position.y = -1.5+0.25;
            ball1.speed = -0.5;
           // flagg = 0;
            tim = 0.001;
            }
        }
}

void move_water(){
    if((ball1.position.x >= 1 || ball1.position.x <= -1) && ball1.speed == 0 && ball1.position.y < -2.5) ball1.position.y = -2.5;
    if(ball1.position.x > -1 && ball1.position.x < 1 && ball1.position.y <= -2.5 ){
        if(ball1.position.y >= -abs((double)sqrt(1-((double)ball1.position.x * (double)ball1.position.x)))-2.5  && tim == 0) // && tim == 0
            ball1.speed = 0.001;
        else if(ball1.position.y < -abs((double)sqrt(1-((double)ball1.position.x * (double)ball1.position.x)))-2.5)
            ball1.speed = 0;
            if(ball1.speed != 0 && ball1.position.y < -2.5) {ball1.position.y -= 0.01;}

            else {
            ball1.position.y = -abs((double)sqrt(1-((double)ball1.position.x * (double)ball1.position.x)))-2.5;
            if(ball1.position.x>0)
            ball1.position.x -= 0.01;
            if(ball1.position.x<0)
            ball1.position.x += 0.01;
            }

    }
}

void magnetballs() {
    if(t5.processTick() || (timer_f )){
        timer_f = 1;
        if(t1.processTick()){
            if(timer_f == 1)
                timer_f = 0;
        }
        int tmp_f = 0;
        for(int i=0;i<count1;i++){
            if((detect_collision(ball1.bounding_box(), slope[i].bounding_slope())))
                tmp_f = 1;
        }
        if(ball1.position.y > -2.5 && tmp_f == 0)
            ball1.speed_x -= 0.001;
     }
}
void boostcollision() {
    if(ball1.position.y<= 4.9 && ball1.speed > 0){
        ball1.position.y = 11.25;
        ball1.speed = 0;
        ball1.speed_x = 0;
        if(ball1.position.y >= 11.25) {
            ball1.speed = 0;
            ball1.position.y = 11.25;
        }
        world2 = 1;

    }

}

void porcucollision() {
    if((detect_collision(ball1.bounding_box(), porcu.bounding_box())) && porcu_f == 1){
        //porcu.erase(porcu.begin() + 0);
        //delete * Porcupine;
        world2 = 1;
        ball1.score -= 100;
        //balls.erase(balls.begin() + i);
       // printf("askhbvkb\n");
        porcu_f = 0;
    }

    if((detect_collision(ball1.bounding_box(), porcu1.bounding_box())) && porcu1_f == 1){
        //printf("asclknvkbav\n");
        //porcu1.Porcupine_delete();

        world2 = 1;
        ball1.score -= 500;
        porcu1_f = 0;
    }
}

void tick_elements() {
    ball1.tick();
    porcu.tick();
    porcu1.tick();
    move_water();
    slopecollision();
    porcucollision();
    if(ball1.position.x >= 2.75&& ball1.position.y <= -1.5){
        ball1.speed_x = 0;
        ball1.position.x = 2.75;
        ball1.speed = 0;
    }/*
    if(ball1.position.x >= 2.75&& ball1.position.x <= 4.2 && ball1.position.y <= -1.5){
        ball1.speed_x = 0;
        ball1.position.x = 4.3;
        ball1.speed = 0;

    }*/
    //if(world2 == 0)
   // boostcollision();
  //  worldcheck();
//    if(world2 == 0){
//        y_1 = -2.5;
//    }
//    if(world2 == 1){
//        y_1 = 11.25;
//    }
    if(ball1.score > 300){
        magnetballs();
    }
    if(porcu1_f == 1){
       // printf("::::BEFOREASSDASD::::\n");
        if(t2.processTick()){
         //   printf("::::ASSDASD::::\n");
            porcu1_f = 0;
        }
    }
    if(ball1.score > 200){
    //porcu.push_back(Porcupine(-2,0,COLOR_YELLOW));
    //porcu_f = 1;
  //  pan+=13;
    }
     if(ball1.score > 100){
       //porcu1.push_back( Porcupine(2.5,4.5,COLOR_YELLOW));
       //slope.push_back(P(-5.5,random+tempoo +0.1,tempoo ,c * b,COLOR_YELLOW));
      // porcu1_f = 1;

     }

     if(ball1.score > 300){
          Level = 3;
         magnet = Magnet(-4,4,1,COLOR_RED);
         magnet1 = Magnet(-4,4,0.75,COLOR_BACKGROUND);
     }
    for(int i =0;i< count2;i++){
        balls[i].position.x += balls[i].speed_x;
    }
    for(int i =0;i< count1;i++){
        slope[i].position.x += slope[i].speed_x;
    }
    for(int i=0;i< count2;i++){
        if(balls[i].position.x >= 5){
            balls.erase(balls.begin() + i);
            count2--;

        }
     for(int i = 0; i< count1;i++){
             if(slope[i].position.x >= 5){
         slope.erase(slope.begin() + i);
         count1--;
             }
     }
    }
//    if(flagg == 2){

//    }
    if(tim){
       // ball1.speed -= 0.01*tim;
        if(ball1.position.y > -2.5)
                ball1.speed += 0.02;
        ball1.position.x += ball1.speed_x;
        tim+=1;
        if (ball1.position.y <= -2.5 ) {
            if(ball1.position.x < 1 && ball1.position.x > -1){
                if(ball1.position.y < -2.5){
                    ball1.speed_x = ball1.speed_x /3;
                    ball1.speed = ball1.speed / 1.5;
                   //ball1.speed = (ball1.speed /abs(ball1.speed)) *(abs(ball1.speed) - 0.06);
                }
                if(ball1.position.y <= -abs((double)sqrt(1-((double)ball1.position.x * (double)ball1.position.x)))-2.5 )
                        {
                            tim = 0;
                            ball1.speed = 0;
                            ball1.speed_x = 0;
                            allow = 0;
                             //flagg = 0;
                            //ball1.position.x = -abs(sqrt(1-(ball1.position.y+2.5)*(ball1.position.y+2.5)));
                            ball1.position.y = -abs(sqrt(1-(ball1.position.x * ball1.position.x)))-2.5;
                        }

            }
            else {
               // printf("HEYAAAAA\n");
                    ball1.speed = 0;
                    ball1.speed_x = 0;
                    tim = 0;
                    ball1.position.y = -2.5; //ball2.position.y;
                    allow = 0;
                   flagg = 0;
                  }
         }

    }


    for(int i=0;i<count2;i++){
        color_t cc1 = COLOR_RED;
        color_t cc2 = COLOR_YELLOW;
        color_t cc3 = COLOR_GREEN;
        color_t cc4 = COLOR_BROWN;
        color_t cc5 = COLOR_BLUE;
        if (detect_collision(ball1.bounding_box(), balls[i].bounding_box())) {

             if(ball1.position.y < balls[i].position.y ){
                ball1.speed = 0;
                ball1.position.y = balls[i].position.y - 1;
                //flagg = 2;
            }
            else if(balls[i].rotation == 0){
                 if(balls[i].rotation!=0){
                     //balls[i].speed =
                             double ang = balls[i].rotation * PI/180;
                             //double ang = 45 * PI/180;
                             ball1.speed_x = -ball1.speed*sin(ang);
                             ball1.speed = -ball1.speed*cos(ang);
                            }
                 else {
                     int ret = ball1.score;
                 if(balls[i].color.r == cc1.r && balls[i].color.g == cc1.g && balls[i].color.b == cc1.b)
                     ball1.score += 40;
                 else if(balls[i].color.r == cc2.r && balls[i].color.g == cc2.g && balls[i].color.b == cc2.b)
                     ball1.score +=  50;
                 else if(balls[i].color.r == cc3.r && balls[i].color.g == cc3.g && balls[i].color.b == cc3.b)
                     ball1.score += 20;
                 else if(balls[i].color.r == cc4.r && balls[i].color.g == cc4.g && balls[i].color.b == cc4.b)
                     ball1.score += 30;
                 else if(balls[i].color.r == cc5.r && balls[i].color.g == cc5.g && balls[i].color.b == cc5.b)
                     ball1.score += 50;
                balls.erase(balls.begin() + i);
                count2--;
                    if(ball1.score > 200 && ret <= 200 ) {
                        porcu_f = 1;
                       // printf("ASDASD\n");
                    }

                    if(ball1.score > 500 && ret <= 500 ) {
                        porcu1_f = 1;
                    }
                ball1.speed = -0.3;
                 }
            }
            // printf("%d\n",ball1.score);
        }

    }
    tramp_func();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    porcu = Porcupine(-2,0,COLOR_YELLOW);
    porcu1 =  Porcupine(2.5,4.5,COLOR_YELLOW);
    ball1       = Ball(2, -2.5,0.25, COLOR_RED);
    box = Box(0,-3.5,1,COLOR_GREEN);
    box2 = Box (0,-4.25,1,COLOR_BROWN);
    box3 = Box(0,9.5,1,COLOR_GREEN);
    box4 = Box (0,8.75,1,COLOR_BROWN);
    water = Water(0,-2.75,COLOR_RED);
    tramp = Trampoline(3.5,-1.5,COLOR_RED);
    boost = Boost(2,4,1,COLOR_RED);
    boost1 = Boost(2,4.6,1,COLOR_BLUE);
    boost2 = Boost(2.6,4,1,COLOR_BLUE);
    boost3 = Boost(2.6,4.6,1,COLOR_RED);
    //if(ball1.score > 200)
    //porcu = Porcupine(-2,0,COLOR_YELLOW);
    /*
    magnet = Magnet(-4,4,1,COLOR_RED);
    magnet1 = Magnet(-4,4,0.75,COLOR_BACKGROUND); */
    ball1.speed_x = 0;
    //balls.push_back(Ball(-3, 2, COLOR_RED));
//    int j;
//    for(j=0;j = 10;j++){
//        lanuchers[i]
//    }
  //GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
//          static const GLfloat g_vertex_buffer_data[] = {
//             0.0f, 1.0f, 0.0f,
//             1.0f, -1.0f, 0.0f,
//             -1.0f,  -1.0f, 0.0f,


//          };

//          GLuint vertexbuffer;
//                  glGenBuffers(1, &vertexbuffer);
//                  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//                  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//    glDrawArrays(GL_TRIANGLES, 0, 3);




    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    //object = create3DObject(GL_TRIANGLES, 1080, g_vertex_buffer_data, color, GL_FILL);
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 1.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 1200;

    window = initGLFW(width, height);

    initGL (window, width, height);
//    static int oldState = GLFW_PRESS;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            string rst;
                        stringstream convert;
                        convert << ball1.score;
                        rst = convert.str();

                        const char *one = "Score ";
                        const char *two = rst.c_str();
                        string rst1;
                                    stringstream convert1;
                                    convert1 << Level;
                                    rst1 = convert1.str();

                        const char *three = "   Level ";
                        const char *four = rst1.c_str();

                        string total( string(one) + two + string(three)+four);
                        glfwSetWindowTitle(window, total.c_str());
            int newState = glfwGetKey(window, GLFW_KEY_UP);
            if (oldState == GLFW_PRESS && newState == GLFW_RELEASE) {

                if(allow == 0){
                    ball1.speed = -0.4;
                    flagg = 1;
                    //if(tim != 0) check = 1;
                    tim = 0.001;
                    allow = 1;
                }
            }
            oldState = newState;
            draw();


//            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
        }
        if(t20.processTick()){

            if(count2 < 10){
                const float MIN_RAND = 0.0, MAX_RAND = 4.5;
                const float range = MAX_RAND - MIN_RAND;

                float random = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND ;

                const float MAX_RAND1 = 1.0,MIN_RAND1 = 0.1;
                const float range1 = MAX_RAND1 - MIN_RAND1;
                //float tempoo = range1 * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND1 ;
                int xx = rand() % 9;
                float tempoo = 0.4;
                if(xx == 0)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_RED));
                else if(xx == 1)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_YELLOW));
                else if(xx == 2)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_GREEN));
                else if(xx == 3)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_BROWN));
                else if(xx == 4)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_BLUE));
                else if(xx == 5)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_BLUE));
                else if(xx == 6)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_GREEN));
                else if(xx == 7)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_BLUE));
                else if(xx == 8)
                balls.push_back(Ball(-5.5, random,tempoo, COLOR_BROWN));

                int a = rand() % 3;

                if(a == 0 && (ball1.score > 100 || slope_f == 1)){
                    Level =  2;
                    int b = rand() % 46;
                    int c = rand() % 2;
                    if(c == 0) c = -1;
                    if(c == 1) c = 1;
                    //printf("%d\n",a);
                        //printf("%f\nmain",tempoo);
                        balls[count2].rotation = b;
                        slope.push_back(Slopes(-5.5,random+tempoo +0.1,tempoo ,c * b,COLOR_YELLOW));
                        count1++;
                        slope_f = 1;
                }

                count2++;
            }
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x)   < (a.width + b.width)) &&
           (abs(a.y - b.y)   < (a.height + b.height));
}



void zoomDec(){
    screen_zoom += 0.1;
    reset_screen();
}

void zoomInc(){
    screen_zoom -= 0.1;
    reset_screen();
}
void reset_screen() {
    float top    = screen_center_y + 8 / screen_zoom;
    float bottom = screen_center_y - 5 / screen_zoom;
    float left   = screen_center_x - 5 / screen_zoom;
    float right  = screen_center_x + 5 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
