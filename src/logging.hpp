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

// For tuning motion profiling
struct Velocities {
    double l;
    double r;
    double target;
    uint32_t t; //ms
};

inline void to_json(json& j, const Velocities& vels) {
    j = json{
        {"l", vels.l},
        {"r", vels.r},
        {"target", vels.target},
        {"t", vels.t}
    };
}

// For comparing setpoint to process variable
struct SPPV {
    double sp;
    double pv;
    uint32_t t; //ms
};

inline void to_json(json& j, const SPPV& sppv) {
    j = json {
        {"SP", sppv.sp},
        {"PV", sppv.pv},
        {"t", sppv.t}  
    };
}

struct Number {
    double x;
};

inline void to_json(json& j, const Number num) {
    j = json{{"x", num.x}};
}