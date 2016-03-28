#include <vector>
#include <string>
#include "spark_wiring_usbserial.h"
#include "HttpClient.h"
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

    void emitState();
    void updateState(std::vector<State> &newState);
private:
    bool hasStateChanged(std::vector<State> &newState);
    std::string jsonizeState();

    // HTTP Request
    HttpClient http;
    http_header_t headers;
    http_request_t request;
    http_response_t response;
    void setupHttpClient();
};
