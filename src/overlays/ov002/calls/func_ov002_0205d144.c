/* Close the ov002 sub-session: release the lookup at +0x5e8, publish four of its
 * fields to the globals the rest of the game reads, and drop the pointer. */
extern int data_ov002_0207f620;
extern unsigned char data_0204c4f0;
extern unsigned char data_0204c4f2;
extern unsigned char data_0204c4f3;
extern int data_0204c4fc;

extern void func_ov002_02052834(void *ref);

void func_ov002_0205d144(void) {
    unsigned char *self = *(unsigned char **)&data_ov002_0207f620;

    func_ov002_02052834(self + 0x5e8);
    data_0204c4f0 = self[1];
    data_0204c4f3 = self[0];
    data_0204c4f2 = self[4];
    data_0204c4fc = *(int *)(self + 0x10);
    *(int *)&data_ov002_0207f620 = 0;
}
