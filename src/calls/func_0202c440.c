extern void OS_Terminate(void);
extern void func_020110f4(void *);
extern void func_02011304(void *);

typedef struct {
    unsigned char pad0[0xa1d0];
    unsigned char arr1[16][0x28];      /* offset 0xa1d0 */
    unsigned char gap1[0x450 - 0x1d0 - 16 * 0x28];
    unsigned char arr2[16][8];         /* offset 0xa450 */
    unsigned char gap2[0x4d0 - 0x450 - 16 * 8];
    unsigned char counter;             /* offset 0xa4d0 */
} S;

extern S *data_0204c208;

unsigned char func_0202c440(void) {
    S *s = data_0204c208;
    if (s->counter < 0x10) {
        func_020110f4(&s->arr1[s->counter]);
        func_02011304(&s->arr2[s->counter]);
        s->counter++;
    } else {
        OS_Terminate();
    }
    return s->counter;
}
