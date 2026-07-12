/* Record param_1 at (*global)+0x16; if the object is idle (byte +1 == 0), (re)issue
 * its request via func_ov002_0205ae08 with the "first" flag set when byte +0 is 0. */
extern void func_ov002_0205ae08(int a, int b, int first);
extern int data_ov002_0207f620;

void func_ov002_0205de40(int param_1) {
    int base = *(int *)&data_ov002_0207f620;
    *(unsigned short *)(base + 0x16) = param_1;
    if (*(unsigned char *)(base + 1) == 0) {
        int first;
        if (*(unsigned char *)base != 0) {
            first = 0;
        } else {
            first = 1;
        }
        func_ov002_0205ae08(*(unsigned short *)(base + 0x14), *(int *)(base + 0xc), first);
    }
}
