extern void func_ov002_020767ec(void *obj);

void func_ov017_020804b4(void *obj) {
    unsigned short v = *(unsigned short *)(*(int *)((char *)obj + 8) + 0x4c);
    if (v == 8) goto call1;
    if (v == 0x15) goto call2;
    return;
call1:
    func_ov002_020767ec(obj);
    return;
call2:
    func_ov002_020767ec(obj);
    return;
}
