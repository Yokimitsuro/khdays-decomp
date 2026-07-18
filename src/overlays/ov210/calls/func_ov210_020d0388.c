/*
 * func_ov210_020d0388 -- x3. Set up a sub-object (arg5) bound to owner arg2. Init it (0202a440),
 * clear its +0xc field, then bind the owner's node p = *(arg2+0x88): register p's callback
 * (02014b5c with p+0x20 and *(p+0x78)) and attach it to arg5 (0202a388(arg5, p, arg3, 0xc)). Finally
 * link arg5 into the owner (0203b9ac) and configure it (0203b9fc(arg2, 0, 0, arg4)). arg1 unused.
 */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);

void func_ov210_020d0388(int arg1, int arg2, int arg3, int arg4, int arg5) {
    int p;

    func_0202a440(arg5);
    *(int *)(arg5 + 0xc) = 0;
    p = *(int *)(arg2 + 0x88);
    func_02014b5c(p + 0x20, *(int *)(p + 0x78));
    func_0202a388(arg5, p, arg3, 0xc);
    func_0203b9ac(arg2, arg5);
    func_0203b9fc(arg2, 0, 0, arg4);
}
