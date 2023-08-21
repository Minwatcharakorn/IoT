#include <DHT.h> // เรียกใช้งานไลบรารี DHT
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2     // ขาที่เชื่อมต่อกับเซ็นเซอร์ DHT
#define DHTTYPE DHT22   // ประเภทของเซ็นเซอร์ DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE); // เริ่มต้นใช้งานเซ็นเซอร์ DHT

LiquidCrystal_I2C lcd(0x27, 16, 2); // ตั้งค่าที่อยู่ของจอ LCD ที่ 0x27 ให้แสดงผลทีละ 16 ตัวอักษรและ 2 บรรทัด

// กำหนดขนาดจอ LCD เป็น 16x2

int screenWidth = 16;
int screenHeight = 2;

// ในการเคลื่อนที่บรรทัดเพียงหนึ่งบรรทัดต้องเคลื่อนที่ตัวอักษรหนึ่งตัวอักษรต่อครั้ง

// กำหนดบรรทัดสองบรรทัด

int stringStart, stringEnd = 0;
int scrollCursor = screenWidth;

void setup() {
  dht.begin(); // เริ่มต้นใช้งานเซ็นเซอร์ DHT

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  lcd.init();
  lcd.backlight();
  lcd.begin(screenWidth, screenHeight);
}

void loop() {
  
  

  

  lcd.clear();

  // อ่านข้อมูลจากเซ็นเซอร์ DHT22
  float temperature = dht.readTemperature(); // อ่านอุณหภูมิเป็นองศาเซลเซียส
  float humidity = dht.readHumidity();       // อ่านความชื้น

  // แสดงข้อมูลจากเซ็นเซอร์ DHT บนจอ LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000); // หน่วงเวลาสักครู่ก่อนที่จะอัปเดตจอ LCD อีกครั้ง
}
