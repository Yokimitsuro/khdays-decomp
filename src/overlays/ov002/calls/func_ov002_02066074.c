extern int func_ov002_0206b7a4(void);
extern void OS_IsThreadAvailable_0x0206373c(void);
extern void func_ov002_02066738(void);
extern int func_02030788(void);
extern char *data_ov002_0207f99c;

/* Confirms the pending mission once the fade is done, and records the caller's choice when the
 * current slot is the local player's. */
void func_ov002_02066074(int choice) {
    char *self = data_ov002_0207f99c;
    if (func_ov002_0206b7a4() != 0) {
        return;
    }
    OS_IsThreadAvailable_0x0206373c();
    func_ov002_02066738();
    if (*(int *)(self + 4) == func_02030788()) {
        *(int *)(self + 0x28) = choice;
    }
}
