/* ov002 panel field scales, 0x0207dcc0-0x0207dd14.
 *
 * Twenty-one Q12 values read by Ov002_GetPanelField0134, running about 0.96 to 2.37
 * with 8192 meaning exactly 2.0. The last five are zero and unused.
 */

typedef int fx32;

const fx32 data_ov002_0207dcc0[21] = {
     8888,  7987,  9380,  9011,  9708,  7905,  8192,
     8806,  8233,  8192,  8438,  7455,  6758,  6308,
     3932,  7086,     0,     0,     0,     0,     0,
};
