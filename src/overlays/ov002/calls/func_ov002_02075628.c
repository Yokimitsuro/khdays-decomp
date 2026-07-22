/* Finish the ov002 request: wipe the sub-object's 0x100-byte block at +0x4a4,
 * hand the request to func_ov002_02075578, take the battle-view focus and post
 * event 0x20ef with follow-up 1.
 *
 * Refuses (reporting 1) while link phase 1 is running in the boot mode gated by
 * bit 2 of data_0204c240 -- the same gate func_ov002_02062bd8 reads. Sibling of
 * func_ov002_0207568c, which drives the same request one step at a time; note
 * func_02021980's result is fetched and discarded here. */
extern int func_02021980(void *self, void *arg);
extern int func_ov002_0206b78c(void);
extern void INITi_CpuClear32_0x01ff86fc();
extern void func_ov002_02075578(void *self, void *req);
extern void func_ov002_02075460(void);
extern void func_020235e8(int event, int a, int b);
extern void func_020219b4(void *self, void *req);

extern unsigned char data_0204c240;

int func_ov002_02075628(int *self, char *req) {
    func_02021980(self, req + 8);

    if (func_ov002_0206b78c() == 1 && (data_0204c240 & 4) != 0) {
        return 1;
    }

    INITi_CpuClear32_0x01ff86fc(0, self[0x4a] + 0x4a4, 0x100);
    func_ov002_02075578(self, req);
    func_ov002_02075460();
    func_020235e8(0x20ef, 1, 1);
    func_020219b4(self, req);
    return 0;
}
