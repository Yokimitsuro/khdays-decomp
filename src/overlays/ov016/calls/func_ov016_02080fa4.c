/* Resolve five descriptors, feed the last three plus the second (truncated to 16
 * bits) through func_ov016_0207feb8, and store the result into the ov002 module
 * slot named by the first (func_ov002_0207643c = Ov002_SetModuleSlot). The five
 * descriptors use three different resolvers: 0 and 8 go through func_02021980,
 * 0x10 through func_02021948, 0x18 and 0x20 through func_02021994. Always
 * reports success. */
extern int func_02021980(void *self, void *desc);
extern int func_02021948(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov016_0207feb8(unsigned short key, int *args);
extern void func_ov002_0207643c(int slot, int value);

int func_ov016_02080fa4(void *self, char *descs) {
    int args[3];
    int slot = func_02021980(self, descs);
    int key = func_02021980(self, descs + 8);

    args[0] = func_02021948(self, descs + 0x10);
    args[1] = func_02021994(self, descs + 0x18);
    args[2] = func_02021994(self, descs + 0x20);

    func_ov002_0207643c(slot, func_ov016_0207feb8((unsigned short)key, args));
    return 1;
}
