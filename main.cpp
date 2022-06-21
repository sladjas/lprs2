#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include <ctype.h>
#include<windows.h>


#include"SerialPort.h"
#include <algorithm>

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

const char *port = "COM6";

bool is_digits(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

int main() {
	SerialPort arduino(port);
	if (arduino.isConnected()) {
		cout << "Arduino je povezan" << endl << endl;
	}
	else {
		cout << "Pogresan PORT" << endl << endl;
	}
	while (arduino.isConnected()) {
		cout << "Unesite broj koji zelite da se ispise na displeju: " << endl;
		string data;
		cin >> data;
		fflush(stdout);
		Sleep(1000);

		if(data.size()>8){
			cout << "Broj ne smije imati vise od 8 cifara!" << endl << endl;
		}
		else {
			if (is_digits(data)) {
				char* charArray = new char[data.size() + 1];
				copy(data.begin(), data.end(), charArray);
				charArray[data.size()] = '\n';

				arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
				arduino.readSerialPort(output, MAX_DATA_LENGTH);

				delete[] charArray;
				data = "";
				data.clear();

				cout << "Da li zelite jos brojeva?" << endl << endl;
				cout << "Ako je vas odgovor DA unesite y." << endl;
				cout << "Ako je vas odgovor NE unesite n." << endl;
				string data1;
				cin >> data1;
				while (data1.compare("y") != 0 && data1.compare("n") != 0) {
					cout << "Pogresan unos, unesite ponovo" << endl << endl;
					cin >> data1;
				}
				if (data1.compare("n") == 0) {
					cout << "Dovidjenja" << endl << endl;
					break;
				}
			}
			else {
				cout << "Pogresan unos, unesite broj" << endl << endl;
			}
		}
	
	}
	return 0;
}
