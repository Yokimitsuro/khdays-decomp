/* ov256 .rodata head 0x020d2444-0x020d2594: pose tables of the actor, one object per function in
 * the original unit's order (the templates that follow are in ov256_templates_020d2594.c). */

/* func_ov256_020cbfc8 (constructor): poses of the 16 hidden parts. */
typedef struct { int id[16]; } PartPoses;

/* Ov256_PlayRigMove (020ccba4): per-move poses of the +0x384 body rig and the +0x3ac tail rig. */
typedef struct { int id[34]; } MovePoses;

const PartPoses data_ov256_020d2444 = { {
    80, 81, 82, 83, 84, 84, 85, 86, 87, 88, 89, 89, 90, 90, 91, 92,
} };

const MovePoses data_ov256_020d2484 = { {
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
} };

const MovePoses data_ov256_020d250c = { {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
} };
