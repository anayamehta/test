#include "Ball.h"
#include "Wall.h"
#include <cstdlib>
#include <ctime>

using namespace godot;

void Ball::_register_methods() {
    register_method("_process", &Ball::_process);
    register_method("_on_Wall_area_entered", &Ball::_on_Wall_area_entered);
    register_method("_on_Ball_area_entered", &Ball::_on_Ball_area_entered);
    register_method("_ready", &Ball::_ready);
    register_method("get_direction", &Ball::get_direction);
}

Ball::Ball() {
}

Ball::~Ball() {
    // add your cleanup here
}

void Ball::_init() {
    // initialize any variables here
    time_passed = 0.0;
    set_monitoring(true);
    std::srand(std::time(NULL));
}

void Ball::_ready(){
    get_node(NodePath("/root/Main/Wall"))->connect("area_entered", this, "_on_Wall_area_entered", Array::make(get_node(NodePath("/root/Main/Wall"))));
    get_node(NodePath("/root/Main/Wall2"))->connect("area_entered", this, "_on_Wall_area_entered", Array::make(get_node(NodePath("/root/Main/Wall2"))));  
    get_node(NodePath("/root/Main/Wall3"))->connect("area_entered", this, "_on_Wall_area_entered", Array::make(get_node(NodePath("/root/Main/Wall3"))));
    get_node(NodePath("/root/Main/Wall4"))->connect("area_entered", this, "_on_Wall_area_entered", Array::make(get_node(NodePath("/root/Main/Wall4"))));
    get_node(NodePath("/root/Main/Wall5"))->connect("area_entered", this, "_on_Wall_area_entered", Array::make(get_node(NodePath("/root/Main/Wall5"))));
    get_node(NodePath("/root/Main/Wall6"))->connect("area_entered", this, "_on_Wall_area_entered", Array::make(get_node(NodePath("/root/Main/Wall6"))));


    get_node(NodePath("/root/Main/Spatial/Area"))->connect("area_entered", this, "_on_Ball_area_entered", Array::make(get_node(NodePath("/root/Main/Spatial/Area"))));
    get_node(NodePath("/root/Main/Spatial2/Area"))->connect("area_entered", this, "_on_Ball_area_entered", Array::make(get_node(NodePath("/root/Main/Spatial2/Area"))));
    get_node(NodePath("/root/Main/Spatial3/Area"))->connect("area_entered", this, "_on_Ball_area_entered", Array::make(get_node(NodePath("/root/Main/Spatial3/Area"))));


    double x = ((double) std::rand());
    double y = ((double) std::rand());
    double z = ((double) std::rand());
    direction = Vector3(x, y, z);// something random
    direction.normalize();

    speed = (std::rand() % 10) + 5; // something random
    double x_pos = ((double) std::rand() / (RAND_MAX)) * 2;
    double y_pos = ((double) std::rand() / (RAND_MAX)) * 3;
    double z_pos = ((double) std::rand() / (RAND_MAX));
    curr_position = Vector3(x_pos, y_pos, z_pos); // something random
    set_translation(curr_position);
}

void Ball::_process(float delta) {
    // if the ball is signaled to hit something, use the normal vector received to
    // calculate what its new direction should be
    // for each time tick, keep the ball moving in the same direction and same speed

    time_passed += delta;

    Vector3 velocity = speed * direction;
    Vector3 displacement = delta * velocity;
    Vector3 new_position = curr_position + displacement;

    set_translation(new_position);
    curr_position = new_position;
}

Vector3 Ball::get_direction(){
    return this->direction;
}

void Ball::_on_Wall_area_entered(Area *area, Area *wall){
    if(Object::cast_to<Ball>(area) && Object::cast_to<Wall>(wall)){
        if(Object::cast_to<Ball>(area) == this){
            Vector3 normal = (Object::cast_to<Wall>(wall))->get_normal();
            // direction = direction - 2 * normal * (normal.dot(direction));
            this->direction = this->direction.bounce(normal);
            this->direction.normalize();
        } 
    }
}

void Ball::_on_Ball_area_entered(Area *area, Area *ball){
    // check if it is not a wall. // check if it is not itself
    if(Object::cast_to<Ball>(ball) && Object::cast_to<Ball>(area)){
        if(Object::cast_to<Ball>(ball) != this && Object::cast_to<Ball>(area) == this){
            Vector3 normal = (Object::cast_to<Ball>(ball))->get_direction();
            this->direction = this->direction.bounce(normal);
            this->direction.normalize();
        }
    }
}