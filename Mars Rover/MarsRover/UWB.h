// adapted from UWB sample code from UNSW.

#ifndef UWB_h
#define UWB_h
#include "UWB.h" 

#include "MatrixMath.h";

#define PACKAGE_HEADER      0xFF
#define PACKAGE_TAIL        0xFE
#define PACKAGE_HEADER_LEN   2
#define PACKAGE_SELF_ID_LEN  2
#define PACKAGE_SEQ_LEN      1
#define PACKAGE_AMOUNT_LEN   1
#define PACKAGE_TAIL_LEN     2
#define PACKAGE_MIN_LEN      PACKAGE_HEADER_LEN+PACKAGE_SELF_ID_LEN+PACKAGE_SEQ_LEN+PACKAGE_AMOUNT_LEN+PACKAGE_TAIL_LEN
#define PACKAGE_ANCHOR_ID_LEN   2
#define PACKAGE_FLOAT_LEN       4

#define bufferSize      300
#define MaxObsevationNum      6

class UWB {
    public:
        void setup();
        void loop();
        void computeLocation();
        void decodePackage();
        void serialEvent();
        void readSerialEvent(char read);
        float getX();
        float getY();
    private:
        byte uartBuffer[bufferSize];
        int uartBufferCursor=0;
        int ObservationNum;
        int ObserverdID[MaxObsevationNum];
        float ObservedRange[MaxObsevationNum];
        uint8_t hasNewUWBdata=0;
        float position[2] = {0,0};
        
        /*******************************************************************************/
        /***Anchors' coordinates will be provided once the test environment is set up   */
        /*******************************************************************************/
        int AnchorNum=4;

        /*******************************************************************************/
};

#endif