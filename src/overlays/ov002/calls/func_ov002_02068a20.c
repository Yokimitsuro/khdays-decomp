extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_0206ebac(void);
extern int func_ov002_020573cc(void);
extern int func_02030694(void);
extern int func_ov002_0206ec2c(void);
extern void func_ov002_02068a60(void);

/* Picks the follow-up step for the save prompt: the confirm page when the slot is usable and
 * nothing else objects, otherwise nothing. */
void *func_ov002_02068a20(void) {
    *(char *)(NNSi_FndGetCurrentRootHeap() + 0x8b68) = 0x20;
    if (func_ov002_0206ebac() != 0 && func_ov002_020573cc() == 0) {
        if (func_02030694() != 0 && func_ov002_0206ec2c() == 0) {
            return 0;
        }
        return (void *)&func_ov002_02068a60;
    }
    return 0;
}
