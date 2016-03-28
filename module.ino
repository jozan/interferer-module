#include <vector>
#include "InterfererModule.h"
#define LOGGING

InterfererModule module;

int outputPins[] = {
    A0, A1, A2, A3, A4, A5
};

int inputPins[] = {
    D0, D1, D2, D3, D4, D5
};

void setup() {
    //setupHttpClient();

    // Set which pins are outputting
    for (auto pinOut : outputPins) {
        pinMode(pinOut, OUTPUT);
    }

    // Set which pins are reading
    for (auto pinIn : inputPins) {
        pinMode(pinIn, INPUT_PULLDOWN);
    }

    #ifdef LOGGING
    Serial.begin(9600);
    #endif
}

void loop() {
    checkWiring();

    #ifdef LOGGING
    Serial.println();
    Serial.print("State:");
    Serial.println();
    for (auto conf : module.state) {
        Serial.print(conf.pinOut);
        Serial.print(" -> ");
        Serial.println(conf.pinIn);
    }
    #endif

    // Emits state only when state has changed
    module.emitState(module.state);

    delay(500);
}

void checkWiring() {
    std::vector<State> newState;

    // Loop through each possible state in
    // order to check the wiring configuration
    for (auto pinOut : outputPins) {
        digitalWrite(pinOut, HIGH);

        for (auto pinIn : inputPins) {
            if (digitalRead(pinIn) != HIGH) {
                continue;
            }

            // Store the configuration into the temporal state
            State conf = { pinOut, pinIn };
            newState.push_back(conf);
        }

        digitalWrite(pinOut, LOW);
    }

    // Updates state only if necessary
    module.updateState(newState);
}

/*
void setupHttpClient() {
    uint8_t server[] = { 192, 168, 0, 10 };
    IPAddress IPfromBytes(server);

    request.ip = IPfromBytes;
    request.port = 8088;
    request.path = "/exec.lua";
}*/
