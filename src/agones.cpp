#include "agones.h"

using namespace godot;

void Agones::_register_methods()
{
    register_method("connect", &Agones::Connect);
    register_method("ready", &Agones::Ready);
    register_method("health", &Agones::Health);
    register_method("shutdown", &Agones::Shutdown);
}

bool Agones::Connect()
{
    return sdk->Connect();
}

bool Agones::Ready()
{
    grpc::Status status = sdk->Ready();
    return status.ok();
}

bool Agones::Health()
{
    return sdk->Health();
}

bool Agones::Shutdown()
{
    grpc::Status status = sdk->Shutdown();
    return status.ok();
}

Agones::Agones()
{
    sdk = new agones::SDK();
}

Agones::~Agones()
{
}