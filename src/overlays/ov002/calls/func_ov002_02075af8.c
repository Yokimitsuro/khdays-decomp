/* Resolve four consecutive 8-byte descriptors and hand the results to
 * func_ov002_0206e524. The first two go through func_02021980, the last two
 * through func_02021948 -- the split is deliberate, not a transcription slip.
 * Same shape as Ov002_ResolveFourDescriptors, which uses func_02021980 for all
 * four. Always reports success. */
extern int func_02021980(void *self, void *desc);
extern int func_02021948(void *self, void *desc);
extern void func_ov002_0206e524(int a, int b, int c, int d);

int func_ov002_02075af8(void *self, char *descs) {
    int a = func_02021980(self, descs);
    int b = func_02021980(self, descs + 8);
    int c = func_02021948(self, descs + 0x10);
    int d = func_02021948(self, descs + 0x18);

    func_ov002_0206e524(a, b, c, d);
    return 1;
}
