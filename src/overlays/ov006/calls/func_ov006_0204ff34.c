typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 values[9];
} MissionParameterRow;

typedef struct {
    u8 pad_000[0x24];
    u32 parameters_ready;
} MissionParameterContext;

extern u8 data_ov006_020561e0[];
extern u8 data_ov006_020561e1[];
extern u8 data_ov006_020561e2[];
extern u8 data_ov006_020561e3[];
extern u8 data_ov006_020561e4[];
extern u8 data_ov006_020561e7[];
extern u8 data_ov006_020561e8[];
extern MissionParameterContext *data_ov006_02056660;

extern void func_ov006_02055d80(int value, int channel, int duration);
extern void func_ov006_02055cfc(int value, int channel, int duration);

void func_ov006_0204ff34(int row_index) {
    u32 offset = row_index * sizeof(MissionParameterRow);

    func_ov006_02055d80(data_ov006_020561e4[offset], 0, 0x12c);
    func_ov006_02055d80(data_ov006_020561e0[offset], 1, 0x12c);
    func_ov006_02055d80(data_ov006_020561e2[offset], 2, 0x12c);
    func_ov006_02055d80(data_ov006_020561e1[offset], 3, 0x12c);
    func_ov006_02055cfc(data_ov006_020561e7[offset], 0, 0x12c);
    func_ov006_02055cfc(data_ov006_020561e3[offset], 1, 0x12c);
    func_ov006_02055cfc(data_ov006_020561e8[offset], 2, 0x12c);
    data_ov006_02056660->parameters_ready = 1;
}
