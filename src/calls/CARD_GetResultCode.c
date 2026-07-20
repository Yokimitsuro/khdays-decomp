/* CARD_GetResultCode: returns the last card result code (*data_020464e0). */

extern int *data_020464e0;

int CARD_GetResultCode(void) {
    return *data_020464e0;
}
