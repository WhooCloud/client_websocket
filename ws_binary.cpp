#include <cpprest/ws_client.h>
#include <cpprest/filestream.h>
#include <cpprest/producerconsumerstream.h>
using namespace utility;
using namespace web;
using namespace web::websockets::client;
using namespace concurrency;
using namespace concurrency::streams;

int main()
{
    websocket_client client;
    client.connect("ws://ec2-52-53-170-219.us-west-1.compute.amazonaws.com/s").wait();

//    websocket_outgoing_message msg;
//    msg.set_utf8_message("I am a UTF-8 string! (Or close enough...)");
//    client.send(msg)
//    .then([]()
//    {
//        std::cout<<"Sending Scuccessfully"<<std::endl;
//    }).wait();

    websocket_outgoing_message msg;
    concurrency::streams::producer_consumer_buffer<uint8_t> buf;
    std::vector<uint8_t> body(6);
    memcpy(&body[0], "a\0b\0c\0", 6);

    auto send_task = buf.putn(&body[0], body.size())
    .then([&](size_t length)
    {
        msg.set_binary_message(buf.create_istream(), length);
        return client.send(msg);
    })
    .then([](pplx::task<void> t)
    {
        try
        {
            t.get();
        }
        catch(const websocket_exception& ex)
        {
            std::cout << ex.what();
        }
    })
    .wait();

    client.receive()
    .then([](websocket_incoming_message msg)
    {
        return msg.extract_string();
    })
    .then([](std::string body)
    {
        std::cout << body << std::endl;
    }).wait();

    client.close().wait();
    return 0;
}
