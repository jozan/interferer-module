#include <sstream>
#include "HttpClient.h"
#include "InterfererModule.h"

/**
* Constructor.
*/
InterfererModule::InterfererModule()
{
    setupHttpClient();
}

void InterfererModule::emitState()
{
    if(!shouldEmitState) {
        return;
    }

    auto json = jsonizeState().c_str();

    request.body = json;
    http.post(request, response);

    #ifdef LOGGING
    Serial.println(json);
    Serial.print("Response from server: ");
    Serial.println(response.body);
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

void InterfererModule::setupHttpClient() {
    uint8_t server[] = { 192, 168, 0, 10 };
    int port = 8087;

    /*
    http_header_t headers[] = {
        { "Content-Type", "application/json" },
        { "Accept" , "*//*"},
        { NULL, NULL } // NOTE: Always terminate headers with NULL
    };
    */

    IPAddress IPfromBytes(server);

    request.ip = IPfromBytes;
    request.port = port;
    request.path = "/";
}

bool operator ==(const State &a, const State &b) {
    return a.pinOut == b.pinOut && a.pinIn == b.pinIn;
}

bool operator !=(const State &a, const State &b) {
    return a.pinOut != b.pinOut && a.pinIn != b.pinIn;
}
