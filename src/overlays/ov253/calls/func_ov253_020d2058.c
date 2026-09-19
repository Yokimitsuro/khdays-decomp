/* func_ov253_020d2058 -- draw the ring entries (stride 0x38, count at +0x8c, array at +0x90):
 * resets the global orientation matrix, and for each entry with a live marker stamps twice the
 * marker into the global state's 0xc4/0xc8/0xcc slots, draws the model at the entry's +0x2c
 * with polygon id `i mod 63` on the +0x88 object's +0x78 model and reruns its +0x20 channels. */
typedef struct { int x, y, z; } VecFx32;

extern void MTX_Identity33_(int *m);
extern void func_02015880(const VecFx32 *target);
extern void func_0201574c(void);
extern void func_02016cd0(void *model, int id);
extern void func_020279e0(unsigned int *param_1);
extern int data_02047428[9];

extern struct {
    char pad0000[0xc4];
    int field_c4;
    int field_c8;
    int field_cc;
} data_02047394;

void func_ov253_020d2058(char *this) {
    int i;
    MTX_Identity33_(data_02047428);
    for (i = 0; i < *(int *)(this + 0x8c); i++) {
        char *entry = *(char **)(this + 0x90) + i * 0x38;
        int marker = *(int *)entry;
        if (marker != 0) {
            data_02047394.field_c4 = marker << 1;
            data_02047394.field_c8 = marker << 1;
            data_02047394.field_cc = marker << 1;
            func_02015880((VecFx32 *)(entry + 0x2c));
            func_0201574c();
            func_02016cd0(*(void **)(*(int *)(this + 0x88) + 0x78), i % 0x3f);
            func_020279e0((unsigned int *)(*(int *)(this + 0x88) + 0x20));
        }
    }
}
