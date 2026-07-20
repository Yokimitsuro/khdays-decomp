typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 text[0x60];
} MissionMenuRow;

typedef struct {
    u8 pad_000[0x100];
    u8 row_count;
    u8 pad_101[0x53];
    MissionMenuRow rows[4];
} MissionContext;

typedef u16 MissionLabel[11];

extern MissionContext *volatile data_ov006_020565e4;
extern u16 data_ov006_020563d4[];
extern void func_020200e4(u16 *dst, const u16 *src);

void func_ov006_0204f9b0(MissionLabel labels[4]) {
    int i;
    u8 row_count = data_ov006_020565e4->row_count;

    for (i = 0; i < 4; i++) {
        if (i < row_count) {
            func_020200e4(labels[i], data_ov006_020565e4->rows[i].text);
        } else {
            func_020200e4(labels[i], data_ov006_020563d4);
        }
    }
}
