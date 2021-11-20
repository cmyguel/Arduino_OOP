class ClassName{
  public: // provides access to object's methods and attributes. (see protected)

    // ATTRIBUTES: aka variables, properties. 
    byte var_1;
    byte var_2;

    // OBJECT CONSTRUCTOR: Special method in the class that creates an Object. 
    // useful for initial Settups and save data in the object. 
    ClassName(byte VAR_1, byte VAR_2){
      // initialize data
      var_1 = VAR_1;
      var_2 = VAR_2;
      // settup example. 
      //  pinMode(var_1, INPUT_PULLUP);
      }

    // METHODS: aka, functions
    bool method_1(){
      // return digitalRead(var_1)
      }
    void method_2(int n){
      // var_2 = var_2 + n
      }
  };

// CREATE OBJECTS FROM CLASS
ClassName object1 = ClassName(1, 2);
ClassName object2 = ClassName(3, 4);

void setup() {
  // ACCESS DATA
   byte x = object1.var_1;
   object1.var_1 = 42;

  // RUN METHODS
   bool y = object1.method_1();  
   object1.method_2(123);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
