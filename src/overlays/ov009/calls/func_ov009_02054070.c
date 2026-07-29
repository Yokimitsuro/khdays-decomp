typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
} Ov009GameState;

extern Ov009GameState *volatile data_0204be18;
extern const int data_ov009_02056010[4];
extern const int data_ov009_02056008[2];

extern int func_ov009_0204e440(void);
extern int func_ov009_0204e42c(void);
extern int func_ov009_020518fc(int manager, int id);
extern void func_ov009_02051a68(int manager, int entry, int visible);
extern void func_ov009_02052be0(int value);
extern long long func_020031d4(void);
extern long long func_ov009_02055f48(void);
extern u64 func_02020368(long long value, unsigned int divisor, int unused);
extern void func_ov009_02052cf4(u32 value);
extern int func_ov009_020525cc(int tracker, int tag);
extern void func_ov009_02052660(int tracker, int entry);

void func_ov009_02054070(int visible, int secondaryVisible)
{
    int manager = func_ov009_0204e440();
    int tracker = func_ov009_0204e42c();
    u8 i;

    for (i = 0; i < 4; i++) {
        int entry = func_ov009_020518fc(
            manager, data_ov009_02056010[i]);
        func_ov009_02051a68(manager, entry, visible);
    }

    for (i = 0; i < 2; i++) {
        int entry = func_ov009_020518fc(
            manager, data_ov009_02056008[i]);
        func_ov009_02051a68(manager, entry, secondaryVisible);
    }

    if (visible != 0) {
        long long elapsed;

        func_ov009_02052be0(data_0204be18->value8);
        elapsed = func_020031d4() - func_ov009_02055f48();
        func_ov009_02052cf4(
            (u32)(data_0204be18->value0 +
                  func_02020368(elapsed << 6, 0x1ff6210, 0)));
    } else {
        int entry = func_ov009_020525cc(tracker, 2);
        func_ov009_02052660(tracker, entry);
    }
}
