/* Report whether +0x4b74 of the ov005 global object is <= 1. */
extern int data_ov005_0205b810;
int func_ov005_02057a90(void) {
    return *(int *)(data_ov005_0205b810 + 0x4b74) <= 1;
}
