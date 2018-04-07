class button {
  private:
    int pin;
    unsigned long debounceTime;
    unsigned int interval;
    boolean mode;
    boolean lastButtonState;
    boolean buttonState;
  public:
    button(int, unsigned int, boolean);
    boolean click();
    boolean click(unsigned int);
    boolean read();
    boolean change();
    boolean holdPress(unsigned int);
    void setInterval(unsigned int);
};

button::button(int pin, unsigned int interval = 30, boolean mode = false) {
  debounceTime = 0;
  lastButtonState = digitalRead(this -> pin);;

  this -> pin = pin;
  this -> mode = mode;
  this -> interval = interval;

  if (this -> mode) pinMode(this->pin, INPUT);
  else pinMode(this->pin, INPUT_PULLUP);
  buttonState = digitalRead(this -> pin);

}

boolean button::change() {
  boolean reading = digitalRead(pin);

  if (reading != lastButtonState) {
    lastButtonState = reading;
    debounceTime = millis();
  }

  if (millis() - debounceTime > interval) {
    if (reading != buttonState) {
      buttonState = reading;
      return true;
    }
  }

  return false;
}

boolean button::click() {
  click(interval);
}

boolean button::click(unsigned int delayTime) {
  boolean reading = digitalRead(pin);
  if (reading != lastButtonState) {
    lastButtonState = reading;
    debounceTime = millis();
  }
  if (millis() - debounceTime >= delayTime) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == mode) return true;
    }
  }

  return false;
}

/*void button::setInterval(unsigned int interval) {
  this -> interval = interval;
  }*/

/*boolean button::holdPress(unsigned int delayTime) {
  return (click(delayTime));
  }*/

button but1(2);

void setup() {
  Serial.begin(9600);
  pinMode (13, OUTPUT);
}

void loop() {
  if (but1.click()) digitalWrite(13, !digitalRead(13));
  //if (but1.holdPress(1000)) digitalWrite(12, !digitalRead(12));

}
