/* main .rodata 0x0204208c-0x02042124: NNS G3D material masks, matrix/quaternion helper constants
 * and the class descriptor of the session's transfer-channel task. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short fx16;
typedef int fx32;

typedef struct VecFx16 {
    fx16 x, y, z;
    fx16 pad;
} VecFx16;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

/* Quaternion as the game stores it: w first, then the vector part. */
typedef struct Quat {
    fx32 w, x, y, z;
} Quat;

typedef void (*GameClassFn)(void);

/* InstantiateClass (02023930 / 02023960) descriptor, as in the overlay class files. */
typedef struct GameClassDescriptor {
    u16 nClassId;             /* 0x00 */
    u16 nGroupId;             /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int ***pArena;            /* 0x10 */
} GameClassDescriptor;

extern void func_02031228(void);
extern void func_0203123c(void);
extern int **data_0204c024;

/* NitroSystem G3D material SBC (func_01ffbbf0): the diffuse/ambient colour-field mask selected by
 * the material's three flag bits. */
const u32 data_0204208c[8] = {
    0x00000000, 0x00007fff, 0x7fff0000, 0x7fff7fff,
    0x00008000, 0x0000ffff, 0x7fff8000, 0x7fffffff,
};

/* For each element of a 3x3 matrix, the four element indices (row-major) of its 2x2 minor:
 * the cofactor walk of the 3x3 inverse (func_01ffae5c, func_01ffc164, func_02026b70). */
const u8 data_020420ac[9][4] = {
    { 4, 5, 7, 8 }, { 3, 5, 6, 8 }, { 3, 4, 6, 7 },
    { 1, 2, 7, 8 }, { 0, 2, 6, 8 }, { 0, 1, 6, 7 },
    { 1, 2, 4, 5 }, { 0, 2, 3, 5 }, { 0, 1, 3, 4 },
};

/* The unit Y axis as a VecFx16 (func_02028a64). */
const VecFx16 data_020420d0 = { 0, 0x1000, 0, 0 };

/* Rotation quaternion {w 0, x sqrt(1/2), y sqrt(1/2), z 0}: half a turn about the (1, 1, 0)
 * diagonal, applied by func_0202a984. */
const Quat data_020420d8 = { 0, 0xb50, 0xb50, 0 };

/* The -Z unit vector (func_0202e1cc). */
const VecFx32 data_020420e8 = { 0, 0, -0x1000 };

/* Cyclic successor of each axis {1, 2, 0} for the matrix-to-quaternion conversion
 * (func_0202ea48, j/k from i). */
const u8 data_020420f4[4] = { 1, 2, 0, 0 };

/* The identity quaternion {w 1.0, 0, 0, 0}: default orientation of transforms and rigs. */
const Quat data_020420f8 = { 0x1000, 0, 0, 0 };

/* Handle ids patched into the transfer descriptor for its two channels (func_02030e7c). */
const int data_02042108[2] = { 15, 17 };

/* Class descriptor of the transfer-channel task func_02030e7c instantiates twice
 * (func_02023930): class 2, group 0xf, constructor 02031228, method 0203123c, a 4-byte state,
 * arena data_0204c024. */
const GameClassDescriptor data_02042110 = {
    2, 0xf, func_02031228, func_0203123c, 4, &data_0204c024,
};
