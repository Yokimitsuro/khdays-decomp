extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern int func_0202bf84(unsigned short id);
extern void func_02021418(void *slot, int a, void *out, int b, int c);
extern void func_0202ba78(unsigned short a, unsigned short b, int c, void *pos);
extern void func_0202beb8(unsigned short id, int on);
extern void func_ov023_020887dc(void *entity, int a, void *pos, int h, int id);
extern void MTX_Identity43_(int *m);
extern void MTX_RotY43_(int *m, int sin, int cos);
extern void MTX_MultVec43(const void *v, const int *m, void *dst);
extern void VEC_Add(const void *a, const void *b, void *dst);
extern char data_0203d210;

typedef struct { int x, y, z; } Ov023Vec3;

/* Script command: teleports the entity to a point offset from a second one, rotated into that
 * entity's facing. Operand 3, when present, overrides the forward distance. */
int func_ov023_0208632c(int ctx, char *args) {
    int e1 = func_02021980(ctx, args);
    int e2 = func_02021980(ctx, args + 8);
    int side = func_02021994(ctx, args + 0x10);
    int id = func_02020d10(ctx, e1);
    Ov023Vec3 facingOut;
    Ov023Vec3 pos;
    int mtx[12];
    Ov023Vec3 offset;
    char *world = *(char **)(ctx + 0x128);
    char *node;
    int yaw;
    int handle;
    unsigned short facing;
    int i;
    int j;
    func_02021418(world + 0x30 + *(int *)(world + 0x488) * 0x104, 0, &facingOut, 0, 0);
    node = func_0202bfcc((unsigned short)e2);
    yaw = *(unsigned short *)(node + 0x80);
    pos = *(Ov023Vec3 *)(node + 0xa8);
    handle = func_0202bf84((unsigned short)e2);
    offset.z = *(short *)(args + 0x18) == 0 ? side : func_02021994(ctx, args + 0x18);
    facing = (unsigned short)facingOut.x;
    offset.x = 0;
    offset.y = side;
    MTX_Identity43_(mtx);
    i = (int)facing >> 4;
    j = i * 2;
    MTX_RotY43_(mtx, (int)*(short *)((char *)&data_0203d210 + j * 2),
                (int)*(short *)((char *)&data_0203d210 + (j + 1) * 2));
    MTX_MultVec43(&offset, mtx, &offset);
    offset.x = -offset.x;
    VEC_Add(&pos, &offset, &pos);
    func_0202ba78((unsigned short)id, (unsigned short)handle, 0, &pos);
    node = func_0202bfcc((unsigned short)id);
    if ((*(int *)node & 0x20) == 0) {
        *(short *)(node + 0x80) = (short)yaw;
        *(unsigned short *)(node + 4) |= 0x20;
    }
    func_0202beb8((unsigned short)id, 1);
    if (*(char **)(*(char **)(ctx + 0x128) + 0x440) != 0) {
        func_ov023_020887dc(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64,
                            0, &pos, handle, id);
    }
    return 1;
}

/* PARK 2026-07-19: 324/324 bytes, MISMO numero de instrucciones, diferencia de 2:
 *
 *   ROM   ldr r1,[sp,#0x54] / str r0,[sp,#0x14] / lsls r1,r1,#16 / lsrs r6,r1,#16
 *   mwcc  str r0,[sp,#0x14] / ldr r0,[sp,#0x54] / lsls r0,r0,#16 / lsrs r6,r0,#16
 *
 * El ROM adelanta la carga de facingOut y usa r1 de scratch; mwcc guarda primero y reusa r0.
 * Clase "planificacion + se salta el registro libre mas bajo" (deferred-ties). Probado: mover
 * `facing = ...` a cuatro posiciones distintas del cuerpo, `facing` como int y como unsigned short,
 * `facingOut` como struct y como int[3], y el ternario como if/else. Todo da la misma pareja.
 * TODO LO DEMAS CASA -- incluidos el layout de pila (facingOut es una struct de 12 bytes en
 * sp+0x54, por eso el frame es 0x60) y el indice de la tabla de senos escrito como `j = i*2;
 * tabla[j*2], tabla[(j+1)*2]` (con `i*4` mwcc lo pliega y sale otro shift). */
