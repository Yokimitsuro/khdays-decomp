/* c634 handler: unless the parent's busy flag (obj[1]+0xad) is set, re-arm sub-items
 * NONMATCHING (tail scheduling tie): body exact but mwcc schedules the 4th func_0203b9fc
 * call's `mov r2,#1` after `ldr r0` (ROM: before) and the dispatch `mov r0,r5` early
 * (ROM: last) - a few-byte reorder in the last-call+dispatch tail. 4-member family ov206.
 * 0/1/2/4 of obj[1] via func_0203b9fc(.,i,1,1) and dispatch via func_0203c634. */
extern void func_0203b9fc(int obj, int idx, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov206_020ccd68(void);
void func_ov206_020ccce8(int self) {
    int *obj = *(int **)(self + 4);
    if (*(unsigned char *)(obj[1] + 0xad) != 0) {
        return;
    }
    func_0203b9fc(obj[1], 0, 1, 1);
    func_0203b9fc(obj[1], 1, 1, 1);
    func_0203b9fc(obj[1], 2, 1, 1);
    func_0203b9fc(obj[1], 4, 1, 1);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov206_020ccd68);
}
