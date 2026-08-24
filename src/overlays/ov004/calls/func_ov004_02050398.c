typedef unsigned char u8;

typedef struct Ov004Context {
    u8 pad_0000[0x5544];
    void *objects[3];
} Ov004Context;

extern Ov004Context *data_ov004_02051384;

extern void func_020327e0(void *manager, int value);
extern void func_020324ac(void *manager, void *object);
extern void func_0203253c(void *manager);

void func_ov004_02050398(void) {
    int i;

    func_020327e0((char *)data_ov004_02051384 + 0xb0c, 0);
    for (i = 0; i < 3; i++) {
        func_020324ac((char *)data_ov004_02051384 + 0xb0c,
                      data_ov004_02051384->objects[i]);
    }
    func_0203253c((char *)data_ov004_02051384 + 0xb0c);
}

