extern int func_ov002_020536bc(int id);
extern void func_ov002_020536dc(int handle, int a);
extern int func_ov002_020575e4(void);
extern void func_ov002_02053558(int id);
extern void func_ov002_020535a4(void);
extern void func_ov002_02067944(char *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_02024fd4(int h);
extern void func_ov002_020676c8(void);
extern void func_ov002_02052834(char *p);
extern char *data_ov002_0207f9fc;

/* Mission-briefing teardown: drops the five widgets, prints the two closing lines when the
 * briefing was not skipped, releases the buffers and restores the sub-engine's BG priority. */
void func_ov002_02067814(void) {
    char *self = data_ov002_0207f9fc;
    func_ov002_020536dc(func_ov002_020536bc(0x18), 0);
    func_ov002_020536dc(func_ov002_020536bc(0x19), 0);
    func_ov002_020536dc(func_ov002_020536bc(0x16), 0);
    func_ov002_020536dc(func_ov002_020536bc(0x15), 0);
    func_ov002_020536dc(func_ov002_020536bc(0x17), 0);
    if (func_ov002_020575e4() == 0) {
        func_ov002_02053558(0x57);
        func_ov002_020535a4();
        func_ov002_02053558(0x53);
        func_ov002_020535a4();
    }
    func_ov002_02067944(self + 0xc);
    {
        void *tmp = *(void **)(self + 0x20);
        if (tmp != 0) {
            NNSi_FndFreeFromDefaultHeap(tmp);
        }
    }
    func_02024fd4(*(int *)(self + 8));
    func_02024fd4(*(int *)(self + 4));
    func_ov002_020676c8();
    func_ov002_02052834(self + (0x67 << 2));
    *(volatile unsigned *)0x04001000 =
        (*(volatile unsigned *)0x04001000 & 0xffffe0ff) | (*(int *)(self + 0x2c) << 8);
    data_ov002_0207f9fc = 0;
}
