// This is a header file for the rfd interface file.
// make sure that the RFD900+ is configured properly before use
// use the following settings and steps for setup:
// - baud rate: 57600
// - air data rate: 64


// initializer function for the RFD900+
// called from main
void RFD_Init();

void RFD_Thread_Main();