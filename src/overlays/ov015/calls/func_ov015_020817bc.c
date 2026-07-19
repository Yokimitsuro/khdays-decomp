extern int func_ov002_0207285c(int slot);
extern void func_ov015_02081288(int id, void *p, int arg, void *fn, void *self);
extern void func_ov015_02081694(void);

/* Starts the actor's scripted routine with func_ov015_02081694 as its per-frame hook. */
void func_ov015_020817bc(char *self, int arg) {
    func_ov015_02081288(func_ov002_0207285c((unsigned char)self[0x10]), self + 0x488, arg,
                        (void *)&func_ov015_02081694, self);
}
