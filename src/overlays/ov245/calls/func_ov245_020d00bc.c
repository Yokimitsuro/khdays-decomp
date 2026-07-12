/* Refresh +0x390 via 020cab14; unless it and the linked node's +0x4c4 are live, just latch
 * sub-state 2, otherwise kick anim 2, clear +0x30/+0x3d and advance to 020d013c. */
extern int func_ov107_020cab14(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov245_020d013c(int);
void func_ov245_020d00bc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(*(int *)owner + 0x390) = func_ov107_020cab14(*(int *)owner, 0);
    if (*(int *)(*(int *)owner + 0x390) == 0 ||
        *(int *)(*(int *)(*(int *)owner + 0x3dc) + 0x4c4) == 0) {
        *(unsigned char *)(*(int *)owner + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        func_ov107_020c9264(*(int *)owner, 2, 0);
        *(int *)(owner + 0x30) = 0;
        *(unsigned char *)(owner + 0x3d) = 0;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020d013c);
    }
}
