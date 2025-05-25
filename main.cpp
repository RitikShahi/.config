#include <iostream>
#include <raylib.h>
using namespace std;
int player_score=0;
int cpu_score=0;
Color Brown = Color{139, 69, 19, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Yellow = Color{243, 213, 91, 255};
class Ball{
    public:
    float x,y;
    int radius;
    int speed_x,speed_y;
    void draw(){
        DrawCircle(x,y,radius,Yellow);
    }
    void update(){
        x+=speed_x;
        y+=speed_y;
        if(y+radius >=GetScreenHeight() || y-radius<=0){
            speed_y*=-1;
        } 
        if(x+radius >=GetScreenWidth()){
            cpu_score++;
            resetBall();
        }
        if(x-radius<=0){
            player_score++;
            resetBall();
        }
    }
    void resetBall(){
        x=GetScreenWidth()/2;
        y=GetScreenHeight()/2;
        int speedchoices[2]={-1,1};
        speed_x *=speedchoices[GetRandomValue(0,1)];
        speed_y *=speedchoices[GetRandomValue(0,1)];
    }
    Ball(int x,int y,int radius,int sped_x,int sped_y){
        this->x=x;
        this->y=y;
        this->radius=radius;
        speed_x=sped_x;
        speed_y=sped_y;
    }
};
class Paddle{
    protected:
    void LimitMovement(){
        if(y<=0){
            y=0;
        }
        if(y>=GetScreenHeight()-height){
            y=GetScreenHeight()-height;
        }
    }
    public:
    int x,y,height,width;
    int speed_y;
    void draw(){
        DrawRectangle(x,y,width,height,Brown);
    }
    void update(){
        if(IsKeyDown(KEY_UP))
        y=y-speed_y;
        if(IsKeyDown(KEY_DOWN))
        y=y+speed_y;
        LimitMovement();
    }
};
class cpuPaddle:public Paddle{
    public:
    void update(int ball_y){
        if(y+height/2>ball_y){
            y-=speed_y;
        }
        if(y+height/2<=ball_y){
            y+=speed_y;
        }
        LimitMovement();
    }
};
int main () {
    const int width=1280;
    const int height=800;
    const char* title="Ping Pong";
   InitWindow(width,height,title);
   SetTargetFPS(60);
   Ball ball(width/2,height/2,20,7,7);
   Paddle player;
   cpuPaddle cpu;
   player.width=25;
   player.height=120;
   player.x=width-player.width;
   player.y=height/2-player.height/2;
   player.speed_y=5;
   cpu.width=25;
   cpu.height=120;
   cpu.x=0;
   cpu.y=height/2 -60;
   cpu.speed_y=6;
    while(!WindowShouldClose()){
        ball.update();
        player.update();
        cpu.update(ball.y);
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x, player.y, player.width, player.height}))
        ball.speed_x*=-1;
         if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
         ball.speed_x*=-1;
        BeginDrawing();
        ClearBackground(Dark_Green);
        ball.draw();
        cpu.draw();
        player.draw();
        DrawLine(640,0,640,800,WHITE);
        DrawText(TextFormat("%i",cpu_score),width/4 -20,20,80,WHITE);
        DrawText(TextFormat("%i",player_score),3* width/4 -20,20,80,WHITE);
        EndDrawing();
    }
    CloseWindow();
}