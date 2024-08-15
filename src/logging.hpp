#pragma once
#include "json.hpp"
#include "translation.hpp"

using json = nlohmann::json;

struct Message {
    std::string topic;
    json payload; 
};

inline void to_json(json& j, const Message& msg) {
    j = json{{"topic", msg.topic}, {"payload", msg.payload}};
}

// Pose struct defined in translation.hpp
inline void to_json(json& j, const Pose& pose) {
    j = json{
        {"x", pose.coordinates.x}, 
        {"y", pose.coordinates.y},
        {"theta", pose.theta},
    };
}

struct Velocities {
    double l;
    double r;
    double target;
};

inline void to_json(json& j, const Velocities& vels) {
    j = json{
        {"l", vels.l},
        {"r", vels.r},
        {"target", vels.target}
    };
}