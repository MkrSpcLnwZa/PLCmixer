//rc pwm reciever input
#define CH1 3
#define CH2 4
//motor A peripherals
#define motorApwm 5
#define motorAdir 6
#define motorAbrake 7
#define motorAstop 8
//motor B peripherals
#define motorBpwm 9
#define motorBdir 10
#define motorBbrake 11
#define motorBstop 12

int ch1Value;
int ch2Value;

int pwmAval = 0;
int pwmBval = 0;

int movstat = 0;

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  
  pinMode(motorApwm, OUTPUT);
  pinMode(motorAdir, OUTPUT);
  pinMode(motorAbrake, OUTPUT);
  pinMode(motorAstop, OUTPUT);
  
  pinMode(motorApwm, OUTPUT);
  pinMode(motorAdir, OUTPUT);
  pinMode(motorAbrake, OUTPUT);
  pinMode(motorAstop, OUTPUT);

  Serial.println("system initiated");
}

void loop() {
  // put your main code here, to run repeatedly:
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);

  if((-20<=ch1Value<=20)&&(-20<=ch2Value<=20))
  { 
     Serial.println("stopsssssss");
     analogWrite(motorApwm,0);
     digitalWrite(motorAdir, LOW);
     digitalWrite(motorAbrake, HIGH);
      
     analogWrite(motorBpwm,0);
     digitalWrite(motorBdir, LOW);
     digitalWrite(motorBbrake, HIGH);
     digitalWrite(motorAstop, HIGH);
     digitalWrite(motorBstop, HIGH);
//    if(movstat!=0){
//      Serial.println("stopsssssss");
//      analogWrite(motorApwm,0);
//      digitalWrite(motorAdir, LOW);
//      digitalWrite(motorAbrake, HIGH);
//      
//      analogWrite(motorBpwm,0);
//      digitalWrite(motorBdir, LOW);
//      digitalWrite(motorBbrake, HIGH);
//  
//      delay(300);
//      digitalWrite(motorAstop, HIGH);
//      digitalWrite(motorBstop, HIGH);
//      movstat = 0;
//    }
  }
  if((20<ch1Value)&&(20<ch2Value))
  {
    movstat = 1;
    Serial.println("Forward");
    analogWrite(motorApwm,ch1Value);
    digitalWrite(motorAdir, LOW);
    digitalWrite(motorAbrake, LOW);
    digitalWrite(motorAstop, LOW);
    
    analogWrite(motorBpwm,ch2Value);
    digitalWrite(motorBdir, LOW);
    digitalWrite(motorBbrake, LOW);
    digitalWrite(motorBstop, LOW);

  }
  if((ch1Value<-20)&&(ch2Value<-20))
  {
    movstat = 1;
    Serial.println("Reverse");
    analogWrite(motorApwm,abs(ch1Value));
    digitalWrite(motorAdir, HIGH);
    digitalWrite(motorAbrake, LOW);
    digitalWrite(motorAstop, LOW);
    
    analogWrite(motorBpwm,abs(ch2Value));
    digitalWrite(motorBdir, HIGH);
    digitalWrite(motorBbrake, LOW);
    digitalWrite(motorBstop, LOW);
  }
  if((ch1Value<-20)&&(20<ch2Value))
  {
    movstat = 1;
    Serial.println("Turn Left");
    analogWrite(motorApwm,abs(ch1Value));
    digitalWrite(motorAdir, HIGH);
    digitalWrite(motorAbrake, LOW);
    digitalWrite(motorAstop, LOW);
    
    analogWrite(motorBpwm,abs(ch2Value));
    digitalWrite(motorBdir, LOW);
    digitalWrite(motorBbrake, LOW);
    digitalWrite(motorBstop, LOW);
  }
  if((20<ch1Value)&&(ch2Value<-20))
  {
    movstat = 1;
    Serial.println("Turn Right");
    analogWrite(motorApwm,abs(ch1Value));
    digitalWrite(motorAdir, LOW);
    digitalWrite(motorAbrake, LOW);
    digitalWrite(motorAstop, LOW);
    
    analogWrite(motorBpwm,abs(ch2Value));
    digitalWrite(motorBdir, HIGH);
    digitalWrite(motorBbrake, LOW);
    digitalWrite(motorBstop, LOW);
  }
  
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.println();
}
