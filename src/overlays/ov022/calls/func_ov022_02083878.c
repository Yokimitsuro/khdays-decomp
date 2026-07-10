extern void func_ov022_02083c08(int a);
extern int func_ov002_0205196c(void);
extern int func_ov022_0208a2a0(void);
extern int func_01fffe14(void);
extern void func_ov022_02089e90(int state, int id, int obj, int a);
extern void func_ov022_0208872c(int a);
extern void func_020340d0(int a);
extern void func_ov022_02082d8c(void);
extern int data_0204be04;
extern int data_ov022_020b2e60;

struct Fld02083878 { unsigned short _lo : 3; unsigned short id : 13; };

int func_ov022_02083878(void) {
    int r = 0;
    if (*(unsigned char *)&data_0204be04 != 0) return r;
    func_ov022_02083c08(1);
    if (func_ov002_0205196c() != 0) {
        int obj = func_ov022_0208a2a0();
        func_ov022_02089e90(func_01fffe14(),
                            ((struct Fld02083878 *)(obj + 0xc))->id,
                            obj,
                            *(unsigned short *)(obj + 0xe));
        func_ov022_0208872c(1);
        *(signed char *)(data_ov022_020b2e60 + 0x3e) = 2;
        func_020340d0(0);
        r = (int)func_ov022_02082d8c;
    }
    return r;
}
