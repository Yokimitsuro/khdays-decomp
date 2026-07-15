/* func_ov006_0204fb50 -- fetch field [10] of the ov006 context list node, ov006
 * (tail-call to func_02023c28 over the node at *(&data_ov006_020565e4 + 4)). */
extern int func_02023c28(int *node);
extern int data_ov006_020565e4;
int func_ov006_0204fb50(void) {
    return func_02023c28(*(int **)((char *)&data_ov006_020565e4 + 4));
}
