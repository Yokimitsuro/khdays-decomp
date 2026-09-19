/* Load the ov266 enemy's waypoint payload: the leading word is an angle in degrees, stored at
 * +0x584 as -deg x pi (fx32) / 180; the rest are 12-byte entries appended to the +0x5e4 list
 * after it is destroyed and re-created. */
struct ent { int w[3]; };
extern void NNSi_FndDestroyDoubleList(void *p);
extern void func_01fffc24(void *p);
extern void *func_01fffca8(int a, int b, int c);
void func_ov212_020cd524(int obj, int size, int *entries) {
    struct ent *src = (struct ent *)((char *)entries + 4);
    int i;
    NNSi_FndDestroyDoubleList((void *)(obj + 0x5e4));
    func_01fffc24((void *)(obj + 0x5e4));
    *(int *)(obj + 0x584) = entries[0] * -0x3244 / 180;
    size = (int)((unsigned int)(size - 4) / 12);
    for (i = 0; i < size; i++) {
        struct ent *slot = (struct ent *)func_01fffca8(obj + 0x5e4, 12, 0x64);
        *slot = *src;
        src++;
    }
}
