/*
 * [nonmatching: held-value/counter r4<->r5 coloring swap (the entry ptr held across func_ov022_020831dc vs the loop counter); structurally byte-identical]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation. Left uncarved (byte-exact in the blob).
 */
extern void func_ov022_020831dc(void);
extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_ov002_02076568(void);
extern void func_ov002_02077e68(void);
extern void func_0202c4b0(void);
extern void func_ov002_02071ae0(void);
extern void func_020340d0(int arg0);
extern int data_ov022_020b2e60;

void func_ov022_02082bb0(void) {
    int i = 0;
    int e = *(int *)(((int *)&data_ov022_020b2e60)[1] + 0x20);
    func_ov022_020831dc();
    do {
        if (*(int *)(e + 0x14) != 0) WM_EndKeySharing_0x02023ad0(*(int *)(e + 0x14));
        i = i + 1;
        e = e + 4;
    } while (i < 2);
    func_ov002_02076568();
    func_ov002_02077e68();
    func_0202c4b0();
    func_ov002_02071ae0();
    func_020340d0(0);
    ((int *)&data_ov022_020b2e60)[1] = 0;
    ((int *)&data_ov022_020b2e60)[0] = 0;
}
