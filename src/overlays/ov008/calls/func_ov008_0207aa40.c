/* Once per open (guard +0x48 within the 0x4a0 buffer): if the session is ready, run the ready
 * hook and blit the 0x1c-entry list at +8; otherwise blit the 6-entry fallback list at +0x40.
 * Either way clear the 4-byte header at +0. */
struct Ov008ListContext {
    char _pad0[0x4a0];
    unsigned char pad04a0[0x50];
};
extern struct Ov008ListContext *data_ov008_02090f24;
extern int func_02030694(void);
extern void func_ov008_02079ae4(void);
extern void func_02031258(int cmd, void *buf, int n);

int func_ov008_0207aa40(void) {
    if (*(int *)(data_ov008_02090f24->pad04a0 + 0x48) == 0) {
        if (func_02030694()) {
            func_ov008_02079ae4();
            func_02031258(0xd, data_ov008_02090f24->pad04a0 + 8, 0x1c);
            *(int *)data_ov008_02090f24->pad04a0 = 0;
        } else {
            *(int *)data_ov008_02090f24->pad04a0 = 0;
            func_02031258(0xd, data_ov008_02090f24->pad04a0 + 0x40, 6);
        }
    }
    return 0;
}
