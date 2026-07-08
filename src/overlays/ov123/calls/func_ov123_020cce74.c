struct u16pair { unsigned short a, b; };

extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern short data_ov123_020ce2ac;
extern void func_ov123_020cceec(void);

// Reset the node's timers, switch to mode 3, then hand the default parameter pair
// (data_ov123_020ce2ac) to the object's installed method before advancing.
void func_ov123_020cce74(int *this)
{
    int node = this[1];
    struct u16pair params;
    void (*method)(int, struct u16pair *, int);
    *(int *)(node + 0x20) = 0;
    func_ov107_020c9264(*(int *)node, 3, 0);
    *(int *)(node + 0x28) = 0;
    *(int *)(node + 0x2c) = 0;
    params = *(struct u16pair *)&data_ov123_020ce2ac;
    method = *(void (**)(int, struct u16pair *, int))(*(int *)node + 0x24);
    if (method != 0) {
        method(*(int *)node, &params, 4);
    }
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov123_020cceec);
}
