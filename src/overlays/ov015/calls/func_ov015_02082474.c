extern int func_02021980(int vm, unsigned short *pc);
extern int func_ov015_020805cc(unsigned int id, int flag);
extern void func_ov002_0207643c(int slot, int handle);
/* Script op: read a slot and an id, build the resource (id masked to u16), and publish it. */
int func_ov015_02082474(int vm, unsigned short *pc) {
    int slot = func_02021980(vm, pc);
    unsigned int id = func_02021980(vm, pc + 4);
    func_ov002_0207643c(slot, func_ov015_020805cc(id & 0xffff, 0));
    return 1;
}
