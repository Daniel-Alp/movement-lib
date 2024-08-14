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

inline void to_json(json& j, const Pose& pose) {
    j = json{
        {"x", pose.coordinates.x}, 
        {"y", pose.coordinates.y},
        {"theta", pose.theta},
    };
}

inline void to_json(json& j, const Vector& vector) {
    j = json{
        {"x", vector.x},
        {"y", vector.y}
    };
}

struct Test {
    double value;
};

inline void to_json(json& j, const Test& test) {
    j = json{
        {"value", test.value}
    };
}