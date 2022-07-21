#include <ESP8266WiFi.h>// This library is for the wifi routine
#include <ESP8266WebServer.h>// This library is for the web server
#include <Wire.h>  // This library allows you to communicate with I2C devices.
#include <LiquidCrystal_I2C.h> //This library is for the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*Put your SSID & Password*/
const char* ssid = "Mandip's Iphone";  // Enter SSID here
const char* password = "123456789";  //Enter Password here

ESP8266WebServer server(80);

// Pins where IR_sensors are connected
#define parking_slot_1_pin D5
#define parking_slot_2_pin D6
#define parking_slot_3_pin D7
#define parking_slot_4_pin D8

//Variable declearation
int parking_slot_1 =0;
int parking_slot_2 =0;
int parking_slot_3 =0;
int parking_slot_4 =0;

// Setup fuction --> it runs only when staring Node MCU or if its reset
void setup() {
  
  Serial.begin(115200); //baud rate for serial communication

  //pin behaviour defination
  
  pinMode(parking_slot_1_pin, INPUT);
  pinMode(parking_slot_2_pin, INPUT);
  pinMode(parking_slot_3_pin, INPUT);
  pinMode(parking_slot_4_pin, INPUT);
  delay(100);
  
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  INITIALIZING");
  lcd.setCursor(0, 1);      
  lcd.print(">>>>>");
  delay(2000);
            
  // Connect to wifi network
  Serial.println(" Connecting to ");
  Serial.println(ssid);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Connecting to");
  lcd.setCursor(0, 1);      
  lcd.print(ssid);
  delay(2000);
            

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Connected to");
  lcd.setCursor(0, 1);      
  lcd.print(  ssid);
  delay(2000);
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP Address:");
  lcd.setCursor(0, 1);      
  lcd.print(WiFi.localIP());
  delay(2000);
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  //Server initialize
  server.begin();
  Serial.println("HTTP server started");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  HTTP SERVER");
  lcd.setCursor(0, 1);      
  lcd.print("   STARTED !!!");
  delay(2000);

}
void loop() {
  
  server.handleClient();

    read_ir();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Free P-Slot: ");
  lcd.setCursor(0, 1);
  if(parking_slot_1 ==1 && parking_slot_2 ==1 && parking_slot_3 ==1 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("0");
    lcd.setCursor(0, 1);
    lcd.print("NO SLOT AVAILABLE");
  }

    else if(parking_slot_1 ==1 && parking_slot_2 ==1 && parking_slot_3 ==1 && parking_slot_4 ==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("1");
    lcd.setCursor(0, 1);
    lcd.print("-----4-----");
  }

      else if(parking_slot_1 ==1 && parking_slot_2 ==1 && parking_slot_3 ==0 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("1");
    lcd.setCursor(0, 1);
    lcd.print("-----3-----");
  }

        else if(parking_slot_1 ==1 && parking_slot_2 ==0 && parking_slot_3 ==1 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("1");
    lcd.setCursor(0, 1);
    lcd.print("-----2-----");
  }

          else if(parking_slot_1 ==0 && parking_slot_2 ==1 && parking_slot_3 ==1 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("1");
    lcd.setCursor(0, 1);
    lcd.print("-----1-----");
  }

            else if(parking_slot_1 ==1 && parking_slot_2 ==1 && parking_slot_3 ==0 && parking_slot_4 ==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("2");
    lcd.setCursor(0, 1);
    lcd.print("---3---4-----");
  }

              else if(parking_slot_1 ==1 && parking_slot_2 ==0 && parking_slot_3 ==1 && parking_slot_4==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("2");
    lcd.setCursor(0, 1);
    lcd.print("---2---4-----");
  }

                else if(parking_slot_1 ==0 && parking_slot_2 ==1 && parking_slot_3 ==1 && parking_slot_4 ==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("2");
    lcd.setCursor(0, 1);
    lcd.print("---1---4-----");
  }

                  else if(parking_slot_1 ==1 && parking_slot_2 ==0 && parking_slot_3 ==0 && parking_slot_4==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("2");
    lcd.setCursor(0, 1);
    lcd.print("---2---3-----");
  }

                    else if(parking_slot_1 ==0 && parking_slot_2 ==1 && parking_slot_3 ==0 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("2");
    lcd.setCursor(0, 1);
    lcd.print("---1---3-----");
  }

    else if(parking_slot_1 ==0 && parking_slot_2 ==0 && parking_slot_3 ==1 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("2");
    lcd.setCursor(0, 1);
    lcd.print("---1---2-----");
  }

    else if(parking_slot_1 ==0 && parking_slot_2 ==0 && parking_slot_3 ==0 && parking_slot_4 ==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("3");
    lcd.setCursor(0, 1);
    lcd.print("--1---2---3--");
  }

     else if(parking_slot_1 ==1 && parking_slot_2 ==0 && parking_slot_3 ==0 && parking_slot_4 ==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("3");
    lcd.setCursor(0, 1);
    lcd.print("--2---3---4--");
  }

       else if(parking_slot_1 ==0 && parking_slot_2 ==0 && parking_slot_3 ==1 && parking_slot_4 ==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("3");
    lcd.setCursor(0, 1);
    lcd.print("--1---2---4--");
  }

         else if(parking_slot_1 ==0 && parking_slot_2 ==1 && parking_slot_3 ==0 && parking_slot_4 ==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("3");
    lcd.setCursor(0, 1);
    lcd.print("--1---3---4--");
  }

           else if(parking_slot_1 ==0 && parking_slot_2 ==0 && parking_slot_3 ==0 && parking_slot_4==0)
  {
    lcd.setCursor(14, 0);
    lcd.print("4");
    lcd.setCursor(0, 1);
    lcd.print("--1--2--3--4--");
  }
  delay(200);
  
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(parking_slot_1,parking_slot_2,parking_slot_3,parking_slot_4)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

// function to create basic website

String SendHTML(int PS1,int PS2, int PS3, int PS4){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>SMART PARKING SYSTEM</title>\n";
  ptr +="<meta http-equiv=\"refresh\" content=\"5\">\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px; background-color:powderblue;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="body {background-image: url(https://cdn.wallpapersafari.com/32/10/5FScLP.jpg); background-repeat:no-repeat; background-attachment: fixed; background-position: center; background-size: 1400px 900px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body >\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1 style=\"background-color:Grey;\" > <b style=\"color:white\">SMART PARKING SYSTEM</b></h1>\n";
  
  ptr +="<p>Parking Slot 1: ";
  if(parking_slot_1==0)
  {
     ptr +="<b style=\"color:green\";> AVAILABLE!!! </b></p>";
  }
  else
  {
    ptr +="<b style=\"color:red\";> OCCUPIED!!! </b></p>";
  }

    ptr +="<p>Parking Slot 2: ";
  if(parking_slot_2==0)
  {
     ptr +="<b style=\"color:green\";> AVAILABLE!!! </b></p>";
  }
  else
  {
    ptr +="<b style=\"color:red\";> OCCUPIED!!! </b></p>";
  }

      ptr +="<p>Parking Slot 3: ";
  if(parking_slot_3==0)
  {
     ptr +="<b style=\"color:green\";> AVAILABLE!!! </b></p>";
  }
  else
  {
    ptr +="<b style=\"color:red\";> OCCUPIED!!! </b></p>";
  }

      ptr +="<p>Parking Slot 4: ";
  if(parking_slot_4==0)
  {
     ptr +="<b style=\"color:green\";> AVAILABLE!!! </b></p>";
  }
  else
  {
    ptr +="<b style=\"color:red\";> OCCUPIED!!! </b></p>";
  }
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


//function to read_ ir calues
void read_ir()
{
  parking_slot_1= !digitalRead(parking_slot_1_pin);
  parking_slot_2= !digitalRead(parking_slot_2_pin);
  parking_slot_3= !digitalRead(parking_slot_3_pin);
  parking_slot_4= !digitalRead(parking_slot_4_pin); 
}
