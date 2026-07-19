extern void func_ov002_0207687c(char *self);
extern int func_ov002_0206b828(void);
extern void func_ov002_0206b910(void *desc, char *out);
extern int func_02030670(void);
extern void func_ov002_0206b9b4(int mask);
extern int func_ov002_0206b9cc(void);
extern void func_ov002_0206b97c(void);
extern void func_ov002_02076bd8(char *self, int a);
extern void func_ov002_0207cea4(void);
extern int data_ov015_02082900;

/* Step 2 of the cutscene: once the loader is idle, reads the next command, drops the two skip
 * flags on the retail build and hands over to step 3. */
void *func_ov015_02080540(char *self) {
    func_ov002_0207687c(self);
    if (*(unsigned char *)(self + 0x50) == 2) {
        if (func_ov002_0206b828() != 0) {
            return 0;
        }
        func_ov002_0206b910(&data_ov015_02082900, self + 0x51);
        if (func_02030670() != 0) {
            func_ov002_0206b9b4(0);
        } else {
            func_ov002_0206b9b4((unsigned char)(func_ov002_0206b9cc() & ~0xa));
        }
        func_ov002_0206b97c();
        *(char *)(self + 0x50) = 3;
        func_ov002_02076bd8(self, 0);
        return (void *)&func_ov002_0207cea4;
    }
    return 0;
}
