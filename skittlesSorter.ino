#include <Servo.h>

#define S0 0
#define S1 1
#define S2 4
#define S3 3
#define sensorOut 5

Servo plate;
Servo slide;
int frequency = 0;
int f_array[3];
int count = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  plate.attach(12);
  slide.attach(11);
  
  Serial.begin(9600);
}

void rotatePlate(){
  plate.write(1440); // 90 degree
  delay(518);
  plate.write(1490); // still
}

void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,72,255,0);
  f_array[0] = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30,90,255,0);
  f_array[1] = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,70,255,0);
  f_array[2] = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  | ");

  int R = f_array[0];
  int G = f_array[1];
  int B = f_array[2];

  if((R>335) && (R<342) && (G>322) && (G<324) && (B>310) && (B<320)){
    Serial.println("This is RED");
    slide.write(110);
  }
  else if((R>328) && (R<337) && (G>322) && (G<329) && (B>320) && (B<330)){
    Serial.println("This is BLUE");
    slide.write(70);
  }
  else if((R>335) && (R<342) && (G>330) && (G<336) && (B>316) && (B<324)){
    Serial.println("This is GREEN");
    slide.write(130);
  }
//  else if((R>329) && (R<337) && (G>322) && (G<328) && (B>316) && (B<318)){
//    Serial.println("This is PURPLE");
//    slide.write(110);
//  }
  else{
    Serial.println("COLOR ERROR");
    slide.write(90);
  }
  rotatePlate();
  delay(2000);
}
