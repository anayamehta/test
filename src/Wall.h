#ifndef WALL_H
#define WALL_H

#include <Godot.hpp>
#include <Area.hpp>

namespace godot {

class Wall : public Area {
    GODOT_CLASS(Wall, Area)

private:
    Vector3 normal;

public:
    static void _register_methods();

    Wall();
    ~Wall();

    void _init(); // our initializer called by Godot

    void _process(float delta);

    void set_direction();
     
    Vector3 get_direction();

    void set_normal(Vector3 p_normal);
    Vector3 get_normal();
};

}

#endif