class StateMachineName {
  public: // provides access to object's methods and attributes. (see protected)

    // ATTRIBUTES: aka variables, properties.
    // State machine attributes
    byte current_state = 1;
    unsigned long t;
    unsigned long update_time;
    // Other attributes
    byte var_1;
    byte var_2;

    // CONSTRUCTOR
    StateMachineName(byte VAR_1, byte VAR_2) {
      // initialize data
      var_1 = VAR_1;
      var_2 = VAR_2;
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
          default:
            break;
        }
      }
    }

    //  STATE METHODS
    void state1() {
      bool STAY_CONDITION = true;
      if (STAY_CONDITION) { // stays in same state
        // DO SOMETHING (OR NOTHING)
        update_time = t + 20; // time to run state again.
      }
      else {
        // DO SOMETHING ELSE
        current_state = 2;  // state transition
        update_time = t + 1; // time to run next state.
      }
    }

    void state2() {
      bool STAY_CONDITION = true;
      if (STAY_CONDITION) { // stays in same state
        // DO SOMETHING
        update_time = t + 20; // time to run state again.
      }
      else {
        // DO SOMETHING ELSE
        current_state = 1;  // state transition
        update_time = t + 1; // time to run next state.
      }
    }

    void transition(byte NEW_STATE, unsigned long DT = 0) {
      // inmediate transition without waiting for current state to run.
      current_state = NEW_STATE;  // state transition
      update_time = t + DT; // time to run next state.
    }

    // OTHER METHODS
    void method_1() {
      // DO SOMETHING:
      // var_1 = var1 + var_2;
    }
};

StateMachineName machine1 = StateMachineName(1, 2);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  machine1.update();

}
