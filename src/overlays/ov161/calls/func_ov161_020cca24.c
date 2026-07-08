extern void func_0203b9fc(int subitem, int a, int b, int c);
extern void func_0203c634(int obj, int idx, int cb);
extern void func_ov161_020ccafc(void);
extern void func_ov161_020ccac8(void);

// Resolve the linked sub-object (node[0][0x3c4][0x28]) into node[1], clear its
// active bit (obj[0x5c] bit1), reset its sub-state to 2 then 0, and install the
// two follow-up callbacks in slots 1 and 2.
void func_ov161_020cca24(int *this)
{
    int node = this[1];
    int obj = *(int *)(*(int *)(*(int *)node + 0x3c4) + 0x28);
    *(int *)(node + 4) = obj;
    *(unsigned int *)(obj + 0x5c) &= ~2u;
    func_0203b9fc(*(int *)(node + 4), 2, 0, 0);
    func_0203b9fc(*(int *)(node + 4), 0, 0, 0);
    func_0203c634((int)this, 1, (int)&func_ov161_020ccafc);
    func_0203c634((int)this, 2, (int)&func_ov161_020ccac8);
}
