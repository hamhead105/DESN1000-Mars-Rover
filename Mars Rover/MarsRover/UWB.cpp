#include <Arduino.h>
#include "UWB.h"

void UWB::setup() {
    Serial.begin(115200);  
}

void UWB::loop() {
    if(hasNewUWBdata==1){
        hasNewUWBdata=0;
        computeLocation();
   }
}

/**
* @brief Compute location based on UWB measurements
*/
void UWB::computeLocation() {
    int AnchorID[]={2820,2819,2816,2821};
    double AnchorXYZ[][3] = {{0,0,2},
                        {0,10,2},
                        {10,0,2},
                        {10,10,2}};    //unit: m

    Serial.print("UWB observation: ");
    Serial.println(ObservationNum);
    double Matrix_tmp[MaxObsevationNum][4];
    int counter=0;
    for(int i=0;i<ObservationNum;i++){
        Serial.print(ObserverdID[i]);Serial.print(" ");Serial.println(ObservedRange[i]);
        for(int j=0;j<AnchorNum;j++){
            if (ObserverdID[i]==AnchorID[j]){
                Matrix_tmp[counter][0]=AnchorXYZ[j][0];  //X
                Matrix_tmp[counter][1]=AnchorXYZ[j][1];  //Y
                Matrix_tmp[counter][2]=AnchorXYZ[j][2];  //Z
                Matrix_tmp[counter][3]=ObservedRange[i]; //Range
                counter++;
            }
        }
    }
    
    if(counter>=4){
        double Matrix_P[3][1]={{1},{1},{0}};
        double Matrix_dxyz[3][1]={{0},{0},{0}};
        double Matrix_A[counter][3];
        double Matrix_B[counter][1];

        double Matrix_AT[3][counter];
        double Matrix_ATA[3][3];
        double Matrix_ATA_rev[3][3];
        double Matrix_ATA_rev_AT[3][counter];
        int loop=0;
        while(loop<20) {
            Matrix.Add((double*)Matrix_P,(double*)Matrix_dxyz, 3, 1, (double*)Matrix_P);

            for(int i=0;i<counter;i++){
              double tmpD=(pow((Matrix_tmp[i][0]-Matrix_P[0][0]),2)
                              +pow((Matrix_tmp[i][1]-Matrix_P[1][0]),2)
                              +pow((Matrix_tmp[i][2]-Matrix_P[2][0]),2));

              
              Matrix_A[i][0]=2*(Matrix_P[0][0]-Matrix_tmp[i][0]);
              Matrix_A[i][1]=2*(Matrix_P[1][0]-Matrix_tmp[i][1]);
              Matrix_A[i][2]=2*(Matrix_P[2][0]-Matrix_tmp[i][2]);
              Matrix_B[i][0]=pow(Matrix_tmp[i][3],2)-tmpD;
            
            }

            Matrix.Transpose((double*)Matrix_A, counter, 3, (double*)Matrix_AT);
            Matrix.Multiply((double*)Matrix_AT, (double*)Matrix_A, 3, (counter),3, (double*)Matrix_ATA);
            Matrix.Invert((double*)Matrix_ATA, 3);//inv
            Matrix.Multiply((double*)Matrix_ATA, (double*)Matrix_AT, 3, 3,(counter), (double*)Matrix_ATA_rev_AT);
            Matrix.Multiply((double*)Matrix_ATA_rev_AT, (double*)Matrix_B, 3, (counter),1, (double*)Matrix_dxyz);
        
            if(abs(Matrix_dxyz[0][0])<0.005&& abs(Matrix_dxyz[1][0])<0.005){
                Matrix.Add((double*)Matrix_P,(double*)Matrix_dxyz, 3, 1, (double*)Matrix_P);
                break;
            }
            loop++;
        }
      
        if(loop <20){
            /* USER CODE BEGIN */
            
            /*Add code here to pass the positioning result to your application*/
            
            /* USER CODE END  */
            Serial.print("X: ");Serial.print(Matrix_P[0][0]);
            Serial.print(" Y: ");Serial.println(Matrix_P[1][0]);
        } else {
            Serial.println("Algorithm did not converge");
        }
        ObservationNum=0;
        return;
    }
    Serial.println("No enough measurements");
    ObservationNum=0;
}

/**
* @brief Decde the UWB package after a pacakge-end is detected
*/
void UWB::decodePackage(){
  int tmpCursor=0;
  /*ignore the data until a package header is detected*/
  while(tmpCursor<=uartBufferCursor){
    if(uartBuffer[tmpCursor]==PACKAGE_HEADER 
      && uartBuffer[tmpCursor+1]==PACKAGE_HEADER){
      break;
    }else{
      tmpCursor++;
    }
  }

  if(tmpCursor+PACKAGE_MIN_LEN<=uartBufferCursor){
    ObservationNum=uartBuffer[tmpCursor+PACKAGE_HEADER_LEN+PACKAGE_SELF_ID_LEN+PACKAGE_SEQ_LEN];
    
    if(tmpCursor+PACKAGE_MIN_LEN+6*ObservationNum<uartBufferCursor){
      /*Just return if package length is shorter than we expected */
      uartBufferCursor=0;
      return;
    }
    /*Decode data amd prepare for location computation */
    tmpCursor+=(PACKAGE_HEADER_LEN+PACKAGE_SELF_ID_LEN+PACKAGE_SEQ_LEN+PACKAGE_AMOUNT_LEN);
    for(int i=0;i<ObservationNum;i++){
      ObserverdID[i]=uartBuffer[tmpCursor]+(uartBuffer[tmpCursor+1]<<8);
      memcpy(&ObservedRange[i],&uartBuffer[tmpCursor+PACKAGE_ANCHOR_ID_LEN],PACKAGE_FLOAT_LEN);
      tmpCursor+=(PACKAGE_ANCHOR_ID_LEN+PACKAGE_FLOAT_LEN);
    }

    hasNewUWBdata=1;
    uartBufferCursor=0;
    return;
  }else{
    /*Just return if package length is shorter than we expected */
    uartBufferCursor=0;
    return;
  }
  
}

/**
* @brief Read UART buffer on serial event.
*/
void UWB::serialEvent() {
  Serial.println("serial event");
  if (Serial.available() > 0) {
    // read the incoming byte:
    uartBuffer[uartBufferCursor] = Serial.read();
    /* check if the package tail 0xfe 0xfe is detected */
    if(uartBuffer[uartBufferCursor]==PACKAGE_TAIL 
      && uartBufferCursor>0 && uartBuffer[uartBufferCursor-1]==PACKAGE_TAIL){
      decodePackage();
      return;
    }
    uartBufferCursor++;
    if(uartBufferCursor>=bufferSize){
      uartBufferCursor=0;
    }
  }
}

void UWB::readSerialEvent(char read) {
    // read the incoming byte:
    uartBuffer[uartBufferCursor] = read;
    /* check if the package tail 0xfe 0xfe is detected */
    if(uartBuffer[uartBufferCursor]==PACKAGE_TAIL 
      && uartBufferCursor>0 && uartBuffer[uartBufferCursor-1]==PACKAGE_TAIL){
      decodePackage();
      return;
    }
    uartBufferCursor++;
    if(uartBufferCursor>=bufferSize){
      uartBufferCursor=0;
    }
}

