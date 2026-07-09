extern void func_ov008_020551a4(void *);
extern void func_ov008_02055344(void *);
struct ov008_020554e4_flags {
    unsigned char _pad[0x2c];
    unsigned char flag : 1;
};

void func_ov008_020554e4(char *obj)
{
    func_ov008_020551a4(obj);
    if (((struct ov008_020554e4_flags *)obj)->flag != 0) {
        func_ov008_02055344(obj);
    }
}
