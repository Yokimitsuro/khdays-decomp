extern int SND_RegisterSeq(void *name, int mode);
extern void func_0201f390(int a);
extern int func_0201f634(int h, int a);
extern int func_020255bc(int h, int kind);
extern int func_020255d4(int h, int kind, int index);
extern void func_02028670(char *dst, int src, int a);
extern void func_0201f5ac(int h);
extern int data_ov002_0207f470;
extern char *data_ov002_0207fa28;

/* Loads the shop's item table out of the archive: opens it, walks the seven-kind entry list and
 * copies each record into the 8-byte slots at +0x60. */
void func_ov002_02078ef8(void) {
    int arc = SND_RegisterSeq(&data_ov002_0207f470, 4);
    int list;
    int count;
    int i;
    int off;
    func_0201f390(0);
    list = func_0201f634(arc, 1);
    func_0201f390(1);
    count = func_020255bc(list, 7);
    i = 0;
    if (count > 0) {
        off = i;
        do {
            func_02028670((&data_ov002_0207fa28)[1] + 0x60 + off,
                          func_020255d4(list, 7, i), 0);
            i++;
            off += 8;
        } while (i < count);
    }
    func_0201f5ac(arc);
}
