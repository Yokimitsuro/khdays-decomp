extern void func_ov022_0209093c(short *p, int a, int b);
extern void func_ov022_0209c870(int obj);
extern int func_ov022_020926f8(void *p);
extern void func_ov022_02092844(void *p);
extern int func_ov022_02092af8(void *p);
extern void func_ov022_02092d68(void *p);
extern int func_ov022_0209405c(void *p);
extern void func_ov022_020942c4(void *p);
extern int func_ov022_02092ff0(void *p);
extern void func_ov022_02093400(void *p);
extern void func_ov022_02093ea8(int p);
extern void func_ov022_0209b100(int obj);
extern void func_ov022_0209d3a0(int obj);

struct Obj020a0710 { char pad[0x464]; unsigned long long flags464; };
struct Bit694 { unsigned char lo1 : 1; };

void func_ov022_020a0710(int obj, int param2, int param3, int param4) {
    func_ov022_0209093c((short *)(obj + 0x2288), param2, param3);
    if ((*(unsigned long long *)obj & 0x200LL) != 0) return;
    if (((struct Bit694 *)(obj + 0x694))->lo1) {
        func_ov022_0209c870(obj);
        if (func_ov022_020926f8((void *)(obj + 0x1070))) func_ov022_02092844((void *)(obj + 0x1070));
        if (func_ov022_02092af8((void *)(obj + 0x1198))) func_ov022_02092d68((void *)(obj + 0x1198));
        if (func_ov022_0209405c((void *)(obj + 0x1c8c))) func_ov022_020942c4((void *)(obj + 0x1c8c));
        if (func_ov022_02092ff0((void *)(obj + 0x1318)) &&
            (((struct Obj020a0710 *)obj)->flags464 & 0x80LL) != 0)
            func_ov022_02093400((void *)(obj + 0x1318));
        func_ov022_02093ea8(obj + 0x1da8);
        func_ov022_0209b100(obj);
        func_ov022_0209d3a0(obj);
    }
}
