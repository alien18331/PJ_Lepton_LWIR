#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "mqtt/async_client.h"


using namespace std;
using namespace std::chrono;

int MQTT_nodeInit();
void MQTT_Publish(string);
void MQTT_terminated();

const string DFLT_ADDRESS { "tcp://172.168.1.220:1883" };
const string TOPIC { "12AP5_R408_COM_IR" };
const int QOS = 1;

const auto PERIOD = milliseconds(1000);

const int MAX_BUFFERED_MSGS = 300;	// 120 * 5sec => 10min off-line buffering
//@param maxBufferedMessages the maximum number of messages allowed to be buffered while not connected

string address = DFLT_ADDRESS;
mqtt::async_client aclient(address, "", MAX_BUFFERED_MSGS);
mqtt::topic top(aclient, TOPIC, QOS, true);

int MQTT_nodeInit() {
	mqtt::connect_options connOpts;
	//connOpts.set_keep_alive_interval(MAX_BUFFERED_MSGS * PERIOD);
	connOpts.set_clean_session(true);
	connOpts.set_automatic_reconnect(true);
	
	try {
		aclient.connect(connOpts)->wait();
	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() << endl;
		return 1;
	}
 	return 0;
}

void MQTT_Publish(string str_data) {
	top.publish(std::move(str_data));	
	//cout << "OK!!!" << '\n';
}

void MQTT_terminated() {
	// Disconnect
	cout << "\nDisconnecting..." << flush;
	aclient.disconnect()->wait();
	//cout << "OK" << endl;
}
