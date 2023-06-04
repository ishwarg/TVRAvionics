#include <Servo.h>

Servo esc_1;  // create servo object to control the PWM signal


void setup() {
  esc_1.attach(9);  // make sure to use a PWM capable pin
  pinMode(4, INPUT);
  Serial.begin(9600);
  Serial.println(digitalRead(4));


}

void loop() {  
  Serial.println("about to go max");
  Serial.println(" Press H to start");
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0) // did something come in?
      if(Serial.read() == 'H') // is that something the char G?
        break;
  }
  Serial.println(" max");
  //delay(10000);
  //Serial.println("about to go max");

  set_esc_power(esc_1, 100);
  //delay(10000);

  Serial.println(" Press L to end");
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0) // did something come in?
      if(Serial.read() == 'L') // is that something the char G?
        break;
  }
  //Serial.println("going low");
  //delay(10000);
  
  set_esc_power(esc_1, 0);

  while (true){
    Serial.println("Chilling");
  }
  


  // set_esc_power(esc_1, 5);
  // delay(6000) ;
  // set_esc_power(esc_1, 40);
  // delay(500) ;
  // set_esc_power(esc_1, 50);
  // delay(500) ;
  // set_esc_power(esc_1, 40);
  // delay(500) ;
  // set_esc_power(esc_1, 20);
  // delay(500) ;
}

void set_esc_power (Servo esc, int power){
  power = constrain(power, 0, 100);
  int signal_min = 900;
  int signal_max = 2400;
  int signal_output = map(power, 0, 100, signal_min, signal_max); //map(value, fromLow, fromHigh, toLow, toHigh)
  esc.writeMicroseconds(signal_output);
}