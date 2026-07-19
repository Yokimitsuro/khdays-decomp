extern int func_ov002_0207285c(int slot);
extern int func_020235d0(unsigned short id, unsigned char kind);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern void func_ov002_020798a0(void *self);

/* Rebinds the actor model, caches the descriptor's "two-sided" bit and picks the matching draw
 * mode. */
void func_ov002_02079adc(char *self) {
    func_0202ba9c(self + 0x1c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    self[0x1c2] = (char)((unsigned int)((func_020235d0(*(unsigned short *)(self + 0x14),
                          (unsigned char)self[0x16]) & 0xfffe) << 0xf) >> 0x10 & 1);
    self[0x1ce] = *(unsigned char *)(self + 0x1c2) == 1 ? 0 : 2;
    func_ov002_020798a0(self);
}

/* PARK 2026-07-19: 88 vs 84 bytes (4 de mas). Todo casa salvo como se obtiene el segundo offset:
 *   ROM   ldr r0,=0x1c2 / strb / ldrb / cmp / adds r0,#0xc / strb   (reusa la constante)
 *   mwcc  ldr r0,=0x1c2 / strb / ldrb / cmp / ldr r0,[pc,..]  / strb (la recarga del pool)
 * Probado: `self[0x1ce]`, `self[0x1c2 + 0xc]`, un puntero `p = self + 0x1c2` con `p[0xc]`, y una
 * variable de indice `int off = 0x1c2` con `off + 0xc`. mwcc recarga en las cuatro.
 * Clase: reutilizacion de constante del pool (nueva; no encaja en las tres del censo). */
