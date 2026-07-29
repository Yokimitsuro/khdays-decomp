/* func_ov011_0205dac8 -- Ov011_SetupTitleTileSurfaces (200 B, 7 relocs).
 * One-shot setup of the title's tile surfaces: two func_020136b0 registrations for the
 * scene-global surfaces at pScene+0x23a94 / +0x23aa0, then four func_ov011_0205da60
 * tile-surface config submits for the per-slot regions (offsets 0x24, 0x60, 0x10964,
 * 0x109a0 with their pixel sources at 0x9c, 0x89c, 0x109dc, 0x111dc). pScene is read
 * by name on every use. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov011Globals { u32 nTimer; u8 *pScene; } Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern void func_020136b0(int *a, int *b);
extern void func_ov011_0205da60(int a, int b, int c, int d);

void func_ov011_0205dac8(void)
{
    func_020136b0((int *)(data_ov011_0205e960.pScene + 0x23a94),
                  *(int **)(data_ov011_0205e960.pScene + 0x23a9c));
    func_020136b0((int *)(data_ov011_0205e960.pScene + 0x23aa0),
                  *(int **)(data_ov011_0205e960.pScene + 0x23aa8));
    func_ov011_0205da60((int)(data_ov011_0205e960.pScene + 0x24), 0x20,
                        (int)(data_ov011_0205e960.pScene + 0x9c), 5);
    func_ov011_0205da60((int)(data_ov011_0205e960.pScene + 0x60), 3,
                        (int)(data_ov011_0205e960.pScene + 0x89c), 5);
    func_ov011_0205da60((int)(data_ov011_0205e960.pScene + 0x10964), 0x20,
                        (int)(data_ov011_0205e960.pScene + 0x109dc), 0x15);
    func_ov011_0205da60((int)(data_ov011_0205e960.pScene + 0x109a0), 3,
                        (int)(data_ov011_0205e960.pScene + 0x111dc), 0x15);
}
