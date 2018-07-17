#ifndef AGONES_H
#define AGONES_H

#include <agones/sdk.h>
#include <grpc++/grpc++.h>

#include <Godot.hpp>
#include <Reference.hpp>

namespace godot
{
    class Agones : public godot::GodotScript<Reference>
    {
        GODOT_CLASS(Agones)

    private:
        agones::SDK* sdk;

    public:
        static void _register_methods();

        bool Connect();
        bool Ready();
        bool Health();
        bool Shutdown(); 

        Agones();
        ~Agones();
    };
}

#endif