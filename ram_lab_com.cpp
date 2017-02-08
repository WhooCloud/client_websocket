#include "ram_lab_com.h"
char json_state[] = " { \"type\" : \"input_imu\", \"timestamp\" : 500.736034 , "\
                              "\"posi\":[-0.039294902, -0.09044182, -0.06832063] , "\
                              "\"cov_posi\":[-26.178856,-19.393106,-6.809244,"
                                            "-6.809244,-6.809244,-6.809244,"
                                            "-6.809244,-6.809244,-6.809244] , "\
                              "\"ori\":[-2.0395765, 0.068644375,-3.0333138,"
                                        "-3.0333138,-3.0333138,-3.0333138,"
                                        "-3.0333138,-3.0333138,-3.0333138] , "\
                              "\"cov_ori\":[0.026928991, 0.018066406, -0.012341589, "
                                            "-0.012341589, -0.012341589, -0.012341589, "
                                            "-0.012341589, -0.012341589, -0.012341589]}  ";

char json_feature_camera[] = " { \"type\" : \"input_camera\", \"timestamp\" : 1452657.360343, "\
                              "\"camera1\":[[5, 100, 200, 9, 150, 250], [6, 101, 201, 10, 151, 251], "\
                              "[5, 100, 200, 9, 150, 250], [6, 101, 201, 10, 151, 251]]}  ";

char json_payload[] = " {\"timestamp\" : 1452657.360343}  ";

void webSocketSendText(websocket_client client, const char* str)
{

    websocket_outgoing_message out_msg;
    out_msg.set_utf8_message(str);

    client.send(out_msg).wait();
}
string webSocketReceiveText(websocket_client client)
{
    string data_receive;
    client.receive().then([](websocket_incoming_message in_msg) mutable
    {
        return in_msg.extract_string();
    })
    .then([&data_receive](string body)
    {
        data_receive = body;
    })
    .wait();
    return data_receive;
}
double getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

void string2CharArray(char * c, string s)
{
    int i;
    for( i=0; i<s.length(); i++)
        c[i] = s[i];

    c[i] = '\0';
}
/*
string ltos(long l)
{
    ostringstream os;
    os<<l;
    string result;
    istringstream is(os.str());
    is>>result;
    return result;

}*/
