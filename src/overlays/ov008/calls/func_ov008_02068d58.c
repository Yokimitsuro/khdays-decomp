typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
} Ov009GameState;

extern Ov009GameState *volatile data_0204be18;
extern const int data_ov008_0208f4f0[4];
extern const int data_ov008_0208f4e8[2];

extern int func_ov008_02050c54(void);
extern int func_ov008_02050c28(void);
extern int func_ov008_02054788(int manager, int id);
extern void func_ov008_02054ba4(int manager, int entry, int visible);
extern void func_ov008_020679f8(int value);
extern long long func_020031d4(void);
extern long long func_ov008_0208becc(void);
extern u64 func_02020368(long long value, unsigned int divisor, int unused);
extern void func_ov008_02067b0c(u32 value);
extern int func_ov008_02055808(int tracker, int tag);
extern void func_ov008_0205589c(int tracker, int entry);

void func_ov008_02068d58(int visible, int secondaryVisible)
{
    int manager = func_ov008_02050c54();
    int tracker = func_ov008_02050c28();
    u8 i;

    for (i = 0; i < 4; i++) {
        int entry = func_ov008_02054788(
            manager, data_ov008_0208f4f0[i]);
        func_ov008_02054ba4(manager, entry, visible);
    }

    for (i = 0; i < 2; i++) {
        int entry = func_ov008_02054788(
            manager, data_ov008_0208f4e8[i]);
        func_ov008_02054ba4(manager, entry, secondaryVisible);
    }

    if (visible != 0) {
        long long elapsed;

        func_ov008_020679f8(data_0204be18->value8);
        elapsed = func_020031d4() - func_ov008_0208becc();
        func_ov008_02067b0c(
            (u32)(data_0204be18->value0 +
                  func_02020368(elapsed << 6, 0x1ff6210, 0)));
    } else {
        int entry = func_ov008_02055808(tracker, 2);
        func_ov008_0205589c(tracker, entry);
    }
}
