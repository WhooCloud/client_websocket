#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


// Creates an HTTP request and prints part of its response stream.
pplx::task<void> HTTPStreamingAsync()
{
    http_client client(U"http://www.fourthcoffee.com");

    return client.request(methods::GET).then([](http_response response)
    {
        if(response.status_code() != status_codes::OK)
        {
            // Handle error cases...
            return pplx::task_from_result();
        }

        // Perform actions here reading from the response stream...
        // In this example, we print the first 15 characters of the response to the console.
        istream bodyStream = response.body();
        container_buffer<std::string> inStringBuffer;
        return bodyStream.read(inStringBuffer, 15).then([inStringBuffer](size_t bytesRead)
        {
            const std::string &text = inStringBuffer.collection();

            // For demonstration, convert the response text to a wide-character string.
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
            std::wostringstream ss;
            ss << utf16conv.from_bytes(text.c_str()) << std::endl;
            std::wcout << ss.str();
        });
    });

    /* Output:
    <!DOCTYPE html>
    */
}

int main()
{
    HTTPStreamingAsync().wait();
}
