#include <iostream>
#include <cpprest/ws_client.h>
#include <cpprest/filestream.h>

using namespace std;
using namespace utility;
using namespace web;
using namespace web::websockets::client;
using namespace concurrency;
using namespace concurrency::streams;

void ramlab_websocket_test()
{
    websocket_client client;
    client.connect("ws://52.79.166.119/websocket").wait();
    websocket_outgoing_message out_msg;
    out_msg.set_utf8_message("test2");
    client.send(out_msg).wait();

    client.receive().then([](websocket_incoming_message in_msg)
    {
        //cout<<in_msg.length()<<endl;
        return in_msg.extract_string();
    })
    .then([](string body)
    {
        cout<<body<<endl;
    })
    .wait();

    client.close().wait();
}
int main()
{
    for(int i = 0; i < 25; i++)
    {
        ramlab_websocket_test();
        cout<<i<<endl;
    }

    return 0;
}


//#include <iostream>
//#include <cpprest/ws_client.h>
//
//using namespace std;
//using namespace utility;
//using namespace web;
//using namespace web::websockets::client;
//
//void  on_message(const websocket_incoming_message &in_msg)
//{
//    cout<<"I am here"<<endl;
//}
//
//int main()
//{
//  websocket_callback_client client;
//  client.connect("ws://127.0.0.1/s").wait();
//
//  websocket_outgoing_message out_msg;
//  out_msg.set_utf8_message("test");
//  client.send(out_msg).wait();
//
////  client.receive().then([](websocket_incoming_message in_msg)
////  {
////    return in_msg.extract_string();
////    //return in_msg.message_type();
////  })
////  .then([](string body)
////  {
////    cout << body << endl; // test
////  })
////  .wait();
//  cout<<"I am here"<<endl;
//  client.set_message_handler(&on_message);
//  client.close().wait();
//
//  return 0;
//}

