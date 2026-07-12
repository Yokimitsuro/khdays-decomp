/* Allocate the size-0x68 render instance for this actor (kind 0x64, handler 020cc9a8),
 * back-link it to the actor, cache the actor's render root (+0x384) at +4, and store the
 * instance at (param_1)+0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov222_020d6408(void);
void func_ov222_020d625c(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x68, (void *)&func_ov222_020d6408, 0, &out);
    *out = param_1;
    out[1] = *(int *)(*out + 0x384);
    *(int *)(param_1 + 0x214) = (int)out;
}
