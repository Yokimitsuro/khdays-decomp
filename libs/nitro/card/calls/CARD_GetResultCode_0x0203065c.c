/* CARD_GetResultCode: returns the last card-command result code held at *data_0204c228. */

extern int *data_0204c228;

int CARD_GetResultCode_0x0203065c(void) {
    return *data_0204c228;
}
