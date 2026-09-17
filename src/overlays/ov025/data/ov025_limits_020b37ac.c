/* ov025 header limits data_ov025_020b37ac, 0x020b37ac-0x020b37b0 (.rodata): the
 * width / height pair (12 x 2) copied by Ov025_SetupContext 02083e84.
 */

typedef unsigned short u16;

typedef struct Ov008HeaderLimits {
    u16 width;                /* 0x00 */
    u16 height;               /* 0x02 */
} Ov008HeaderLimits;

const Ov008HeaderLimits data_ov025_020b37ac = { 12, 2 };
