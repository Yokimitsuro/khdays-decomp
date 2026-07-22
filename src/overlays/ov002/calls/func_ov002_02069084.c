/* Scene entry gate: run the validation hook installed at +0x8b90 and give up if
 * it refuses, then let func_ov002_020693e0 have a say. Only in phase 9, and only
 * while func_02030670 agrees, does it un-quiesce first. Returns the step at
 * func_ov002_020690cc, or nothing on either refusal. +0x8b58 is the phase word
 * Ov002_GetPhaseWord reads. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_020693e0(void);
extern int func_02030670(void);
extern void func_ov002_0206e718(int mode);
extern void func_ov002_020690cc(void);

void *func_ov002_02069084(void) {
    char *root = NNSi_FndGetCurrentRootHeap();

    if ((*(int (**)(void))(root + 0x8b90))() != 0) {
        if (func_ov002_020693e0() == 0) {
            return 0;
        }
        if (*(int *)(root + 0x8b58) == 9 && func_02030670() != 0) {
            func_ov002_0206e718(1);
        }
        return (void *)&func_ov002_020690cc;
    }
    return 0;
}
