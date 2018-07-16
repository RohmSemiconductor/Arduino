 #include "MK71251.h"
#include <string.h>

MK71251 mk71251;

void setup() {
  // put your setup code here, to run once:
  mk71251.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char data, d;
  const char str[13] = "WRITING TEST";
  int rc;

  // rc = 0, if data is available on Serial2, else rc = -1
  rc = mk71251.read(&data);
  
  if (rc == 0){
    printf("Read %c\n",data);
    
    if (data == 'Z') { //Test write function when 'Z' is detected
      for (unsigned int i = 0; i <= strlen(str); i++) {
        d = str[i];
        mk71251.write(&d);  
      }
    }
  }
}
