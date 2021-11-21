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
      step_count = step_count + 1;
      if (step_count == number_steps) {
        spin_count = spin_count + 1;
        step_count = 0;
      }
      
      state = state + spin_direction;
      if (state > 4) {
        state = 1;
      }
      if (state < 1) {
        state = 4;
      }

      switch (state) {
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

class Display {
  public:
    byte a;
    byte b;
    byte c;
    byte d;
    byte e;
    byte f;
    byte g;
    byte h;
    byte cat;

    Display(byte A, byte B, byte C, byte D, byte E, byte F, byte G, byte CAT) {
      a = A; b = B; c = C; d = D; e = E; f = F; g = G; cat = CAT;

      pinMode(a, OUTPUT);
      pinMode(b, OUTPUT);
      pinMode(c, OUTPUT);
      pinMode(d, OUTPUT);
      pinMode(e, OUTPUT);
      pinMode(f, OUTPUT);
      pinMode(g, OUTPUT);
      pinMode(cat, OUTPUT);
    }

    void hide() {
      digitalWrite(cat, LOW);
    }

    void show_number(byte number) {
      switch (number) {
        case 0:
          digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, HIGH); digitalWrite(g, LOW);
          digitalWrite(cat, HIGH);
          break;
        case 1:
          digitalWrite(a, LOW); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, LOW); digitalWrite(e, LOW); digitalWrite(f, LOW); digitalWrite(g, LOW);
          digitalWrite(cat, HIGH);
          break;
        case 2:
          digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, LOW); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, LOW); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        case 3:
          digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, LOW); digitalWrite(f, LOW); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        case 4:
          digitalWrite(a, LOW); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, LOW); digitalWrite(e, LOW); digitalWrite(f, HIGH); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        case 5:
          digitalWrite(a, HIGH); digitalWrite(b, LOW); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, LOW); digitalWrite(f, HIGH); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        case 6:
          digitalWrite(a, HIGH); digitalWrite(b, LOW); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        case 7:
          digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, LOW); digitalWrite(e, LOW); digitalWrite(f, LOW); digitalWrite(g, LOW);
          digitalWrite(cat, HIGH);
          break;
        case 8:
          digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        case 9:
          digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, LOW); digitalWrite(f, HIGH); digitalWrite(g, HIGH);
          digitalWrite(cat, HIGH);
          break;
        default:
          // statements
          break;
      }
    }
};

// YOUR CODE HERE
//class Display_x4{
//  public:
//    ATTRIBUTES: byte digit_1, byte digit_10, byte digit_100, byte digit_1000,
//                display_1, display_10, display_100, display_1000
//    Display_x4(byte A, byte B, byte C, byte D, byte E, byte F, byte G, byte CAT_1, byte CAT_10, byte CAT_100, byte CAT_1000) {
//    void update()
//    void show_number()
//}

class Display_x4 {
  public:
    // ATTRIBUTES: aka variables, properties.
    // State machine attributes
    byte current_state = 1;
    unsigned long t;
    unsigned long update_time;

    // Other attributes
    byte digit_1 = 0;
    byte digit_10 = 0;
    byte digit_100 = 0;
    byte digit_1000 = 0;

    Display *display_1;
    Display *display_10;
    Display *display_100;
    Display *display_1000;

//    Display_x4(byte A, byte B, byte C, byte D, byte E, byte F, byte G, byte CAT_1, byte CAT_2, byte CAT_3, byte CAT_4) {
    Display_x4(Display *DISPLAY_1, Display *DISPLAY_10, Display *DISPLAY_100, Display *DISPLAY_1000) {
//      display_1 = &Display(A, B, C, D, E, F, G, CAT_1);
//      display_10 = &Display(A, B, C, D, E, F, G, CAT_2);
//      display_100 = &Display(A, B, C, D, E, F, G, CAT_3);
//      display_1000 = &Display(A, B, C, D, E, F, G, CAT_4);

      display_1 = DISPLAY_1;
      display_10 = DISPLAY_10;
      display_100 = DISPLAY_100;
      display_1000 = DISPLAY_1000;
    }

    // UPDATE: Check time and run state process
    void update() {
      t = millis();
      if (t >= update_time) {
        switch (current_state) {
          case 1:
            state1(); break;
          case 2:
            state2(); break;
          case 3:
            state3(); break;
          case 4:
            state4(); break;
          default:
            break;
        }
      }
    }

    void state1() {
      hide();
      display_1->show_number(digit_1);
      current_state = 2; update_time = t + 20;
    }

    void state2() {
      hide();
      display_10->show_number(digit_10);
      current_state = 3; update_time = t + 20;
    }

    void state3() {
      hide();
      display_100->show_number(digit_100);
      current_state = 4; update_time = t + 20;
    }

    void state4() {
      hide();
      display_1000->show_number(digit_1000);
      current_state = 1; update_time = t + 20;
    }

    void show_number(int n) {
      digit_1 = n % 10; n = n / 10;
      digit_10 = n % 10; n = n / 10;
      digit_100 = n % 10; n = n / 10;
      digit_1000 = n % 10; n = n / 10;      
    }

    void hide(){
      display_1->hide();
      display_10->hide();
      display_100->hide();
      display_1000->hide();
      }

};

Motor motor1 = Motor(1, 2, 3, 4, 5);
Motor motor2 = Motor(8, 9, 10, 11, 12);

Button start_stop1 = Button(14);
Button change_direction1 = Button(15);
Button start_stop2 = Button(7);
Button change_direction2 = Button(6);

Display display_1 = Display(A8, A9, A10, A11, A12, A13, A14, A1);
Display display_10 = Display(A8, A9, A10, A11, A12, A13, A14, A2);
Display display_100= Display(A8, A9, A10, A11, A12, A13, A14, A3);
Display display_1000 = Display(A8, A9, A10, A11, A12, A13, A14, A4);

// Display_x4 display_x4 = Display_x4(A8, A9, A10, A11, A12, A13, A14, A1, A2, A3, A4); 
Display_x4 display_x4 = Display_x4(&display_1, &display_10, &display_100, &display_1000); 

void setup() {
  // put your setup code here, to run once:
  motor2.set_step_delay(169);
  display_x4.show_number(4269);
}

void loop() {
  // put your main code here, to run repeatedly:

  // UPDATES
  motor1.update();
  motor2.update();
  start_stop1.update();
  change_direction1.update();
  start_stop2.update();
  change_direction2.update();
  display_x4.update();

  // LOGIC
  if(start_stop1.was_pressed()){
    if(motor1.spinning) motor1.stop();
    else motor1.start();
    }
  if(change_direction1.was_pressed()) motor1.change_direction();

  if(start_stop2.was_pressed()){
    if(motor2.spinning) motor2.stop();
    else motor2.start();
    }
  if(change_direction2.was_pressed()) motor2.change_direction();

  // YOUR CODE HERE
  // connect display_x4 to show the spin count of motor1

  display_x4.show_number(motor1.spin_count);


  delay(1); // TO AVOID SLOW SIMULATION. CAN BE REMOVED IN REAL IMPLEMENTATION.

}
