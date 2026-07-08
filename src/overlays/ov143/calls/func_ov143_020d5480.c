extern int func_ov107_020c08cc(int a, int b, int c, int d, int e, int f);
extern void func_ov107_020c7500(int obj, unsigned char *msg, int arg2);

// On message [2]==5, spawn a 0x17 effect bound to sub-slot 0 (msg[3]==0) or
// sub-slot 1 (msg[3]==1), storing the handle back into the slot; then always
// forward the message to the base handler.
void func_ov143_020d5480(int *this, unsigned char *msg, int arg2)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            *(int *)(*(int *)((int)this + 0x39c) + 4) =
                func_ov107_020c08cc(*(int *)((int)this + 0x3c),
                                    *(int *)(*(int *)((int)this + 0x39c)),
                                    0x17, 0, 0x1000, (int)(msg + 5));
            break;
        case 1:
            *(int *)(*(int *)((int)this + 0x39c) + 0xc) =
                func_ov107_020c08cc(*(int *)((int)this + 0x3c),
                                    *(int *)(*(int *)((int)this + 0x39c) + 8),
                                    0x17, 0, 0x1000, (int)(msg + 5));
            break;
        }
    }
    func_ov107_020c7500((int)this, msg, arg2);
}
