/*
 * func_ov008_0204fbc8 -- x3 (ov008/...). Tear down the current sub-screen's dynamic resources.
 * The screen context lives at data_02090f04[1] + 0x9000. Notify two owned objects (020513f0 on the
 * one at +0x59c, 02051498 on the one at +0x5a0); if the +0x5a0 object is still allocated, free it and
 * null the slot. Clear the +0x624 handle. Run the shared teardown steps 0204ef90 and 02051438, then
 * reset the screen state machine to phase 5 (0204ee28).
 *
 * The `volatile` read of the context pointer for the +0x9624 clear is a matching device: the retail
 * compiler re-loads data_02090f04[1] for every access, but mwcc 3.0/139 keeps it cached from the
 * preceding store. The volatile forces the reload; behaviour is identical.
 */
extern void func_ov008_020513f0(int obj);
extern void func_ov008_02051498(int obj);
extern void NNSi_FndFreeFromDefaultHeap(int obj);
extern void func_ov008_0204ef90(void);
extern void func_ov008_02051438(void);
extern void func_ov008_0204ee28(int phase);
extern int data_ov008_02090f04[];

void func_ov008_0204fbc8(void) {
    int obj;

    func_ov008_020513f0(*(int *)(data_ov008_02090f04[1] + 0x959c));
    func_ov008_02051498(*(int *)(data_ov008_02090f04[1] + 0x95a0));
    obj = *(int *)(data_ov008_02090f04[1] + 0x95a0);
    if (obj != 0) {
        NNSi_FndFreeFromDefaultHeap(obj);
        *(int *)(data_ov008_02090f04[1] + 0x95a0) = 0;
    }
    *(int *)(*(volatile int *)((char *)data_ov008_02090f04 + 4) + 0x9624) = 0;
    func_ov008_0204ef90();
    func_ov008_02051438();
    func_ov008_0204ee28(5);
}
