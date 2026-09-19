/* Kick anim 4, send sprite request 4 (data_ov244_020d3724 entry 10 with the actor's +2 id),
 * clear the +9 byte and +0x1c word, then dispatch to 020d03a0. */
extern void func_02031384(int a, void *req, int b);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern unsigned short data_ov244_020d3724[];
extern int func_ov244_020d03a0(int);
void func_ov244_020d032c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    unsigned short pair[2];
    unsigned short *pp;
    func_ov107_020c9264(*(int *)owner, 4, 0);
    pp = pair;
    pp[0] = data_ov244_020d3724[20];
    pp[1] = data_ov244_020d3724[21];
    pp[0] = *(unsigned short *)(*(int *)owner + 2);
    func_02031384(4, pp, 4);
    *(signed char *)(owner + 9) = 0;
    *(int *)(owner + 0x1c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov244_020d03a0);
}
