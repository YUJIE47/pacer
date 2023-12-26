
#include <stdio.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "022d75fe-9e7d-11ee-8c90-0242ac120002"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"



int X0 = 1, X1 = 0, X10 = 1, X11 = 0;
//int X110 = 1, X111 = 0, X112 = 0;
//int X113 = 0;
int X12 = 0, X120 = 1, X121 = 0, X122 = 0;//, X123 = 0;
int X2 = 0, X20 = 1, X21 = 0;
int X210 = 1, X211 = 0, X212 = 0, X213 = 0, X214 = 0, X215 = 0, X216 = 0;
int X22 = 0, X220 = 1, X221 = 0, X222 = 0, X3 = 0;

//initial values
float Distance = 0, Time = 0;
float CompletedDistance = 0, Speed = 0;
int Pace = 0;
int Acc = 0, Gyro = 0;
bool Bluetooth_connect = false;
BLECharacteristic *pCharacteristic;
BLEService *pService;
BLEServer *pServer;


void grafcet0();
void datapath0();
void action0();
void InitialSetupModule();
void grafcet1();
void datapath1();
void SignalProcessingAndSpeedFeedbackModule();
void grafcet2();
void datapath2();
void DisplayData();
void action10();
void InitialPaceModule();
//void grafcet11();
//void datapath11();
void BluetoothTransmissionModule();
void grafcet12();
void datapath12();
//void action110();
//void GetTotalRunningDistance ();
//void GetDefaultTime();
void action120();
void SetupConnectionBluetooth();
void SendDistanceTimebyCellphone();
void GetDistanceTimebyDevice();
void action20();
void SignalProcessingModule();
void grafcet21();
void datapath21();
void SpeedFeedbackModule();
void grafcet22();
void datapath22();
void action210();
void CalculatePace();
void ReadAccelerometerGyroscope();
void CalculateSpeed();
void CalculateStep();
void CalculateStride();
void CalculateDistance();
void action220();
void LongVibration();
void ShortVibration();

void setup()
{
    Serial.begin(115200);
    printf("X0 = %d,X1 = %d,X2 = %d,X3 = %d\n",X0 ,X1 ,X2 ,X3 );
}
void loop()
{
    datapath0();
	  grafcet0();
  	printf("X0 = %d,X1 = %d,X2 = %d,X3 = %d\n",X0 ,X1 ,X2 ,X3 );
  
  	delay(1000);
}

void grafcet0()
{

	if((X0 == 1) && (1))
	{
    X0 = 0;
		X1 = 1;
		return;
	}

	if((X1 == 1) && (Distance && Time))
	{
		X1 = 0;
		X2 = 1;
		return;
	}

	if((X2 == 1) && (CompletedDistance && Speed))
	{
		X2 = 0;
		X3 = 1;
		return;
	}

	if((X3 == 1) && (1))
	{
		X3 = 0;
		X2 = 1;
		return;
	}

}
void grafcet1()
{

	if((X10 == 1) && (1))
	{
		X10 = 0;
		X11 = 1;
		return;
	}

	if((X11 == 1) && (1))
	{
		X11 = 0;
		X12 = 1;
		return;
	}

	if((X12 == 1) && (1))
	{
		X12 = 0;
		X10 = 1;
		return;
	}

}
/*void grafcet11()
{

	if((X110 == 1) && (1))
	{
		X110 = 0;
		X111 = 1;
		X112 = 1;
		return;
	}

	if((X111 == 1)&& (X112 == 1))
	{
		X111 = 0;
		X112 = 0;
		X110 = 1;
		return;
	}

}*/
void grafcet12()
{

	if((X120 == 1))
	{
		X120 = 0;
		X121 = 1;
		return;
	}

	if((X121 == 1) && (Bluetooth_connect == true))
	{
		X121 = 0;
		X122 = 1;
		return;
	}

	/*if((X122 == 1) && (1))
	{
		X122 = 0;
		X123 = 1;
		return;
	}

	if((X123 == 1) && (1))
	{
		X123 = 0;
		X120 = 1;
		return;
	}*/
	if((X122 == 1) && Distance && Time)
	{
		X122 = 0;
		X120 = 1;
		return;
	}

}
void grafcet2()
{

	if((X20 == 1) && (Distance && Time))
	{
		X20 = 0;
		X21 = 1;
		return;
	}

	if((X21 == 1) && (Pace && Speed))
	{
		X21 = 0;
		X22 = 1;
		return;
	}

	if((X22 == 1) && (1))
	{
		X22 = 0;
		X20 = 1;
		return;
	}

}
void grafcet21()
{

	if((X210 == 1) && (Distance && Time))
	{
		X210 = 0;
		X211 = 1;
		return;
	}

	if((X211 == 1) && (Pace))
	{
		X211 = 0;
		X212 = 1;
		return;
	}

	if((X212 == 1) && (Acc && Gyro ))
	{
		X212 = 0;
		X213 = 1;
		X214 = 1;
		X215 = 1;
		return;
	}

	if((X213 == 1) && (Speed))
	{
		X213 = 0;
		X212 = 1;
		return;
	}

	if((X214 == 1)&& (X215 == 1))
	{
		X214 = 0;
		X215 = 0;
		X216 = 1;
		return;
	}

	if((X216 == 1) && (CompletedDistance))
	{
		X216 = 0;
		X212 = 1;
		return;
	}

}
void grafcet22()
{

	if(X220 == 1)
	{
		if(Pace>=Speed)
		{
			X220 = 0;
			X221 = 1;
		}
		else if( Pace<Speed)
		{
			X220 = 0;
			X222 = 1;
		}
		return;
	}

	if((X221 == 1) && (1))
	{
		X221 = 0;
		X220 = 1;
		return;
	}

	if((X222 == 1) && (1))
	{
		X222 = 0;
		X220 = 1;
		return;
	}

}


void datapath0()
{
	if(X0 == 1) action0();
	if(X1 == 1) InitialSetupModule();
	if(X2 == 1) SignalProcessingAndSpeedFeedbackModule();
	if(X3 == 1) DisplayData();
}


void datapath1()
{
	if(X10 == 1)
		action10();
	if(X11 == 1)
		InitialPaceModule();
	if(X12 == 1)
		BluetoothTransmissionModule();
}
/*void datapath11()
{
	if(X110 == 1)
	action110();
	if(X111 == 1)
	GetTotalRunningDistance ();
	if(X112 == 1)
	GetDefaultTime();
}*/

void datapath12()
{
	if(X120 == 1)
	action120();
	if(X121 == 1)
	SetupConnectionBluetooth();
	/*if(X122 == 1)
	SendDistanceTimebyCellphone();
	if(X123 == 1)
	GetDistanceTimebyDevice();*/
	if(X122 == 1) GetDistanceTimebyDevice();
}
void datapath2()
{
	if(X20 == 1)
	action20();
	if(X21 == 1)
	SignalProcessingModule();
	if(X22 == 1)
	SpeedFeedbackModule();
}
void datapath21()
{
	if(X210 == 1)
	action210();
	if(X211 == 1)
	CalculatePace();
	if(X212 == 1)
	ReadAccelerometerGyroscope();
	if(X213 == 1)
	CalculateSpeed();
	if(X214 == 1)
	CalculateStep();
	if(X215 == 1)
	CalculateStride();
	if(X216 == 1)
	CalculateDistance();
}
void datapath22()
{
	if(X220 == 1)
	action220();
	if(X221 == 1)
	LongVibration();
	if(X222 == 1)
	ShortVibration();
}
void action0()
{
	Serial.println("action0 activate !!\n");
}


void InitialSetupModule()
{
	Serial.println("InitialSetupModule activate !!\n");
	datapath1();
	grafcet1();
	printf("X10 = %d, X11 = %d, X12 = %d\n",X10 ,X11 ,X12 );
}


void SignalProcessingAndSpeedFeedbackModule()
{
	Serial.println("SignalProcessingAndSpeedFeedbackModule activate !!\n");
	datapath2();
	grafcet2();
	printf("X20 = %d,X21 = %d,X22 = %d\n",X20 ,X21 ,X22 );
}
void DisplayData()
{
	Serial.println("DisplayData activate !!\n");
}
void action10()
{
	Serial.println("action10 activate !!\n");
}
void InitialPaceModule()
{
	Serial.println("InitialPaceModule activate !!\n");
	//datapath11();
	//grafcet11();
	//printf("X110 = %d,X111 = %d,X112 = %d,X113 = %d\n",X110 ,X111 ,X112, X113 );
}
void BluetoothTransmissionModule()
{
	Serial.println("BluetoothTransmissionModule activate !!\n");
	datapath12();
	grafcet12();
	//printf("X120 = %d,X121 = %d,X122 = %d,X123 = %d\n",X120 ,X121 ,X122 ,X123 );
  printf("X120 = %d,X121 = %d,X122 = %d\n",X120 ,X121 ,X122 );

}

/*void action110()
{
	printf("action110 activate !!\n");
}


void GetTotalRunningDistance ()
{

	printf("GetTotalRunningDistance  activate !!\n");
	
}


void GetDefaultTime()
{
	printf("GetDefaultTime activate !!\n");
}*/


void action120()
{
	Serial.println("action120 activate !!\n");
}
void SetupConnectionBluetooth()
{
	Serial.println("SetupConnectionBluetooth activate !!\n");
	Serial.println("Starting BLE Server");
	
	class MyServerCallbacks: public BLEServerCallbacks {
		void onConnect(BLEServer* pServer) {
			Serial.println("Client connected");
			//pCharacteristic->setValue("hello client!");
			//pCharacteristic->notify();
			Bluetooth_connect = true;
		};
		void onDisconnect(BLEServer* pServer) {
			Serial.println("Client disconnected");
		}
	};

	BLEDevice::init("MyESP32");
	pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());
	//pServer->start();

	
}
/*void SendDistanceTimebyCellphone()
{
	printf("SendDistanceTimebyCellphone activate !!\n");
}*/
void GetDistanceTimebyDevice()
{
	Serial.println("GetDistanceTimebyDevice activate !!\n");

	class MyCharacCallbacks: public BLECharacteristicCallbacks {
		void onWrite(BLECharacteristic* pCharacteristic){
			std::string value = pCharacteristic->getValue();
			Serial.println(value.c_str());
			if(value.find("Distance")==0){
				Distance = stof(value.substr(10, value.size()-13));
				Serial.println(Distance);
			}
			if(value.find("Time")==0){
				Time = stof(value.substr(6, value.size()-11));
				Serial.println(Time);
			}
		}
	};
	pService = pServer->createService(SERVICE_UUID);
	pCharacteristic = pService->createCharacteristic(
											CHARACTERISTIC_UUID,
											BLECharacteristic::PROPERTY_READ |
											BLECharacteristic::PROPERTY_WRITE |
											BLECharacteristic::PROPERTY_NOTIFY |
											BLECharacteristic::PROPERTY_INDICATE
										);

	pCharacteristic->addDescriptor(new BLE2902());
	pCharacteristic->setCallbacks(new MyCharacCallbacks());
	pService->start();


	BLEAdvertising *pAdvertising = pServer->getAdvertising();
	pAdvertising->addServiceUUID(pService->getUUID());
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
	pAdvertising->setMinPreferred(0x12);

	pAdvertising->start();

	Serial.println("Characteristic defined!");
}


void action20()
{
	Serial.println("action20 activate !!\n");
}
void SignalProcessingModule()
{
	Serial.println("SignalProcessingModule activate !!\n");
	datapath21();
	grafcet21();
	printf("X210 = %d,X211 = %d,X212 = %d,X213 = %d,X214 = %d,X215 = %d,X216 = %d\n",X210 ,X211 ,X212 ,X213 ,X214 ,X215 ,X216 );
}
void SpeedFeedbackModule()
{
	Serial.println("SpeedFeedbackModule activate !!\n");
	datapath22();
	grafcet22();
	printf("X220 = %d,X221 = %d,X222 = %d\n",X220 ,X221 ,X222 );
}
void action210()
{
	Serial.println("action210 activate !!\n");
}
void CalculatePace()
{
	Serial.println("CalculatePace activate !!\n");
}
void ReadAccelerometerGyroscope()
{
	Serial.println("ReadAccelerometerGyroscope activate !!\n");
}
void CalculateSpeed()
{
	Serial.println("CalculateSpeed activate !!\n");
}
void CalculateStep()
{
	Serial.println("CalculateStep activate !!\n");
}
void CalculateStride()
{
	Serial.println("CalculateStride activate !!\n");
}
void CalculateDistance()
{
	Serial.println("CalculateDistance activate !!\n");
}
void action220()
{
	Serial.println("action220 activate !!\n");
}
void LongVibration()
{
	Serial.println("LongVibration activate !!\n");
}
void ShortVibration()
{
	Serial.println("ShortVibration activate !!\n");
}
