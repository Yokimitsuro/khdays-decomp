/* Read the s8 at +0x95ae+param of the ov006 global object, or 1 if absent. */
extern int data_ov006_02056664;
int func_ov006_02055970(int param_1) {
    if (data_ov006_02056664 != 0)
        return *(signed char *)(data_ov006_02056664 + param_1 + 0x95ae);
    return 1;
}
