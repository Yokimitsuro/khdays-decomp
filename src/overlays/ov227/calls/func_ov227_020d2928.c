/* Spawn the child at +0x3e8; if it fails idle at state 2, else kick anim 0x18 and dispatch. */
extern int func_ov107_020cab14(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov227_020d2994(int);
void func_ov227_020d2928(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int child = func_ov107_020cab14(*(int *)owner, 0);
    *(int *)(*(int *)owner + 0x3e8) = child;
    if (*(int *)(*(int *)owner + 0x3e8) == 0) {
        *(signed char *)(*(int *)owner + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        func_ov107_020c9264(*(int *)owner, 0x18, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov227_020d2994);
    }
}
