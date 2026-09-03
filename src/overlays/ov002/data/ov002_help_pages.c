/* ov002 help pages, 0x0207dd14-0x0207dd7c.
 *
 * Four pages read by Ov002_PrintHelpPage: five line ids and the page title id. The
 * lines run in tens except the first page, whose first line is 0 rather than 10.
 */

typedef struct {
    int aLines[5];
    int nTitle;
} Ov002HelpPage;

const Ov002HelpPage data_ov002_0207dd14[4] = {
    { { 0, 11, 12, 13, 14 }, 210 },
    { { 20, 21, 22, 23, 24 }, 220 },
    { { 30, 31, 32, 33, 34 }, 230 },
    { { 40, 41, 42, 43, 44 }, 240 },
};

/* Two zero words directly after the pages, contiguous with them. */
const int data_ov002_0207dd74[2] = { 0, 0 };
