/* Initialise a queued-event record: copy the 3-word payload from src (param_2) into
 * the slot (param_1), store the tag (param_3), a duration (param_4, or the global
 * default at data_0204c20c when 0), a fixed priority byte (10 @+0x14) and clear the
 * status halfword (+0x16). Returns 1. */
#pragma thumb on
typedef struct { unsigned int a, b, c; } EventPayload;
extern int data_0204c20c;
int func_0202df00(unsigned int *param_1, unsigned int *param_2, unsigned int param_3, int param_4) {
    *(EventPayload *)param_1 = *(EventPayload *)param_2;
    param_1[3] = param_3;
    if (param_4 == 0) param_4 = data_0204c20c;
    param_1[4] = param_4;
    *(unsigned char *)(param_1 + 5) = 10;
    *(unsigned short *)((int)param_1 + 0x16) = 0;
    return 1;
}
