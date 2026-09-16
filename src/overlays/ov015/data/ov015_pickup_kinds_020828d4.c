/* ov015 .rodata 0x020828d4-0x020828e4: the per-kind pickup rows read by Ov015_SpawnPickup
 * (020801c8: handler block and rise scale), Ov015_PickupLoad (0207fac0) and
 * Ov015_PickupShow (0207fb8c): kind 0 is a pickup with a model driven by
 * Ov015_PickupUpdate (0207fe0c, rise scale 0x3c), kind 1 a model-less pickup whose
 * state function is Ov015_PickupTakenStep (0207ffd0).  The rise byte of row 0 is also
 * addressed as data_ov015_020828d8. */
typedef unsigned char u8;

typedef struct Ov015PickupKindRow {
    void *pHandlers;          /* 0x00: state function of the kind */
    u8   nRise;               /* 0x04: rise speed scale (random range) */
    u8   pad_05[3];
} Ov015PickupKindRow;

extern void func_ov015_0207fe0c(void);   /* Ov015_PickupUpdate */
extern void func_ov015_0207ffd0(void);   /* Ov015_PickupTakenStep */

const Ov015PickupKindRow data_ov015_020828d4[2] = {
    { (void *)func_ov015_0207fe0c, 0x3c },
    { (void *)func_ov015_0207ffd0, 0 },
};
