typedef struct Fx32Pair {
    int x;
    int y;
} Fx32Pair;

typedef struct Ov004Context {
    char pad_0000[0x5544];
    void *objects[3];
    char pad_5550[4];
    int stopMotion;
    char pad_5558[0x2c];
    int transitionState;
    int positionY;
} Ov004Context;

extern Ov004Context *data_ov004_02051384;

extern void func_0203257c(void *manager, void *object, Fx32Pair *position);

void func_ov004_02050400(void) {
    if (data_ov004_02051384->stopMotion != 0) {
        data_ov004_02051384->transitionState = 2;
        return;
    }

    {
        Fx32Pair position;
        int y;

        position.x = 0x80000;
        position.y = data_ov004_02051384->positionY;
        y = data_ov004_02051384->positionY;
        if (y < 0x8a000) {
            y += 0x36;
            y += 0xb00;
            data_ov004_02051384->positionY = y;
        } else {
            data_ov004_02051384->transitionState = 2;
        }

        func_0203257c((char *)data_ov004_02051384 + 0xb0c,
                      data_ov004_02051384->objects[0], &position);
    }
}
