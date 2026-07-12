/* Read the word at +0x94f4 of the ov006 global object, or -1 if absent. */
extern int data_ov006_02056664;
int func_ov006_02055950(void) {
    if (data_ov006_02056664 != 0) return *(int *)(data_ov006_02056664 + 0x94f4);
    return -1;
}
