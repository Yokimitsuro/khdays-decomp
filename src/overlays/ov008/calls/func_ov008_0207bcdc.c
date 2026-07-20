typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 values[9];
} MissionParameterRow;

typedef struct {
    u8 pad_000[0x24];
    u32 parameters_ready;
} MissionParameterContext;

extern u8 data_ov008_0208fc9c[];
extern u8 data_ov008_0208fc9d[];
extern u8 data_ov008_0208fc9e[];
extern u8 data_ov008_0208fc9f[];
extern u8 data_ov008_0208fca0[];
extern u8 data_ov008_0208fca3[];
extern u8 data_ov008_0208fca4[];
extern MissionParameterContext *data_ov008_02090fa0;

extern void func_ov008_02081af0(int value, int channel, int duration);
extern void func_ov008_02081a6c(int value, int channel, int duration);

void func_ov008_0207bcdc(int row_index) {
    u32 offset = row_index * sizeof(MissionParameterRow);

    func_ov008_02081af0(data_ov008_0208fca0[offset], 0, 0x12c);
    func_ov008_02081af0(data_ov008_0208fc9c[offset], 1, 0x12c);
    func_ov008_02081af0(data_ov008_0208fc9e[offset], 2, 0x12c);
    func_ov008_02081af0(data_ov008_0208fc9d[offset], 3, 0x12c);
    func_ov008_02081a6c(data_ov008_0208fca3[offset], 0, 0x12c);
    func_ov008_02081a6c(data_ov008_0208fc9f[offset], 1, 0x12c);
    func_ov008_02081a6c(data_ov008_0208fca4[offset], 2, 0x12c);
    data_ov008_02090fa0->parameters_ready = 1;
}
