#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

char *port = "\\\\.\\COM6";

int main(){
	SerialPort arduino(port);
	if(arduino.isConnected()){
		cout<<"Connection made"<<endl<<endl;
	}
	else{
		cout<<"Error in port name"<<endl<<endl;
	}
	while(arduino.isConnected()){
		cout<<"Enter your number: "<<endl;
		string data;
		cin>>data;

		char *charArray = new char[data.size() + 1];
		copy(data.begin(), data.end(), charArray);
		charArray[data.size()] = '\n';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		cout<<">> "<<output<<endl;

		delete [] charArray;
	}
	return 0;
}