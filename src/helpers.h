#ifndef HELPERS_H
#define HELPERS_H

#include "agones.h"

using namespace stable::agones::dev;

inline std::string to_std(const godot::String& s)
{
    return std::string(s.utf8().get_data());
}

inline godot::String to_godot(const std::string& s)
{
    return godot::String(s.c_str());
}

inline void log_error(const grpc::Status& status)
{
    if (!status.ok())
    {
        const auto& message = to_godot(status.error_message());
        godot::Godot::print(message);
    }
}

godot::Dictionary object_meta_to_dict(const sdk::GameServer_ObjectMeta& object_meta)
{
    godot::Dictionary result, annotations, labels;
    result["name"] = to_godot(object_meta.name());
    result["namespace"] = to_godot(object_meta.namespace_());
    result["uid"] = to_godot(object_meta.uid());
    result["resource_version"] = to_godot(object_meta.resource_version());
    result["generation"] = object_meta.generation();
    result["creation_timestamp"] = object_meta.creation_timestamp();
    result["deletion_timestamp"] = object_meta.deletion_timestamp();
    for (auto& pair : object_meta.annotations())
    {
        annotations[to_godot(pair.first)] = to_godot(pair.second);
    }
    result["annotations"] = annotations;
    for (auto& pair : object_meta.labels())
    {
        labels[to_godot(pair.first)] = to_godot(pair.second);
    }
    result["labels"] = labels;
    return result;
}

godot::Dictionary spec_to_dict(const sdk::GameServer_Spec& spec)
{
    godot::Dictionary result, health;
    health["disabled"] = spec.health().disabled();
    health["periodseconds"] = spec.health().periodseconds();
    health["failurethreshold"] = spec.health().failurethreshold();
    health["initialdelayseconds"] = spec.health().initialdelayseconds();
    result["health"] = health;
    return result;
}

godot::Dictionary status_to_dict(const sdk::GameServer_Status& status)
{
    godot::Dictionary result, ports;
    result["state"] = to_godot(status.state());
    result["address"] = to_godot(status.address());
    for (auto& port : status.ports())
    {
        ports[to_godot(port.name())] = port.port();
    }
    result["ports"] = ports;
    return result;
}

godot::Dictionary game_server_to_dict(const sdk::GameServer& gameServer)
{
    godot::Dictionary result;
    result["object_meta"] = object_meta_to_dict(gameServer.object_meta());
    result["spec"] = spec_to_dict(gameServer.spec());
    result["status"] = status_to_dict(gameServer.status());
    return result;
}

#endif // HELPERS_H
