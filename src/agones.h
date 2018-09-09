#ifndef AGONES_H
#define AGONES_H

#include <memory>

#include <agones/sdk.h>
#include <grpc++/grpc++.h>

#include <Godot.hpp>
#include <Reference.hpp>
#include <CoreTypes.hpp>

namespace godot
{
    class Agones : public godot::GodotScript<Reference>
    {
        GODOT_CLASS(Agones)

    private:
        std::unique_ptr<agones::SDK> sdk;

    public:
        Agones();

        bool Connect();
        void Ready();
        bool Health();
        godot::Dictionary GameServer();
        void Shutdown();
        void SetLabel(godot::String key, godot::String value);
        void SetAnnotation(godot::String key, godot::String value);

        static void _register_methods();
    };
}

#endif