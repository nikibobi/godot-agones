#include "agones.h"
#include "helpers.h"

using namespace godot;

Agones::Agones()
{
    sdk = std::make_unique<agones::SDK>();
}

bool Agones::Connect()
{
    return sdk->Connect();
}

void Agones::Ready()
{
    const auto& status = sdk->Ready();
    log_error(status);
}

bool Agones::Health()
{
    return sdk->Health();
}

godot::Dictionary Agones::GameServer()
{
    sdk::GameServer gameServer;
    const auto& status = sdk->GameServer(&gameServer);
    log_error(status);
    return game_server_to_dict(gameServer);
}

void Agones::Shutdown()
{
    const auto& status = sdk->Shutdown();
    log_error(status);
}

void Agones::SetLabel(godot::String key, godot::String value)
{
    const auto& status = sdk->SetLabel(to_std(key), to_std(value));
    log_error(status);
}

void Agones::SetAnnotation(godot::String key, godot::String value)
{
    const auto& status = sdk->SetAnnotation(to_std(key), to_std(value));
    log_error(status);
}

void Agones::_register_methods()
{
    register_method("connect", &Agones::Connect);
    register_method("ready", &Agones::Ready);
    register_method("health", &Agones::Health);
    register_method("game_server", &Agones::GameServer);
    register_method("shutdown", &Agones::Shutdown);
    register_method("set_label", &Agones::SetLabel);
    register_method("set_annotation", &Agones::SetAnnotation);
}
