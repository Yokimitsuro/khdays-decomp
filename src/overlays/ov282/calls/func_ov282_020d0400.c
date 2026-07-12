/* Allocate the size-0x70 render instance for this actor (kind 0x64, handler 020ce738),
 * back-link it to the actor and store it at (param_1)+0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov282_020d072c(void);
void func_ov282_020d0400(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x70, (void *)&func_ov282_020d072c, 0, &out);
    *out = param_1;
    *(int *)(param_1 + 0x214) = (int)out;
}
