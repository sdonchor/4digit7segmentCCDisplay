

/**PINS**/
int segPins[7] = {2,3,4,5,6,7,8};
int dispPins[4] = {12,11,10,9};
/*******/

/**DISPLAY GLOBALS**/
int displayedContent[4] = {13,13,13,13}; //initialize with four dashes, change to {12,12,12,12} for empty display
int currentDisplay = 0;
unsigned long lastRefreshTime = 0;
int refreshInterval = 1;
int dispToRefresh = 0;
/*******************/

/**SEGMENTS MAPPING**/
int segments[14][7] = 
{
// A B C D E F G
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}, //9
  {1,0,0,1,1,1,1}, //10 - E
  {0,0,0,0,1,0,1}, //11 - r
  {0,0,0,0,0,0,0}, //12 - empty
  {0,0,0,0,0,0,1}  //13 - dash
};
/*********************/





void setup() {
  for(int i = 0 ; i<7 ; i++){
    pinMode(segPins[i], OUTPUT);
  }
  for(int i = 0 ; i <4 ; i++){
    pinMode(dispPins[i],OUTPUT);
  }
}

void clearDisplay(){
  for(int i = 0 ; i < 7 ; i++)
  {
    digitalWrite(segPins[i],0);
  }
}

void printDigit(int digit,int disp){
  clearDisplay();
  //set display
  for(int i = 0 ; i <4 ; i++){
    if(disp==i)
    {
      digitalWrite(dispPins[i],LOW);
    }
    else
    {
      digitalWrite(dispPins[i],HIGH);
    }
  }
  //set segments
  for(int i = 0 ; i<7; i++){
     digitalWrite(segPins[i],segments[digit][i]);
  }
}

void refreshDisplay(){
  if(millis() > lastRefreshTime + refreshInterval){
    printDigit(displayedContent[dispToRefresh],dispToRefresh);
    dispToRefresh++;
    lastRefreshTime=millis();
    if(dispToRefresh>3)
    {
      dispToRefresh=0;
    }
  }
}

void displayNumber(int x){
  if(x>9999 || x<0){
    displayedContent[3] = 10;
    displayedContent[2] = 11;
    displayedContent[1] = 11;
    displayedContent[0] = 12;
    return;
  }
  
  //split the number into single digits
  int a = x%10000/1000;
  int b = x%1000/100;
  int c = x%100/10;
  int d = x%10; 

  //remove unnecessary zeros
  if(x<10){
    c=12;
  }
  if(x<100){
    b=12;
  }
  if(x<1000){
    a=12;
  }

  //write to global display variable
  displayedContent[3] = a;
  displayedContent[2] = b;
  displayedContent[1] = c;
  displayedContent[0] = d;
}


/**TEST - SAFE TO REMOVE**/
unsigned long lastCountTime = 0;
int countInterval = 1000;
int count = 0;

void countUp(){
  if(millis()>lastCountTime+countInterval)
     {
        count++;
        lastCountTime=millis();
        displayNumber(count);  
     }
}
/*************************/

void loop(){
     refreshDisplay();
     
     /**TEST - SAFE TO REMOVE**/
     countUp();
     /************************/


}
