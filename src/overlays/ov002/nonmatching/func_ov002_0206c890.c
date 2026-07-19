extern int func_ov002_0207285c(int slot);
extern void func_01fffe14(void);
extern int func_ov022_02088474(void);
extern char *func_ov002_02076850(int index);

typedef struct { int x, y, z; } Ov002Vec3;

/* Collects the world position of every live actor that belongs to the current party member.
 * Returns how many were written. */
int func_ov002_0206c890(char *out) {
    int count = 0;
    int i;
    int kind;
    char *obj;
    func_01fffe14();
    kind = func_ov022_02088474() & 0xff;
    for (i = 0; i < 0x40; i++) {
        obj = func_ov002_02076850(i);
        if (obj != 0 && kind == func_ov002_0207285c((unsigned char)obj[0x10])) {
            *(Ov002Vec3 *)out =
                *(*(Ov002Vec3 *(**)(void *))(*(char **)(obj + 8) + 0x2c))(obj);
            out += 0xc;
            count++;
        }
    }
    return count;
}

/* PARK 2026-07-19: 112/112 bytes. Todo casa salvo QUE registro recibe cada contador:
 *   ROM   mov r6,#0 (count) / mov r5,r6 (i = count, artefacto de copia) / and r7,r0,#0xff (kind)
 *   mwcc  mov r5,#0          / mov r6,r5                                / and r7,r0,#0xff
 * O sea el par esta invertido: mwcc mete el primero en r5 y el ROM en r6.
 * Probado: cuatro ordenes de declaracion, `count` asignada por separado, y escribir el artefacto
 * de copia a mano (`int i = count;` + `for (; i < 0x40; i++)`) -- este ultimo mueve el fallo mas
 * arriba todavia. Clase A del censo (permutacion de registros). */
