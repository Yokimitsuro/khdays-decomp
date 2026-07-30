typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
} Ov009GameState;

extern Ov009GameState *volatile data_0204be18;
extern const int data_ov025_020b4050[4];
extern const int data_ov025_020b4048[2];

extern int func_ov025_02084a7c(void);
extern int func_ov025_02084a50(void);
extern int func_ov025_0208843c(int manager, int id);
extern void func_ov025_0208884c(int manager, int entry, int visible);
extern void func_ov025_02099dd8(int value);
extern long long func_020031d4(void);
extern long long func_ov025_020b0e30(void);
extern u64 func_02020368(long long value, unsigned int divisor, int unused);
extern void func_ov025_02099eec(u32 value);
extern int func_ov025_020894b0(int tracker, int tag);
extern void func_ov025_02089544(int tracker, int entry);

void func_ov025_0209b138(int visible, int secondaryVisible)
{
    int manager = func_ov025_02084a7c();
    int tracker = func_ov025_02084a50();
    u8 i;

    for (i = 0; i < 4; i++) {
        int entry = func_ov025_0208843c(
            manager, data_ov025_020b4050[i]);
        func_ov025_0208884c(manager, entry, visible);
    }

    for (i = 0; i < 2; i++) {
        int entry = func_ov025_0208843c(
            manager, data_ov025_020b4048[i]);
        func_ov025_0208884c(manager, entry, secondaryVisible);
    }

    if (visible != 0) {
        long long elapsed;

        func_ov025_02099dd8(data_0204be18->value8);
        elapsed = func_020031d4() - func_ov025_020b0e30();
        func_ov025_02099eec(
            (u32)(data_0204be18->value0 +
                  func_02020368(elapsed << 6, 0x1ff6210, 0)));
    } else {
        int entry = func_ov025_020894b0(tracker, 2);
        func_ov025_02089544(tracker, entry);
    }
}
