#include <LiquidCrystal.h>
#define AUTHOR "Salah Ud Din"
#define AUTHOR_GIT "GitHub: @4yub1k"
#define MULTIPLIER 86.504             // Multipier for voltage calculation.

LiquidCrystal lcd(12, 11, 10, 9, 8, 7); //(RS,EN,D4,D5,D6,D7)

int ac_input_r = A0;  //Pin assigning for R Phase
int ac_input_y = A1;  //Pin assigning for Y Phase
int ac_input_b = A2;  //Pin assigning for B Phase

// All functions, sequence wise.
void setup();
int samples(int acInput);
void author();
void loop();

//Setup function Start
void setup() {
  pinMode(ac_input_r, INPUT);
  pinMode(ac_input_y, INPUT);
  pinMode(ac_input_b, INPUT);

  lcd.begin(16,2);
  author();

  Serial.begin(9600);
}

// Take average of analoge values.
int samples(int acInput){
  unsigned short total = 0;
  unsigned short SAMPLES = 30;

  for (int i; i < SAMPLES; i++){
    total += analogRead(acInput);
    delay(1); 
  }
  return total / SAMPLES; //average
}

// Display
void author(){
  lcd.setCursor(0,0);
  lcd.print("Measure 3 Phase");
  lcd.setCursor(2,1);
  lcd.print("AC Voltages");
  delay(1000);
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print(AUTHOR);
  lcd.setCursor(1,1);
  lcd.print(AUTHOR_GIT);
  delay(1000);
  lcd.clear();
}

//Loop Function Start Here
void loop() {
  unsigned short ac_out_r = samples(ac_input_r);
  unsigned short ac_out_y = samples(ac_input_y);
  unsigned short ac_out_b = samples(ac_input_b);

  float ac_volt_r = (ac_out_r *  (5.0 / 1023.0) * MULTIPLIER); // (5/1023) * 544(serial ouput) = 2.67, 230/2.67
  float ac_volt_y = (ac_out_y *  (5.0 / 1023.0) * MULTIPLIER);
  float ac_volt_b = (ac_out_b *  (5.0 / 1023.0) * MULTIPLIER);
 
  Serial.println(ac_out_r);  // Display the R-Phase voltage on serial monitor.
  
  lcd.setCursor(0,0);
  lcd.print("R=" + String(ac_volt_r));
  
  lcd.setCursor(8,0);
  lcd.print("Y=" + String(ac_volt_y));
  
  lcd.setCursor(5,1);
  lcd.print("B=" + String(ac_volt_b));
  delay(20);
}