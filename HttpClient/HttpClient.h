// HttpClient made by Nils Mattisson (nmattisson)
// License: MIT
// Github: https://github.com/nmattisson/HttpClient

#ifndef __HTTP_CLIENT_H_
#define __HTTP_CLIENT_H_
//#define LOGGING

#include "application.h"
#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"

/**
 * Defines for the HTTP methods.
 */
static const char* HTTP_METHOD_GET    = "GET";
static const char* HTTP_METHOD_POST   = "POST";
static const char* HTTP_METHOD_PUT    = "PUT";
static const char* HTTP_METHOD_DELETE = "DELETE";
static const char* HTTP_METHOD_PATCH  = "PATCH";

/**
 * This struct is used to pass additional HTTP headers such as API-keys.
 * Normally you pass this as an array. The last entry must have NULL as key.
 */
struct http_header_t
{
  const char* header;
  const char* value;
};

/**
 * HTTP Request struct.
 * hostname request host
 * path	 request path
 * port     request port
 * body	 request body
 */
struct http_request_t
{
  String hostname;
  IPAddress ip;
  String path;
  // TODO: Look at setting the port by default.
  //int port = 80;
  int port;
  String body;
};

/**
 * HTTP Response struct.
 * status  response status code.
 * body	response body
 */
struct http_response_t
{
  int status;
  String body;
};

class HttpClient {
public:
    /**
    * Public references to variables.
    */
    TCPClient client;
    char buffer[1024];

    /**
    * Constructor.
    */
    HttpClient(void);

    /**
    * HTTP request methods.
    * Can't use 'delete' as name since it's a C++ keyword.
    */
    void get(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, (http_header_t*)NULL, HTTP_METHOD_GET);
    }

    void post(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, (http_header_t*)NULL, HTTP_METHOD_POST);
    }

    void put(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, (http_header_t*)NULL, HTTP_METHOD_PUT);
    }

    void del(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, (http_header_t*)NULL, HTTP_METHOD_DELETE);
    }

    void get(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[])
    {
        request(aRequest, aResponse, headers, HTTP_METHOD_GET);
    }

    void post(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[])
    {
        request(aRequest, aResponse, headers, HTTP_METHOD_POST);
    }

    void put(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[])
    {
        request(aRequest, aResponse, headers, HTTP_METHOD_PUT);
    }

    void del(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[])
    {
        request(aRequest, aResponse, headers, HTTP_METHOD_DELETE);
    }

    void patch(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[])
    {
        request(aRequest, aResponse, headers, HTTP_METHOD_PATCH);
    }

private:
    /**
    * Underlying HTTP methods.
    */
    void request(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[], const char* aHttpMethod);
    void sendHeader(const char* aHeaderName, const char* aHeaderValue);
    void sendHeader(const char* aHeaderName, const int aHeaderValue);
    void sendHeader(const char* aHeaderName);
};

#endif /* __HTTP_CLIENT_H_ */