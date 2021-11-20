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

class Motor {
  public:
    // ATTRIBUTES: aka variables, properties.
    // State machine attributes
    byte current_state = 1;
    unsigned long t;
    unsigned long update_time;

    // Other attributes
    byte wire_1;
    byte wire_2;
    byte wire_3;
    byte wire_4;
    byte enable_pin;
    short spin_direction = 1; // 1 or -1
    short state = 1;

    int number_steps = 10;
    int step_count = 0;
    int step_delay = 100;
    int spin_count = 0;
    bool spinning = false;

    // CONSTRUCTOR
    Motor(byte WIRE_1, byte WIRE_2, byte WIRE_3, byte WIRE_4, byte ENABLE_PIN) {
      wire_1 = WIRE_1;
      wire_2 = WIRE_2;
      wire_3 = WIRE_3;
      wire_4 = WIRE_4;
      enable_pin = ENABLE_PIN;

      pinMode(enable_pin, OUTPUT);
      pinMode(wire_1, OUTPUT);
      pinMode(wire_2, OUTPUT);
      pinMode(wire_3, OUTPUT);
      pinMode(wire_4, OUTPUT);
      enable(HIGH);
    }
    // YOUR CODE HERE
    // IMPLEMENT FUNCTIONS: *UPDATE(), *STATE1_STOPPED(), *STATE2_SPINNING(), *SET_STEP_DELAY(ms), *START(), *STOP()
    // NEW VARIABLES: unsigned long *t, unsigned long *update_time, byte *current_state,
    //                bool *spinning, int *number_steps, int *step_count, int *spin_count, int *step_delay

    // UPDATE: Check time and run state process
    void update() {
      t = millis();
      if (t >= update_time) {
        switch (current_state) {
          case 1:
            state1_stopped();
            break;
          case 2:
            state2_spinning();
            break;
          default:
            break;
        }
      }
    }

    //  STATE METHODS
    void state1_stopped() {
      spinning = false;
      update_time = t + 1;
    }

    void state2_spinning() {
      do_step();
      update_time = t + step_delay;
    }

    // OTHER METHODS
    void start() {
      current_state = 2;
      spinning = true;
    }

    void stop() {
      current_state = 1;
      spinning = false;
    }

    void set_step_delay(int STEP_DELAY) {
      step_delay = STEP_DELAY;
    }

    void enable(bool en) {
      digitalWrite(enable_pin, en);
    }

    void change_direction() {
      if (spin_direction == 1)
      {
        spin_direction = -1;
      }
      else
      {
        spin_direction = 1;
      }
    }

    void do_step() {
      state = state + spin_direction;
      if (state > 4) {
        state = 1;
      }
      if (state < 1) {
        state = 4;
      }

      switch (state) {
          step_count = step_count + 1;
          if (step_count == spin_count) {
            spin_count = spin_count + 1;
            step_count = 0;
          }

        case 1:
          digitalWrite(wire_1, LOW);
          digitalWrite(wire_2, HIGH);
          digitalWrite(wire_3, HIGH);
          digitalWrite(wire_4, LOW);
          break;
        case 2:
          digitalWrite(wire_1, LOW);
          digitalWrite(wire_2, HIGH);
          digitalWrite(wire_3, LOW);
          digitalWrite(wire_4, HIGH);
          break;
        case 3:
          digitalWrite(wire_1, HIGH);
          digitalWrite(wire_2, LOW);
          digitalWrite(wire_3, LOW);
          digitalWrite(wire_4, HIGH);
          break;
        case 4:
          digitalWrite(wire_1, HIGH);
          digitalWrite(wire_2, LOW);
          digitalWrite(wire_3, HIGH);
          digitalWrite(wire_4, LOW);
          break;
        default:
          // statements
          break;
      }
    }
};


Motor motor1 = Motor(1, 2, 3, 4, 5);
Motor motor2 = Motor(8, 9, 10, 11, 12);

Button start_stop1 = Button(14);
Button change_direction1 = Button(15);
Button start_stop2 = Button(7);
Button change_direction2 = Button(6);

void setup() {
  // put your setup code here, to run once:

  motor2.set_step_delay(169);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Connect buttons to Stop/Start and Change direction of motors.
  //
  // YOUR CODE HERE

  // UPDATES
  motor1.update();
  motor2.update();
  start_stop1.update();
  change_direction1.update();
  start_stop2.update();
  change_direction2.update();

  // LOGIC
  if (start_stop1.was_pressed()) {
    if (motor1.spinning) motor1.stop();
    else motor1.start();
  }
  if (change_direction1.was_pressed()) motor1.change_direction();

  if (start_stop2.was_pressed()) {
    if (motor2.spinning) motor2.stop();
    else motor2.start();
  }
  if (change_direction2.was_pressed()) motor2.change_direction();

  delay(1); // TO AVOID SLOW SIMULATION. CAN BE REMOVED IN REAL IMPLEMENTATION.

}
