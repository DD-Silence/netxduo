#include "nx_api.h"
#if defined(NX_TAHI_ENABLE) && defined(FEATURE_NX_IPV6)  

#include "netx_tahi.h"

/* Frame (70 bytes) */
static char pkt1[70] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, /* .R.....# */
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef              /* Eg.... */
};

/* Frame (86 bytes) */
static char pkt2[86] = {
0x33, 0x33, 0xff, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* 33...... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6c, 0x27, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* l'...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt3[86] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x88, 0x00, /* "..3DV.. */
0x4e, 0xa4, 0xe0, 0x00, 0x00, 0x00, 0xfe, 0x80, /* N....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x02, 0x01, /* ........ */
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0              /* ...... */
};

/* Frame (70 bytes) */
static char pkt4[70] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, /* ........ */
0xda, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, /* .R.....# */
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef              /* Eg.... */
};

/* Frame (70 bytes) */
static char pkt5[70] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, /* .R.....# */
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef              /* Eg.... */
};

/* Frame (70 bytes) */
static char pkt6[70] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, /* ........ */
0xda, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, /* .R.....# */
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef              /* Eg.... */
};

/* Frame (86 bytes) */
static char pkt7[86] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* j....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (78 bytes) */
static char pkt8[78] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0xfe, 0x80, /* ....:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, /* ........ */
0xcd, 0xed, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, /* ..@..... */
0x27, 0x10, 0x00, 0x00, 0x03, 0xe8, 0x01, 0x01, /* '....... */
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0              /* ...... */
};

/* Frame (86 bytes) */
static char pkt9[86] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* j....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt10[86] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* j....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt11[86] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0xb0, 0xb0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x88, 0x00, /* ........ */
0xe5, 0xab, 0xa0, 0x00, 0x00, 0x00, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x02, 0x01, /* ........ */
0x00, 0x00, 0x00, 0x00, 0xb0, 0xb0              /* ...... */
};

/* Frame (70 bytes) */
static char pkt12[70] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xb0, 0xb0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, /* .R.....# */
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef              /* Eg.... */
};

/* Frame (86 bytes) */
static char pkt13[86] = {
0x33, 0x33, 0xff, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* 33...... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6c, 0x27, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* l'...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt14[86] = {
0x33, 0x33, 0xff, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* 33...... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6c, 0x27, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* l'...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt15[86] = {
0x33, 0x33, 0xff, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* 33...... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6c, 0x27, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* l'...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (102 bytes) */
static char pkt16[102] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x30, 0x3a, 0xff, 0xfe, 0x80, /* ...0:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, /* ........ */
0x97, 0x93, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, /* ..@..... */
0x75, 0x30, 0x00, 0x00, 0x03, 0xe8, 0x03, 0x04, /* u0...... */
0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* @....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00              /* ...... */
};



TAHI_TEST_SEQ tahi_02_158[] = {
    {TITLE, "02-158", 6, 0},
    {WAIT, NX_NULL, 0, 5},

    {INJECT, &pkt1[0], sizeof(pkt1), 0},  /* Echo request  */
    {CHECK, &pkt2[0], sizeof(pkt2), 2},   /* NS  */
    {INJECT, &pkt3[0], sizeof(pkt3), 0},  /* NA  */
    {CHECK, &pkt4[0], sizeof(pkt4), 2},   /* Echo reply  */

    {WAIT, NX_NULL, 0, 45},
    {INJECT, &pkt5[0], sizeof(pkt5), 0},  /* Echo request  */
    {CHECK, &pkt6[0], sizeof(pkt6), 2},   /* Echo reply  */
    {CHECK, &pkt7[0], sizeof(pkt7), 7},   /* NS  */
    {INJECT, &pkt8[0], sizeof(pkt8), 0},  /* RA  */
    {CHECK, &pkt9[0], sizeof(pkt9), 2},   /* NS  */
    {CHECK, &pkt10[0], sizeof(pkt10), 2}, /* NS  */
    {WAIT, NX_NULL, 0, 2},
    {DUMP, NX_NULL, 0, 0},

    {INJECT, &pkt11[0], sizeof(pkt11), 0},/* NA  */
    {INJECT, &pkt12[0], sizeof(pkt12), 0},/* Echo request  */
    {CHECK, &pkt13[0], sizeof(pkt13), 2}, /*    NS */
    {CHECK, &pkt14[0], sizeof(pkt14), 2}, /*    NS */
    {CHECK, &pkt15[0], sizeof(pkt15), 2}, /*    NS */

    {WAIT, NX_NULL, 0, 5},
    {INJECT, &pkt16[0], sizeof(pkt16), 0},/* RA  */
    
    {CLEANUP, NX_NULL, 0, 0},
    {DUMP, NX_NULL, 0, 0}
};

int tahi_02_158_size = sizeof(tahi_02_158) / sizeof(TAHI_TEST_SEQ);

#endif /* NX_TAHI_ENABLE */
