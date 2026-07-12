/* Initialise a spawned child: point its +8 at obj+0xb0, reset state bytes
 * +0x1c6/+0x1c7, clear the low bit of its high-byte flags at +0x60 and of the u16
 * at +0x1ae, then run the 0/1/2 dispatch sequence. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov221_020d4690(void);
extern void func_ov221_020d4768(void);
extern void func_ov221_020d4708(void);

struct hi_flags_020cfaac { unsigned short pad : 8; unsigned short flags : 8; };

void func_ov221_020d45e8(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 8) = *(int *)child + 0xb0;
    *(signed char *)(*(int *)child + 0x1c6) = 0;
    *(signed char *)(*(int *)child + 0x1c7) = -1;
    ((struct hi_flags_020cfaac *)(*(int *)child + 0x60))->flags &= ~1;
    *(unsigned short *)(*(int *)child + 0x1ae) &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov221_020d4690);
    func_0203c634(param_1, 1, (void *)&func_ov221_020d4768);
    func_0203c634(param_1, 2, (void *)&func_ov221_020d4708);
}
