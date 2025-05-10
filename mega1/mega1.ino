#include <Servo.h>
#include <Adafruit_NeoPixel.h>

const int ena = 2;
const int in1 = 3;
const int in2 = 4;
const int in3 = 5;
const int in4 = 6;
const int enb = 7;

const int sayac_bildirim = A8;
const int ceza_bildirim = A9;
const int kilit_sinyal = A10;
const int bolge_sinyal = A11;
const int ceza_tokatla_sinyal = A12;

const int sag = 35;
const int sol = 33;
const int yan = 31;

Servo ceza_kapak, rakip_kapak, bizim_kapak;

const int s0 = 46;
const int s1 = 44;
const int s2 = 50;
const int s3 = 48;
const int out = 52;


float kirmizi = 0, mavi = 0;
byte bolge = 0, duvarla_isim_var = 0;

int kirmizi_veriler[4] = { 0, 0, 0, 0 };
int mavi_veriler[4] = { 0, 0, 0, 0 };


Adafruit_NeoPixel serit(200, 11, NEO_GRB + NEO_KHZ800);  // Tanımlamalar yapılıyor

void setup() {
  Serial.begin(9600);

  ceza_kapak.attach(10);
  rakip_kapak.attach(9);
  bizim_kapak.attach(8);

  serit.begin();             // Kütüphane başlatılıyor
  serit.clear();             // LED'ler temizleniyor
  serit.setBrightness(200);  // LED parlaklığı ayarlanıyor

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(sag, INPUT);
  pinMode(sol, INPUT);
  pinMode(yan, INPUT);
  pinMode(sayac_bildirim, INPUT);
  pinMode(ceza_bildirim, INPUT);
  pinMode(kilit_sinyal, OUTPUT);
  pinMode(bolge_sinyal, OUTPUT);
  pinMode(ceza_tokatla_sinyal, OUTPUT);

  pinMode(32, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(26, OUTPUT);
  digitalWrite(32, LOW);
  digitalWrite(30, LOW);
  digitalWrite(28, LOW);
  digitalWrite(26, LOW);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  ceza_kapak.write(0);
  rakip_kapak.write(90);  //bu ters
  bizim_kapak.write(13);  //bu normal hali

  bolge = digitalRead(A0);
  digitalWrite(bolge_sinyal, bolge);
  // ***** Bölge Tespiti ********
  if (bolge == 1) {
    kirmizi_yak();
  } else {
    mavi_yak();
  }
  analogWrite(ena, 130);
  analogWrite(enb, 130);
  while(digitalRead(sag) == 0)
  {
    
  }
}

void loop() {
    if (digitalRead(sayac_bildirim) == 1)  //KENDİ TOPUMUZUN SAYACI DOLMUŞ
    {
    //DUVAR TAKİBİ VE KENDİ BÖLGEMİZE BOŞALTMA
    digitalWrite(kilit_sinyal, HIGH);
    dur();
    delay(2000);
    duvar_bul();
    duvarla_isim_var = 1;
    while (duvarla_isim_var == 1) {
      duvar_takip(1);
    }
    digitalWrite(kilit_sinyal, LOW);
    delay(1000);
    } else if (digitalRead(ceza_bildirim) == 1)  //CEZA TOPLADIK
    {
    //DUVAR TAKİBİ VE RAKİP BÖLGEYE BOŞALTMA
    digitalWrite(kilit_sinyal, HIGH);
    dur();
    delay(2000);
    duvar_bul();
    duvarla_isim_var = 1;
    while (duvarla_isim_var == 1) {
      duvar_takip(0);
    }
    digitalWrite(kilit_sinyal, LOW);
    delay(1000);
    } else {
    Serial.println(digitalRead(sol));
    Serial.println(digitalRead(sag));
    rastgele();
    }

}

void duvar_bul()
{
  while(true)
  {
    if (digitalRead(sag) == 0)
    {
      analogWrite(ena, 160);
      analogWrite(enb, 160);
      sola_don();
      delay(100);
      dur();
      break;
    }
    else if (digitalRead(sol) == 0)
    {
      analogWrite(ena, 160);
      analogWrite(enb, 160);
      sola_don();
      delay(400);
      dur();
      break;
    }
    else
    {
      analogWrite(ena, 130);
      analogWrite(enb, 130);
      ileri();
    }
  }
  
}

void duvar_takip(int nereye)
{
  if (digitalRead(sol) == 0) //KÖŞEYE GELDİK
  {
    dur();
    delay(50);
    geri();
    delay(500);
    dur();
    float sonuc = olcum();
    if((sonuc > 200 && bolge == nereye) || (sonuc < 70 && bolge != nereye)) // park etmemiz gereken durumlar. sonuc > 200 kırmızı, sonuc < 70 mavi
    {
      park(nereye);
    }
    else
    {
      analogWrite(ena, 160);
      analogWrite(enb, 160);
      sola_don();
      delay(500);
    }
    
  }
  else
  {
    while (digitalRead(sag) == 0 && digitalRead(sol) == 1)
    {
      analogWrite(ena, 30);
      analogWrite(enb, 140);
      ileri();
    }
    while (digitalRead(sag) == 1 && digitalRead(sol) == 1)
    {
      analogWrite(ena, 140);
      analogWrite(enb, 30);
      ileri();
    }
  }

}

void park(byte nereye)
{
  if(nereye == 1)
  {
    analogWrite(ena, 160);
      analogWrite(enb, 160);
      sola_don();
      delay(600);
      analogWrite(ena, 130);
      analogWrite(enb, 130);
      geri();
      delay(200);
      dur();
      bizim_kapak.write(103);
      delay(300);
      analogWrite(ena, 130);
      analogWrite(enb, 130);
      ileri();
      delay(600);
      dur();
      bizim_kapak.write(13);
      duvarla_isim_var = 0;
  }
  else
  {
    analogWrite(ena, 160);
      analogWrite(enb, 160);
      sola_don();
      delay(700);
      analogWrite(ena, 130);
      analogWrite(enb, 130);
      geri();
      delay(200);
      dur();
      ceza_kapak.write(90);
      delay(300);
      digitalWrite(ceza_tokatla_sinyal, HIGH);
      delay(1000);
      digitalWrite(ceza_tokatla_sinyal, LOW);
      analogWrite(ena, 130);
      analogWrite(enb, 130);
      ileri();
      delay(600);
      dur();
      ceza_kapak.write(0);
      duvarla_isim_var = 0;
  }
}

void duvar_takip_eski(int nereye) {
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  ileri();
  if (digitalRead(sol) == 0 && digitalRead(sag) == 0) { // KÖŞEDEYİZ
    float sonuc = olcum();
    geri();
    delay(300);
    if ((sonuc > 200 && bolge == nereye) || (sonuc < 70 && bolge != nereye)) // park etmemiz gereken durumlar. sonuc > 200 kırmızı sonuc < 70 mavi
    {
      if (nereye == 0 && digitalRead(yan) == 1)
      {
        //ters_park();
      }
      park(nereye);
      duvarla_isim_var = 0;
    }
    else
    {
      analogWrite(ena, 150);
      analogWrite(enb, 150);
      sola_don();
      delay(500);
    }
  }
}

void duvar_takip_hazirlik()
{
  unsigned long baslangic = millis();
  while ((millis() - baslangic) > 10000)
  {
    analogWrite(ena, 200);
    analogWrite(enb, 200);
    ileri();
    if (digitalRead(sol) == 0 && digitalRead(sag) == 0) {
      geri();
      delay(300);
      analogWrite(ena, 150);
      analogWrite(enb, 150);
      sola_don();
      delay(500);
    }
  }
}

void park_eski(int nereye) {
  dur();
  delay(1000);
  geri();
  delay(300);
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  sola_don();
  delay(500);
  dur();
  delay(1000);
  ileri();
  delay(600);
  analogWrite(ena, 200);
  analogWrite(enb, 20);
  geri();
  delay(350);
  dur();
  delay(1000);
  analogWrite(ena, 0);  //SOLA MEYİLLİ İLERİ
  analogWrite(enb, 255);
  ileri();
  delay(700);
  dur();
  delay(1000);
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  geri();
  delay(500);
  dur();

  if (nereye == 1)
  {
    bizim_kapak.write(170);
    delay(400);
    ileri();
    delay(500);
    dur();
    bizim_kapak.write(10);
  }
  else
  {
    //CEZA BIRAK
    ceza_kapak.write(90);
    delay(300);
    digitalWrite(ceza_tokatla_sinyal, HIGH);
    delay(1000);
    digitalWrite(ceza_tokatla_sinyal, LOW);
    analogWrite(ena, 100);
    analogWrite(enb, 100);
    ileri();
    delay(300);
    dur();
    ceza_kapak.write(0);
  }
}

void rastgele() {
  if (digitalRead(sol) == 0)  //SOLDA ENGEL VAR
  {
    dur();
    delay(20);
    geri();
    delay(500);
    analogWrite(ena, 160);
    analogWrite(enb, 160);
    saga_don();
    delay(300);
    dur();
    delay(100);
    ileri();
  }
  else if (digitalRead(sag) == 0)  //SAĞDA ENGEL VAR
  {
    dur();
    delay(20);
    geri();
    delay(500);
    analogWrite(ena, 160);
    analogWrite(enb, 160);
    saga_don();
    delay(500);
    dur();
    delay(100);
    analogWrite(ena, 130);
    analogWrite(enb, 130);
    ileri();
  }
  else
  {
    ileri();
  }
}

void kirmizi_yak() {
  serit.clear();
  serit.setPixelColor(0, serit.Color(255, 0, 0));
  serit.setPixelColor(1, serit.Color(255, 0, 0));
  serit.setPixelColor(2, serit.Color(255, 0, 0));
  serit.setPixelColor(3, serit.Color(255, 0, 0));
  serit.setPixelColor(4, serit.Color(255, 0, 0));
  serit.show();
}

void mavi_yak() {
  serit.clear();
  serit.setPixelColor(0, serit.Color(0, 0, 255));
  serit.setPixelColor(1, serit.Color(0, 0, 255));
  serit.setPixelColor(2, serit.Color(0, 0, 255));
  serit.setPixelColor(3, serit.Color(0, 0, 255));
  serit.setPixelColor(4, serit.Color(0, 0, 255));
  serit.show();
}

float olcum() {
  //verileri güncelliyoruz
  for (int i = 0; i < 4; i++) {
    olc();
    kirmizi_veriler[i] = kirmizi;
    mavi_veriler[i] = mavi;
    delay(10);
  }

  kirmizi = stabilSonucuBul(kirmizi_veriler, 4);
  mavi = stabilSonucuBul(mavi_veriler, 4);

  float sonuc = ((float)mavi / (float)kirmizi) * 100;
  return sonuc;
}

void olc() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  delay(5);
  kirmizi = pulseIn(out, LOW);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  delay(5);
  mavi = pulseIn(out, LOW);
}

void ileri() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void geri() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void saga_don() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void sola_don() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void saga_ilerle() {
  analogWrite(ena, 255);
  analogWrite(enb, 70);
  ileri();
}

void sola_ilerle() {
  analogWrite(ena, 70);
  analogWrite(enb, 255);
  ileri();
}

void saga_gerile() {
  analogWrite(ena, 150);
  analogWrite(enb, 100);
  geri();
}

void sola_gerile() {
  analogWrite(ena, 150);
  analogWrite(enb, 200);
  geri();
}

void dur() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}




// ******************************Ortalama hesaplayan fonksiyon*****************************
double ortalamaHesapla(const int arr[], int size) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum / size;
}

// Standart sapmayı hesaplayan fonksiyon
double standartSapmaHesapla(const int arr[], int size, double mean) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += pow(arr[i] - mean, 2);
  }
  return sqrt(sum / size);
}

// Uç değerleri filtreleyerek en istikrarlı değeri bul
int stabilSonucuBul(const int arr[], int size) {
  // Dizinin ortalamasını hesapla
  double mean = ortalamaHesapla(arr, size);

  // Dizinin standart sapmasını hesapla
  double stdDev = standartSapmaHesapla(arr, size, mean);

  // Standart sapmanın 1.5 katından daha uzak olan değerleri göz ardı et
  const double threshold = 1.5 * stdDev;

  // Filtrelenmiş dizinin ortalamasını ve en yakın değeri bul
  double filteredSum = 0;
  int filteredCount = 0;
  int closestValue = arr[0];
  double minDifference = 1e6;  // çok büyük bir sayı kullanıyoruz

  for (int i = 0; i < size; i++) {
    if (fabs(arr[i] - mean) <= threshold) {
      filteredSum += arr[i];
      filteredCount++;

      // Ortalamaya en yakın değeri bul
      double diff = fabs(arr[i] - mean);
      if (diff < minDifference) {
        minDifference = diff;
        closestValue = arr[i];
      }
    }
  }

  return closestValue;
}
