
#include <stdio.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "MPU9250.h"

#define SERVICE_UUID        "022d75fe-9e7d-11ee-8c90-0242ac120002"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define pi 3.14
#define g 9.81

int X0 = 1, X1 = 0, X10 = 1, X11 = 0;
//int X110 = 1, X111 = 0, X112 = 0;
//int X113 = 0;
int X12 = 0, X120 = 1, X121 = 0, X122 = 0;//, X123 = 0;
int X2 = 0, X20 = 1, X21 = 0;
int X210 = 1, X211 = 0, X212 = 0, X213 = 0, X214 = 0, X215 = 0, X216 = 0;
int X22 = 0, X220 = 1, X221 = 0, X222 = 0, X3 = 0;

//initial values
float Distance = 0; // km
float Time = 0; // min
float CompletedDistance = 0; // km
float Speed = 0; // km/hr
int Step = 0;
float Stride = 0.0; // cm
bool Pace = false;
bool Acc = false, Gyro = false;

// 藍芽傳輸參數
bool Bluetooth_connect = false;
bool service_started = false;
BLECharacteristic *pCharacteristic;
BLEService *pService;
BLEServer *pServer;
BLEAdvertising *pAdvertising;

// 九軸感測器參數
MPU9250 mpu; 
int I2C_SCL = 47;
int I2C_SDA = 21;

// 配速計算參數
int pace_seconds = 0;
float total_seconds = 0.0;
int hh = 0, mm = 0, ss = 0;

// 速度&步數&步幅 計算參數
float Acc_x = 0.0, Acc_y=0.0, Acc_z=0.0;
float V_x = 0.0, V_y = 0.0, V_z = 0.0;
float theta_x=0.0, theta_y=0.0, theta_z=0.0;
float last_theta_x = 0.0, last_theta_y = 0.0, last_theta_z = 0.0;
float h = 160.0;
const float threshold_x = 5.0;  // X軸閾值
const float threshold_y = 5.0;  // Y軸閾值
const float threshold_z = 5.0;  // Z軸閾值
float Gyro_x = 0.0, Gyro_y=0.0, Gyro_z=0.0;


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
    // 藍芽設定
    BLEDevice::init("MyESP32");
    pServer = BLEDevice::createServer();
    pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
                    
    // 運動感測器初始化
    Wire.begin(I2C_SDA, I2C_SCL);
    delay(2000);
    static uint32_t lastTime = 0;
    if (!mpu.setup(0x68)){  // change to your own address
        while (1){
          Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
          delay(5000);
        }
    }
}
void loop()
{
    datapath0();
	  grafcet0();
  	//printf("X0 = %d,X1 = %d,X2 = %d,X3 = %d\n",X0 ,X1 ,X2 ,X3 );
  
  	delay(100);
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

	if((X12 == 1) && Distance && Time)
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

  if((X213 == 1) && (X214 == 1)&& (X215 == 1) && (Step && Stride)){
    X213 = 0;
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
	//Serial.println("action0 activate !!\n");
}


void InitialSetupModule()
{
	//Serial.println("InitialSetupModule activate !!\n");
	datapath1();
	grafcet1();
	//printf("X10 = %d, X11 = %d, X12 = %d\n",X10 ,X11 ,X12 );
}


void SignalProcessingAndSpeedFeedbackModule()
{
	Serial.println("SignalProcessingAndSpeedFeedbackModule activate !!\n");
	datapath2();
	grafcet2();
	//printf("X20 = %d,X21 = %d,X22 = %d\n",X20 ,X21 ,X22 );
}
void DisplayData()
{
	Serial.println("DisplayData activate !!\n");
}
void action10()
{
	//Serial.println("action10 activate !!\n");
}
void InitialPaceModule()
{
	//Serial.println("InitialPaceModule activate !!\n");
	//datapath11();
	//grafcet11();
	//printf("X110 = %d,X111 = %d,X112 = %d,X113 = %d\n",X110 ,X111 ,X112, X113 );
}
void BluetoothTransmissionModule()
{
	//Serial.println("BluetoothTransmissionModule activate !!\n");
	datapath12();
	grafcet12();
	//printf("X120 = %d,X121 = %d,X122 = %d,X123 = %d\n",X120 ,X121 ,X122 ,X123 );
  //printf("X120 = %d,X121 = %d,X122 = %d\n",X120 ,X121 ,X122 );

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
	//Serial.println("action120 activate !!\n");
}
void SetupConnectionBluetooth()
{
	//Serial.println("SetupConnectionBluetooth activate !!\n");
	
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

	pServer->setCallbacks(new MyServerCallbacks());

  pAdvertising = pServer->getAdvertising();
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  pAdvertising->start();	
  Serial.println("Starting BLE Server");
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
			//Serial.println(value.c_str());
			if(value.find("Distance")==0){
				Distance = stof(value.substr(10, value.size()-13));
				printf("Distance: %.2f km\n",Distance);
			}
			if(value.find("Time")==0){
				Time = stof(value.substr(6, value.size()-11));
				printf("Time: %.2f mins\n",Time);
			}
		}
	};
	
	pCharacteristic->addDescriptor(new BLE2902());
	pCharacteristic->setCallbacks(new MyCharacCallbacks());
  if (!service_started) {
    pService->start();
    service_started = true;
  }
	pAdvertising->addServiceUUID(pService->getUUID());
}


void action20()
{
	//Serial.println("action20 activate !!\n");
}
void SignalProcessingModule()
{
	Serial.println("SignalProcessingModule activate !!\n");
	datapath21();
	grafcet21();
	//printf("X210 = %d,X211 = %d,X212 = %d,X213 = %d,X214 = %d,X215 = %d,X216 = %d\n",X210 ,X211 ,X212 ,X213 ,X214 ,X215 ,X216 );
}
void SpeedFeedbackModule()
{
	Serial.println("SpeedFeedbackModule activate !!\n");
	datapath22();
	grafcet22();
	//printf("X220 = %d,X221 = %d,X222 = %d\n",X220 ,X221 ,X222 );
}
void action210()
{
	//Serial.println("action210 activate !!\n");
}
void CalculatePace()
{
  Serial.println("CalculatePace activate !!\n");
  total_seconds = Time*60;
  pace_seconds = total_seconds / Distance;
  hh = pace_seconds / 3600;
  mm = (pace_seconds % 3600) / 60;
  ss = pace_seconds % 60;
  Pace = true;
}
void ReadAccelerometerGyroscope()
{
	Serial.println("ReadAccelerometerGyroscope activate !!\n");
  if (mpu.update()){
    // 加速計值
    Acc_x = mpu.getAccX();
    Acc_y = mpu.getAccY();
    Acc_z = mpu.getAccZ();
    Acc = true;
    // delete
    Serial.print("Acc: ");
    Serial.println(Acc_x);
    
    // 陀螺儀值
    Gyro_x = mpu.getGyroX();
    Gyro_y = mpu.getGyroY();
    Gyro_z = mpu.getGyroZ();
    Gyro = true;
  }
}
void CalculateSpeed()
{
	Serial.println("CalculateSpeed activate !!\n");
  V_x = Acc_x*2*g*0.01;
  V_y = Acc_y*2*g*0.01;
  V_z = Acc_z*2*g*0.01;
  Speed = sqrt(V_x*V_x + V_y*V_y + V_z*V_z)*3.6;  // km/hr
}
void CalculateStep()
{
	Serial.println("CalculateStep activate !!\n");
  // 加速度數據->變化角度
  theta_x = atan(Acc_x/sqrt(Acc_y*Acc_y + Acc_z*Acc_z))*180/pi;
  theta_y = atan(Acc_y/sqrt(Acc_x*Acc_x + Acc_z*Acc_z))*180/pi;
  theta_z = atan(sqrt(pow(Acc_x, 2) + pow(Acc_y, 2))/Acc_z)*180/pi;
  
  // 判斷角度變化
  if (abs(theta_x - last_theta_x) > threshold_x && 
      abs(theta_y - last_theta_y) > threshold_y && 
      abs(theta_z - last_theta_z) > threshold_z) {
        Step += 1;
  }
  // 更新
  last_theta_x = theta_x;
  last_theta_y = theta_y;
  last_theta_z = theta_z;
  // delete
  Serial.print("Step: ");
  Serial.println(Step);
}
void CalculateStride()
{
	Serial.println("CalculateStride activate !!\n");
  Stride = h*0.43; // cm
  // delete
  Serial.print("Stride: ");
  Serial.println(Stride);
}
void CalculateDistance()
{
	Serial.println("CalculateDistance activate !!\n");
  CompletedDistance = Step*Stride/100; // m
  // delete
  Serial.print("Distance: ");
  Serial.println(Distance);
//  Acc = false;
//  Gyro = false;
}
void action220()
{
	//Serial.println("action220 activate !!\n");
}

void LongVibration()
{
  Serial.println("LongVibration activate !!\n");
  digitalWrite(3,LOW);
  delay(1000);
  
  digitalWrite(3,HIGH);
  delay(1000);
 
  digitalWrite(3,LOW);
  delay(1000);
 
  digitalWrite(3,HIGH);
  delay(1000);
} // LongVibration()

void ShortVibration()
{
  Serial.println("ShortVibration activate !!\n");
  digitalWrite(3,LOW);
  delay(1000);
  
  digitalWrite(3,HIGH);
  delay(100);
 
  digitalWrite(3,LOW);
  delay(1000);
 
  digitalWrite(3,HIGH);
  delay(100); 
} // ShortVibration()