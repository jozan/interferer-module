#include <sstream>
#include "InterfererModule.h"

/**
* Constructor.
*/
InterfererModule::InterfererModule()
{

}

void InterfererModule::emitState(std::vector<State> &state)
{
    if(!shouldEmitState) {
        return;
    }

    #ifdef LOGGING
    Serial.println(jsonizeState().c_str());
    #endif

    shouldEmitState = false;
}

void InterfererModule::updateState(std::vector<State> &newState) {
    if (!hasStateChanged(newState)) {
        return;
    }

    state.clear();

    for (auto conf : newState) {
        state.push_back(conf);
    }

    shouldEmitState = true;
}

bool InterfererModule::hasStateChanged(std::vector<State> &newState) {
    return state != newState;
}

std::string InterfererModule::jsonizeState() {
    std::ostringstream json;
    auto it = state.begin(); // iterator

    json << "[";

    while (it != state.end()) {
        json << "{";
            json << "\"" << it->pinOut << "\"" << ":";
            json << "\"" << it->pinIn << "\"";
        json << "}";

        if (!(it != state.end() && it + 1 == state.end())) {
            json << ",";
        }

        it++;
    }

    json << "]";

    return json.str();
}

bool operator ==(const State &a, const State &b) {
    return a.pinOut == b.pinOut && a.pinIn == b.pinIn;
}

bool operator !=(const State &a, const State &b) {
    return a.pinOut != b.pinOut && a.pinIn != b.pinIn;
}
