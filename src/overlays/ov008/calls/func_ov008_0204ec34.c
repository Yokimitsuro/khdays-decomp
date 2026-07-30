/* func_ov008_0204ec34 -- Ov008_RecordInputCoords (164 B, 6 relocs).
 * Records the current input coordinates into the shared input log data_ov008_02090f00. Gets the
 * slot index (func_02030788) up front, and bails out if the log is not allocated or the gate
 * (func_02030640) is false. When a fresh coordinate source is supplied (arg0 != 0) it copies the
 * 3-halfword coordinate triple into the log's "current" slot. Then, if func_ov008_0204ed3c()
 * reports the recording is enabled, it snapshots the current triple into the per-slot history
 * (entries[idx], stride 6) and signals mode 3 to func_ov008_0204cadc; otherwise it signals
 * mode 2. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct InputCoords {
    u16 x;   /* 0x0 */
    u16 y;   /* 0x2 */
    u16 z;   /* 0x4 */
} InputCoords;

typedef struct InputLog {
    u8          pad_0000[0x2e];
    InputCoords entries[4];   /* 0x2e: per-slot recorded coords, stride 6 */
    InputCoords cur;          /* 0x46: current coordinates */
} InputLog;

extern InputLog *data_ov008_02090f00;
extern int  func_02030788(void);
extern int  func_02030640(void);
extern int  func_ov008_0204ed3c(void);
extern void func_ov008_0204cadc(int mode);

void func_ov008_0204ec34(InputCoords *arg0)
{
    int idx = func_02030788();
    if (data_ov008_02090f00 == 0) return;
    if (func_02030640() == 0) return;
    if (arg0 != 0) {
        InputLog *g = data_ov008_02090f00;
        g->cur = *arg0;
    }
    if (func_ov008_0204ed3c() != 0) {
        InputLog *g = data_ov008_02090f00;
        g->entries[idx] = g->cur;
        func_ov008_0204cadc(3);
    } else {
        func_ov008_0204cadc(2);
    }
}
