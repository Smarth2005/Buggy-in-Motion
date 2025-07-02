int ir1 = A0;
int ir2 = A1;
int pin = 4;
int l;
int r;
int count = 0;
unsigned long value=0;

const int trigPin = 13;
const int echoPin = 12;
int distance;
long duration;

void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);    
  pinMode(ir2, INPUT);
  pinMode(pin, INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);    
  pinMode(8,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void forward() {
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

void backward() {
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
}

void clockWise() {
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
}

void anticlockWise() {
  digitalWrite(5,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
}

void left() {
  digitalWrite(8,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

void right() {
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

void stop() {
  digitalWrite(8,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

long st = millis(), endt;
int flag = 0;

void loop() {
  if (Serial.read() == 'V' || flag == 1) {

    if (digitalRead(pin) > 0) {
      value = pulseIn(pin, HIGH);
      Serial.print("Value =");
      Serial.println(value);
      if (value > 3000 && value < 4000) {
        Serial.println("Gantry 1 Crossed");
        stop();
        delay(1000);
      }
      if (value > 2500 && value < 3000) {
        Serial.println("Gantry 2 Crossed");
        stop();
        delay(1000);
      }
      if (value > 500 && value < 1000) {
        Serial.println("Gantry 3 Crossed");
        stop();
        delay(1000);
      }
    }

    flag = 1;

    l = digitalRead(ir1);
    r = digitalRead(ir2);

   digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration*0.034/2;
    if(distance <= 15)
    {
      stop();
      delay(500);
    }

    if (l == 1 && r == 1) {
      forward();
    }
    if (l == 1 && r == 0) {
      right();
    }
    if (l == 0 && r == 1) {
      left();
    }
    if (l == 0 && r == 0) {
      endt = millis();

      if (endt - st > 1000) {
        count++;
        st = millis();
      }

      if (count == 1) {
        forward();
        Serial.print("Forward:");
        Serial.println(count);
      }

      if (count == 2) {
        left();
        Serial.print("Left:");
        Serial.println(count);
      }

      if (count == 3) {
        forward();
        Serial.print("Forward:");
        Serial.println(count);
      }

      if (count == 4) {
        forward();
        Serial.print("Forward:");
        Serial.println(count);
      }

      if (count == 5) {
        left();
        Serial.print("Left:");
        Serial.println(count);
        delay(430);
      }

      if (count == 6) {
        forward();
        Serial.print("Forward:");
        Serial.println(count);
      }

      if (count > 6) {
        stop();
        Serial.print("Stop:");
        Serial.println(count);
        flag = 0;
      }
    }
  }
}
