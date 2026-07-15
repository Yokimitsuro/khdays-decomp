/* func_ov006_02051f6c -- title input poll, ov006. 0 = idle; 2 = attract timeout fired
 * (key 9 + func_ov006_0204fd94); 1 = Start pressed (key 7). Guarded by the title-ready
 * flag data_ov006_02056660. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *data_ov006_02056660;
extern int  func_ov006_02055950(void);
extern int  func_ov006_0204fd94(void);
int func_ov006_02051f6c(void) {
    NNSi_FndGetCurrentRootHeap();
    if (data_ov006_02056660 == 0) {
        return 0;
    }
    if (func_ov006_02055950() == 9 && func_ov006_0204fd94() != 0) {
        return 2;
    }
    return func_ov006_02055950() == 7;
}
