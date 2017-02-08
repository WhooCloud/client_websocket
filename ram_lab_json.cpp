#include "ram_lab_com.h"

int main(int, char*[])
{
     ofstream out("localhost.txt");
    for(int n = 0; n < 1; n++)
    {
        char url[] = "ws://localhost/websocket"; //ws_url
        websocket_client client;    //Connect to server
        client.connect(url).wait();

        Document docu_state_imu;
        docu_state_imu.SetObject();
        // Change timestamp to current time
        docu_state_imu.Parse(json_payload);
        //add payload
        char payload_char[5];
        int payload_size = 4;
        int i;
        for(i = 0; i < payload_size; i++)
            payload_char[i] = '0';
        payload_char[i] = '\0';
        Value payload;
        payload.SetString(payload_char, static_cast<SizeType>(payload_size), docu_state_imu.GetAllocator());
        docu_state_imu.AddMember("payload", payload, docu_state_imu.GetAllocator());
        //change timestamp to current time
        docu_state_imu["timestamp"] = getCurrentTime();
        StringBuffer data_send;
        PrettyWriter<StringBuffer> writer(data_send);
        docu_state_imu.Accept(writer);
        //Send Json packet
        webSocketSendText(client, data_send.GetString());
        //cout<<data_send.GetString()<<endl;

        //Receive Json packet
        string data_receive;
        data_receive = webSocketReceiveText(client);
        //Culculate delay
        double time1_receive, time2_receive, delta_time_receive;
        time2_receive = getCurrentTime();

        Document docu_state_fused;
        docu_state_fused.SetObject();
        char data_receive_char[1024*2];
        string2CharArray(data_receive_char, data_receive);
        docu_state_fused.Parse(data_receive_char);
        time1_receive = docu_state_fused["timestamp"].GetDouble();
        delta_time_receive = time2_receive - time1_receive;

        cout<<"delay2 is: "<<delta_time_receive*1000<<" ms"<<endl;
        out<<"delay2 is: "<<delta_time_receive*1000<<" ms"<<endl;
        cout<<"size of data_send is: "<<data_send.GetSize()<<endl;
        cout<<"size of data_receive is: "<<data_receive.size()<<endl;

        client.close().wait();
        //for(long i = 0; i < 10000; i++);
    }
    return 0;
}
/*
int main(int, char*[])
{
    for(int n = 0; n < 1; n++)
    {
        char url[] = "ws://localhost/websocket"; //ws_url
        websocket_client client;    //Connect to server
        client.connect(url).wait();

        Document docu_state_imu;
        docu_state_imu.SetObject();
        // Change timestamp to current time
        docu_state_imu.Parse(json_state);
        docu_state_imu["timestamp"] = getCurrentTime();
        StringBuffer data_send;
        PrettyWriter<StringBuffer> writer(data_send);
        docu_state_imu.Accept(writer);
        //Send Json packet
        webSocketSendText(client, data_send.GetString());
        //Receive Json packet
        string data_receive;
        data_receive = webSocketReceiveText(client);
        //Culculate delay
        double time1_receive, time2_receive, delta_time_receive;
        time2_receive = getCurrentTime();

        Document docu_state_fused;
        docu_state_fused.SetObject();
        char data_receive_char[1024];
        string2CharArray(data_receive_char, data_receive);
        docu_state_fused.Parse(data_receive_char);

        time1_receive = docu_state_fused["timestamp"].GetDouble();
        delta_time_receive = time2_receive - time1_receive;
        cout<<"delay2 is: "<<delta_time_receive*1000<<" ms"<<endl;
        cout<<"size of state_imu is:"<<data_send.GetSize()<<endl;
        cout<<"state_imu is:"<<data_send.GetString()<<endl;
        cout<<"size of state_fused is:"<<data_receive.size()<<endl;
        cout<<"state_fused is:"<<data_receive<<endl;
        //cout<<data_receive<<endl;

        client.close().wait();
    }
    return 0;
}
*/
