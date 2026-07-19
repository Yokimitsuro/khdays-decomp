extern void func_ov002_02053558(int id);
extern void func_ov002_020535a4(void);
extern void func_ov002_0205b234(int slot);
extern void func_ov002_02053cd4(int id);

/* Redraws the party strip: the header line, the four member rows and the two side panels. */
void func_ov002_0205c9c4(void) {
    int i;
    func_ov002_02053558(0x51);
    func_ov002_020535a4();
    for (i = 0; i < 4; i++) {
        func_ov002_0205b234(i);
    }
    func_ov002_02053cd4(9);
    func_ov002_02053cd4(0xb);
}
