
//pin 5,13 TV불&스위치
const int buttonPin = 5;
const int ledPin = 13;

//pin 8,9 초음파센서
#define trigPin 8
#define echoPin 9



//스위치 상태 (1=off, 0=on)
boolean buttonStatus = HIGH;

int oneTimeFlag;

void setup()
{
        pinMode(buttonPin,INPUT);
        digitalWrite(buttonPin,HIGH);

        pinMode(ledPin,OUTPUT);
        
        Serial.begin(9600);
        
  //pin 12 밝기센서      
  pinMode(12,OUTPUT);
  //pin 4 거리센서
  pinMode(4,INPUT);      

  // 초음파센서
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}
void loop()
{

 
  //스위치 & LED출력
        if(digitalRead(buttonPin)==LOW)
        {
           if(oneTimeFlag==0)
           {
              oneTimeFlag = 1;
              buttonStatus = !buttonStatus;
           }
        }
        else {
          oneTimeFlag = 0;
        }
       
        digitalWrite(ledPin,buttonStatus);
        
        if (digitalRead(ledPin) == 1 ) {
          Serial.print("TV : ");
          Serial.println(digitalRead(ledPin));
          Serial.println("Turn on the television");
        }
        
        if (digitalRead(ledPin) == 0 ) {
          Serial.print("TV : ");
          Serial.println(digitalRead(ledPin));
          Serial.println("Turn off the television");
        }
        delay(10);
        
  //밝기센서 & LED출력
    int sensorValue= analogRead(A0);
  
    if( sensorValue < 800 && digitalRead(4) == HIGH) {
      digitalWrite(12, HIGH);
    } else {
      digitalWrite(12, LOW);
    }
      
      if (digitalRead(12) == 1 ) {
          Serial.print("Light : ");
          Serial.println(digitalRead(12));
          Serial.println("!! Living room light turns on !!" );
        }
      delay(100);  
  
  // 초음파센서
if(buttonStatus==HIGH) {
  
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1; 
  //Serial.println(distance);

  while (distance < 10) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("Too close, then turn off the TV");
    delay(5000);
    digitalWrite(ledPin, LOW);
    
  // distance 값 다시 계산ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1; 
    delay(1000);
  // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    
  } 

  delay(100);
 }
}




