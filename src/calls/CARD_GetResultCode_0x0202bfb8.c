/* CARD_GetResultCode: returns the last card-command result code held at *data_0204c208. */

extern int *data_0204c208;

int CARD_GetResultCode_0x0202bfb8(void) {
    return *data_0204c208;
}
