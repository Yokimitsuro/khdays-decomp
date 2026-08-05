/*
 * Predicate over an entity/actor record (param_2). Returns 1 early when either low flag bit at
 * +0x24 is clear (b1 or b0 == 0); returns 0 when the counter at +4 is below (+2 - 1); otherwise
 * returns 1 only when the state word at +8 equals 1, else 0.
 *
 * The flag byte at +0x24 is a bitfield (both bits extracted from one ldrb via lsl/lsrs); the result
 * register is seeded to 0 up front so the counter-bounds case returns it directly (bxlt).
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct { u8 b0:1; u8 b1:1; } Fl;

int func_ov002_02054b40(int param_1, char *param_2)
{
    int result = 0;
    Fl *f = (Fl *)(param_2 + 0x24);
    if (f->b1 == 0) return 1;
    if (f->b0 == 0) return 1;
    if (*(u16 *)(param_2 + 4) < *(u16 *)(param_2 + 2) - 1) return result;
    if (*(int *)(param_2 + 8) == 1) result = 1;
    return result;
}
