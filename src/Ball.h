#ifndef BALL_H
#define BALL_H

#include <Godot.hpp>
#include <Area.hpp>

namespace godot {

class Ball : public Area {
    GODOT_CLASS(Ball, Area)

private:
    Vector3 direction;
    float time_passed;
    float speed;
    Vector3 curr_position;
public:
    static void _register_methods();

    Ball();
    ~Ball();

    void _init(); // our initializer called by Godot

    void _ready();

    void _process(float delta);

    void _on_Wall_area_entered(Area *area, Area *wall);

    void _on_Ball_area_entered(Area *area, Area *ball);

    Vector3 get_direction();
};

}

#endif