#include "Wall.h"

using namespace godot;

void Wall::_register_methods() {
    register_method("_process", &Wall::_process);
    register_property<Wall, Vector3>("normal", &Wall::set_normal, &Wall::get_normal, Vector3(1.0, 1.0, 1.0));
    // register_signal<Wall>((char *)"area_entered", "normal", GODOT_VARIANT_TYPE_VECTOR3);
}

Wall::Wall() {

}

Wall::~Wall() {
    // add your cleanup here
}

void Wall::_init() {
    // initialize any variables here
    // TODO: calculate the normal vector of this wall 
    set_monitoring(true);
}

void Wall::_process(float delta) {
    // check for collisions (if anything entered this area)
    // if so, then send this wall's normal to the ball it hit (so that ball can use it)
    // emit_signal("area_entered", this, (0.0, 1.1, 2.2));
}

void Wall::set_normal(Vector3 p_normal){
    normal = p_normal;
}

Vector3 Wall::get_normal(){
    return normal;
}