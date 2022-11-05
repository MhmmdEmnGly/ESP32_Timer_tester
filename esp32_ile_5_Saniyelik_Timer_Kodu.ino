#define led 13

volatile int interruptCounter =0;
int totalInterruptCounter=0;

int toplamGecenSure=0;



hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 


void IRAM_ATTR Sayac() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
  
 
}
 

void setup() {
 
  Serial.begin(115200);
  //            0.indekssteki timer -> yani timer 1 i kullanıyoruz
  // 80MHZ = 80 000 000 /80 den yani 1milyon mikrosaniye yani 1 saniye
  // true de çalış demek
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &Sayac, true);
  timerAlarmWrite(timer, 500000, true);
  timerAlarmEnable(timer);
 

 pinMode(led, OUTPUT);
}
 
void loop() {
  int deger = digitalRead(led);

  if (interruptCounter > 0) {
 
    toplamGecenSure +=interruptCounter;

    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;

    

    Serial.print("An interrupt as occurred. Total number: ");
    Serial.println(totalInterruptCounter);

    digitalWrite(led,!deger);
 
  }

  else if(totalInterruptCounter >=3){
    totalInterruptCounter =0;
    Serial.println("Resim Cekiliyor...");
    Serial.println("Sayac 3 saniyeye ulasti.");
    Serial.println("Sayac sifirlaniyor....");

    Serial.print("Toplam Gecen sure : ");
    Serial.println(toplamGecenSure);

  }


}
