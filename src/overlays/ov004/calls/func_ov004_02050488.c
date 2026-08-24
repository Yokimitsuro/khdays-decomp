typedef struct Ov004Context {
    char pad_0000[0xafc];
    int phaseFrame;
} Ov004Context;

extern Ov004Context *data_ov004_02051384;
extern void func_ov004_02050548(int frame, int mode);

void func_ov004_02050488(void) {
    data_ov004_02051384->phaseFrame++;
    if (data_ov004_02051384->phaseFrame > 0x19) {
        return;
    }
    func_ov004_02050548(data_ov004_02051384->phaseFrame - 0x10, 3);
}
