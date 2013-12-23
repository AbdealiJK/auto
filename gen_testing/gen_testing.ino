char c;

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
 
  Serial.begin(9600);
           digitalWrite(5,LOW);
          digitalWrite(4,LOW);          
          analogWrite(6,255);          
 

}

void loop() {

  if(Serial.available())
  {
      c = Serial.read();
      if(c=='a')
      {
          digitalWrite(4,HIGH);
          digitalWrite(5,LOW);          
          analogWrite(6,200);          
          Serial.println("a");
      }
      else if(c=='d')
      {
          digitalWrite(5,HIGH);
          digitalWrite(4,LOW);          
          analogWrite(6,200);            
          Serial.println("d");          
      }      
      else if(c=='s')
      {
          digitalWrite(5,LOW);
          digitalWrite(4,LOW);          
          analogWrite(6,255); 
          Serial.println("s");         
      }            
      else if(c=='w')
      {
          digitalWrite(5,HIGH);
          digitalWrite(4,HIGH);          
          analogWrite(6,255);                    
          Serial.println("w");          
      }                  
  }
  
}
