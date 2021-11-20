class Button {
  public: // provides access to object's methods and attributes. (see protected)

    // ATTRIBUTES: aka variables, properties.
    // State machine attributes
    byte current_state = 1;
    unsigned long t;
    unsigned long update_time;
    // Other attributes
    byte pin;
    bool pressed = false;

    // CONSTRUCTOR
    Button(byte PIN) {
      pin = PIN;
      pinMode(pin, INPUT_PULLUP);
      current_state = 1;
      update_time = 0;
    }

    // UPDATE: Check time and run state process
    void update() {
      t = millis();
      if (t >= update_time) {
        switch (current_state) {
          case 1:
            state1_released(); break;
          case 2:
            state2_pressed(); break;
          default:
            break;
        }
      }
    }

    //  STATE METHODS
    void state1_released() {
      if (digitalRead(pin) == HIGH) {
        update_time = t + 1;
      }
      else {
        pressed = true;
        current_state = 2;
        update_time = t + 20;
      }
    }

    void state2_pressed() {
      if (digitalRead(pin) == LOW) {
        update_time = t + 1;

      }
      else {
        current_state = 1;
        update_time = t + 20;
      }
    }

    // OTHER METHODS
    bool was_pressed() {
      if (pressed) {
        pressed = false;
        return true;
      }
      else {
        return false;
      }
    }
};

Button button1 = Button(8);
Button button2 = Button(9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  button1.update();
  button2.update();

  if (button1.was_pressed()) {
    Serial.println("Doing something");
  }
  if (button2.was_pressed()) {
    Serial.println("Doing something else");
  }
}
