#include <vector>
#include <string>
#include "spark_wiring_usbserial.h"
#define LOGGING

/**
 * Store a pin-to-pin wiring.
 */
struct State
{
    int pinOut, pinIn;
};

class InterfererModule {
public:

    /**
    * Constructor.
    */
    InterfererModule(void);

    /**
     * Used to store all pin-to-pin wirings
     * that are currently configured.
     */
    std::vector<State> state;

    bool shouldEmitState = false;

    void emitState(std::vector<State> &state);
    void updateState(std::vector<State> &newState);
private:
    bool hasStateChanged(std::vector<State> &newState);
    std::string jsonizeState();
};
