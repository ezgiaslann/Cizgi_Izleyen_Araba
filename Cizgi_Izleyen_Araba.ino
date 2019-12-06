 const int inA = 2; //sağ teker
const int in1 = 3;
const int in2 = 4;

const int in3 = 5; //sol teker1
const int in4 = 6;
const int inB = 7;

int trigPin = 11; /* Sensorun trig pini Arduinonun 7 numaralı ayağına bağlandı */
int echoPin = 12;  /* Sensorun echo pini Arduinonun 6 numaralı ayağına bağlandı */

const int buzzerPin = 7;

#define solSensor 10
#define ortaSensor 9
#define sagSensor 8
int sayac = 0;
char komut;

long  uzaklik=0;
long sayi=0;
long sure=0;
int sagsensor, solsensor, ortasensor;


void setup() {
  pinMode(inA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(inB, OUTPUT);

  pinMode(sagSensor, INPUT);
  pinMode(solSensor, INPUT);
  pinMode(ortaSensor, INPUT);

  pinMode(trigPin, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin, INPUT); /* echo pini giriş olarak ayarlandı */
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  sayi = random(0, 10);
  Serial.println("çalışıyo");
  if (Serial.available() > 0 ) {
    komut = Serial.read();

    
    if (komut == 'W') {
      if (sayac == 0) {
        Serial.println(komut);
        singBuzzer(); // 5 SN boyunca buzzer ötecek
        Serial.println("if");
        sagsensor = digitalRead(sagSensor);
        solsensor = digitalRead(solSensor);
        ortasensor = digitalRead(ortaSensor);
        while (!(sagsensor == 0 && ortasensor == 0 && solsensor == 0)) {
          kontroller();
          sayac ++;
        
        }
      }
      Serial.println("while den çıktı"  );
      sagsensor = digitalRead(sagSensor);
        solsensor = digitalRead(solSensor);
        ortasensor = digitalRead(ortaSensor);
      if (sayac > 0) {
        Serial.println(sayac);
        sagsensor = digitalRead(sagSensor);
        solsensor = digitalRead(solSensor);
        ortasensor = digitalRead(ortaSensor);
        while(true)
        { 
          komut = Serial.read();
          if(komut=='U')
          {
            break;
          }
         else
          kontroller2();   
        }
      }
    }
  
    if(komut=='U')
    {
      Serial.println("bluetooth");
      komut = Serial.read();
      while(true)
      {
         bluetooth();
         if(komut=='u')
         {
          break;
         }
      }
      // Serial.println(komut);
    }
  }
}
void singBuzzer()
{
  int i = 0;
  for (i; i < 5; i++)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);

  }

}

void ileri() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 90);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 90);
  Serial.println("ileri");

}

void sag () {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 100);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(inB, 100);
  Serial.println("sag");
}
void sol () {

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(inA, 100);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 100);
  Serial.println("sol");
}

void geri() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(inA, 80);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(inB, 80);
  Serial.println("geri");
}

void dur() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 0);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 0);
  Serial.println("dur");
}
void solCapraz() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 30);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 70);
  Serial.println("solCapraz");

}
void sagCapraz() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 70);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 30);
  Serial.println("sagCapraz");
}


void geriSagcapraz() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(inA, 200);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(inB, 150);
  Serial.println("geri sag capraz");

}
void geriSolcapraz() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(inA, 150);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(inB, 200);
  Serial.println("geri sol capraz");
}


void cizgiAra() {

  solCapraz();
     sagsensor = digitalRead(sagSensor);
  solsensor = digitalRead(solSensor);
  ortasensor = digitalRead(ortaSensor);
  Serial.println("cizgi ara");
}

void kontroller() {

  sagsensor = digitalRead(sagSensor);
  solsensor = digitalRead(solSensor);
  ortasensor = digitalRead(ortaSensor);


  if (sagsensor == 1 && ortasensor == 0 && solsensor == 0) {
    sag();
  }
  else if (sagsensor == 0 && ortasensor == 1 && solsensor == 0) {
    ileri();

  }
  else if (sagsensor == 0 && ortasensor == 0 && solsensor == 1) {
    sol();

  }
  else if (sagsensor == 0 && ortasensor == 1 && solsensor == 1) {
    solCapraz();
  }
  else if (sagsensor == 1 && ortasensor == 1 && solsensor == 0) {
    sagCapraz();
  }

  else if (sagsensor == 1 && ortasensor == 1 && solsensor == 1) {
    ileri();
  }
  else if (sagsensor == 1 && ortasensor == 0 && solsensor == 1) {
    
  }
}

void kontroller2() {
  digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

  sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = sure / 29.1 / 2; //ölçülen süre uzaklığa çevriliyor

  Serial.println(uzaklik);
  Serial.println("kontroller2");
  sagsensor = digitalRead(sagSensor);
  solsensor = digitalRead(solSensor);
  ortasensor = digitalRead(ortaSensor);
  if (uzaklik < 15) // Uzaklık 15'den küçük ise,
  {
    dur();

  }

   else if (sagsensor == 1 && ortasensor == 0 && solsensor == 0) {
    sag();
  }
  else if (sagsensor == 0 && ortasensor == 1 && solsensor == 0) {
    ileri();

  }
  else if (sagsensor == 0 && ortasensor == 0 && solsensor == 1) {
    sol();

  }
  else if (sagsensor == 0 && ortasensor == 1 && solsensor == 1) {
    solCapraz();
  }
  else if (sagsensor == 1 && ortasensor == 1 && solsensor == 0) {
    sagCapraz();
  }

  else if (sagsensor == 1 && ortasensor == 1 && solsensor == 1) {
    ileri();
  }
  else if (sagsensor == 1 && ortasensor == 0 && solsensor == 1) {
    
  }
  else if (sagsensor == 0 && ortasensor == 0 && solsensor == 0) {
    cizgiAra();
  }
 
}

void bluetooth()
{
  if (Serial.available() > 0) {
    komut = Serial.read();
    dur();
    switch (komut) {
      case 'F':
        ileri();
        break;
      case 'B':
        geri();
        break;
      case 'L':
        sol();
        break;
      case 'R':
        sag();
        break;
      case 'J':
        bgerisagcapraz();
        break;
      case 'H':
        bgerisolcapraz();
        break;
      case'I':
        bsagCapraz();
        break;
      case 'G':
        bsolCapraz();
        break;


    }
  }
}
void bsolCapraz() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 100);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 255);
  Serial.println("solCapraz");

}
void bsagCapraz() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(inA, 255);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(inB, 100);
  Serial.println("sagCapraz");
}


void bgerisagcapraz() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(inA, 255);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(inB, 100);
  Serial.println("geri sag capraz");

}
void bgerisolcapraz() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(inA, 80);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(inB, 255);
  Serial.println("geri sol capraz");
}
