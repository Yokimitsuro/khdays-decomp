/* Post a link message: build it from the result context's leading halfword at
 * root+0x8ba8 with kind 3, stamp the caller's two bytes into the record at
 * root+0x8d6c, send it, and mark the result slot free again (-1). */
extern void func_ov002_0206b9e4(int value, int arg, int kind);
extern void func_0201f924(void *record, void *payload);

extern char *data_ov002_0207fa00;

void func_ov002_0206b0b8(int slot, void *payload, int arg, int flag) {
    char *root = data_ov002_0207fa00;
    char *result = root + 0x8ba8;
    char *record = root + 0x8d6c;

    func_ov002_0206b9e4(*(short *)result, arg, 3);
    record[0xc] = (char)slot;
    record[0xd] = (char)flag;
    func_0201f924(record, payload);
    *(int *)(result + 0xc) = -1;
}
