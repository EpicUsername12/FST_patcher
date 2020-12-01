static const unsigned char arm_kernel_bin[] = {
  0xea, 0xff, 0xff, 0xff, 0xe9, 0x2d, 0x4f, 0xf7, 0xe5, 0x9f, 0xa1, 0x40,
  0xe5, 0x9f, 0x51, 0x40, 0xe5, 0x9f, 0x41, 0x40, 0xe1, 0xa0, 0x10, 0x0a,
  0xe2, 0x85, 0x3e, 0x16, 0xe5, 0x9f, 0x01, 0x38, 0xe1, 0x2f, 0xff, 0x33,
  0xe2, 0x84, 0x3e, 0x77, 0xe2, 0x83, 0x30, 0x08, 0xe1, 0x2f, 0xff, 0x33,
  0xe5, 0x9f, 0x91, 0x28, 0xe5, 0x9f, 0xb1, 0x28, 0xe5, 0x9f, 0x61, 0x28,
  0xe2, 0x85, 0x5f, 0x59, 0xe1, 0xa0, 0x70, 0x00, 0xeb, 0x00, 0x00, 0x5d,
  0xe5, 0x9f, 0x31, 0x1c, 0xe1, 0xa0, 0x10, 0x09, 0xe5, 0x93, 0x2d, 0x18,
  0xe5, 0x9f, 0x31, 0x14, 0xe5, 0x83, 0x20, 0x00, 0xe5, 0x9f, 0x31, 0x10,
  0xe5, 0x9f, 0x21, 0x10, 0xe5, 0x83, 0x2a, 0x24, 0xe3, 0xa0, 0x20, 0x30,
  0xe1, 0xa0, 0x80, 0x00, 0xe1, 0xa0, 0x00, 0x0b, 0xe1, 0x2f, 0xff, 0x36,
  0xe2, 0x89, 0x10, 0x30, 0xe3, 0xa0, 0x20, 0x68, 0xe5, 0x9f, 0x00, 0xf4,
  0xe1, 0x2f, 0xff, 0x36, 0xe2, 0x89, 0x10, 0x98, 0xe3, 0xa0, 0x20, 0x68,
  0xe5, 0x9f, 0x00, 0xe8, 0xe1, 0x2f, 0xff, 0x36, 0xe5, 0x9f, 0x10, 0xe4,
  0xe3, 0xa0, 0x20, 0xa4, 0xe5, 0x9f, 0x00, 0xe0, 0xe1, 0x2f, 0xff, 0x36,
  0xe5, 0x9f, 0x30, 0xdc, 0xe5, 0x9f, 0x90, 0xdc, 0xe5, 0x93, 0x20, 0x00,
  0xe5, 0x9f, 0x10, 0xd8, 0xe2, 0x83, 0x34, 0x12, 0xe2, 0x43, 0x3a, 0xe2,
  0xe5, 0x83, 0x15, 0x6c, 0xe1, 0xa0, 0x00, 0x09, 0xe5, 0x8d, 0x20, 0x04,
  0xe5, 0x9f, 0x10, 0xc4, 0xe1, 0x2f, 0xff, 0x36, 0xe5, 0x9d, 0x20, 0x04,
  0xe1, 0xa0, 0x00, 0x09, 0xe1, 0xa0, 0x10, 0x02, 0xe5, 0x9f, 0x90, 0xb4,
  0xe1, 0x2f, 0xff, 0x35, 0xe1, 0x2f, 0xff, 0x39, 0xe5, 0x9f, 0x30, 0xac,
  0xe5, 0x9f, 0x20, 0xac, 0xe3, 0xa0, 0x60, 0x00, 0xe5, 0x83, 0x2b, 0xa8,
  0xe5, 0x9f, 0x20, 0xa4, 0xe1, 0xa0, 0x00, 0x08, 0xe5, 0x83, 0x2b, 0xac,
  0xe5, 0x9f, 0x20, 0x9c, 0xe5, 0x83, 0x2b, 0xb0, 0xe5, 0x9f, 0x20, 0x98,
  0xe5, 0x83, 0x2b, 0xb4, 0xe5, 0x9f, 0x30, 0x94, 0xe5, 0x83, 0x65, 0x00,
  0xeb, 0x00, 0x00, 0x2b, 0xe1, 0xa0, 0x10, 0x0a, 0xe1, 0xa0, 0x00, 0x0b,
  0xe1, 0x2f, 0xff, 0x35, 0xe1, 0x2f, 0xff, 0x39, 0xe2, 0x84, 0x3d, 0x1e,
  0xe1, 0xa0, 0x00, 0x07, 0xe2, 0x83, 0x30, 0x0c, 0xe1, 0x2f, 0xff, 0x33,
  0xe1, 0xa0, 0x00, 0x06, 0xe2, 0x8d, 0xd0, 0x0c, 0xe8, 0xbd, 0x8f, 0xf0,
  0x00, 0x00, 0x40, 0x01, 0x08, 0x12, 0x00, 0x00, 0x08, 0x12, 0xe0, 0x00,
  0x08, 0x12, 0x00, 0xf0, 0x08, 0x13, 0x42, 0xe0, 0x08, 0x12, 0x98, 0xbc,
  0x08, 0x13, 0x1d, 0x04, 0x10, 0x16, 0xa0, 0x00, 0x01, 0xe1, 0x00, 0x00,
  0x08, 0x12, 0x90, 0x00, 0xe1, 0x2f, 0xff, 0x1e, 0x08, 0x12, 0x96, 0xe4,
  0x10, 0x10, 0x01, 0x74, 0x01, 0xe5, 0x00, 0x00, 0x10, 0x13, 0x12, 0xd0,
  0x01, 0xe7, 0x00, 0x00, 0x13, 0xd8, 0xe5, 0x70, 0x47, 0x70, 0x00, 0x00,
  0x01, 0xe7, 0x00, 0x20, 0x08, 0x12, 0xdc, 0xf0, 0x08, 0x1e, 0x60, 0x00,
  0x47, 0x78, 0x00, 0x00, 0xe5, 0x9f, 0x10, 0x00, 0xe1, 0x2f, 0xff, 0x11,
  0x05, 0x10, 0xe5, 0x70, 0x01, 0x55, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xee, 0x11, 0x0f, 0x10, 0xe5, 0x9f, 0x10, 0x10,
  0xe0, 0x00, 0x10, 0x01, 0xee, 0x01, 0x1f, 0x10, 0xe1, 0x2f, 0xff, 0x1e,
  0xee, 0x01, 0x0f, 0x10, 0xe1, 0x2f, 0xff, 0x1e, 0xff, 0xff, 0xef, 0xfa,
  0xe1, 0x2f, 0xff, 0x1e, 0xe9, 0x2d, 0x40, 0x30, 0xe5, 0x93, 0x20, 0x00,
  0xe1, 0xa0, 0x40, 0x00, 0xe5, 0x92, 0x30, 0x54, 0xe1, 0xa0, 0x50, 0x01,
  0xe3, 0x53, 0x00, 0x01, 0x0a, 0x00, 0x00, 0x02, 0xe1, 0x53, 0x00, 0x00,
  0xe3, 0xe0, 0x00, 0x00, 0x18, 0xbd, 0x80, 0x30, 0xe3, 0x54, 0x00, 0x0d,
  0x08, 0x16, 0x6c, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x08, 0x14, 0x40, 0x00,
  0x00, 0x00, 0x9d, 0x70, 0x08, 0x16, 0x84, 0x0c, 0x00, 0x00, 0xb4, 0x0c,
  0x00, 0x00, 0x01, 0x01, 0x08, 0x14, 0x40, 0x00, 0x08, 0x15, 0x00, 0x00,
  0x08, 0x17, 0x21, 0x80, 0x08, 0x17, 0x38, 0x00, 0x08, 0x14, 0x30, 0xd4,
  0x08, 0x14, 0x12, 0x50, 0x08, 0x14, 0x12, 0x94, 0xe3, 0xa0, 0x35, 0x36,
  0xe5, 0x93, 0x21, 0x94, 0xe3, 0xc2, 0x2e, 0x21, 0xe5, 0x83, 0x21, 0x94,
  0xe5, 0x93, 0x11, 0x94, 0xe1, 0x2f, 0xff, 0x1e, 0xe5, 0x9f, 0x30, 0x1c,
  0xe5, 0x9f, 0xc0, 0x1c, 0xe5, 0x93, 0x20, 0x00, 0xe1, 0xa0, 0x10, 0x00,
  0xe5, 0x92, 0x30, 0x54, 0xe5, 0x9c, 0x00, 0x00, 0xe5, 0x8d, 0xe0, 0x04,
  0xe5, 0x8d, 0xc0, 0x08, 0xe5, 0x8d, 0x40, 0x0c, 0xe5, 0x8d, 0x60, 0x10,
  0xeb, 0x00, 0xb2, 0xfd, 0xea, 0xff, 0xff, 0xc9, 0x10, 0x14, 0x03, 0xf8,
  0x10, 0x62, 0x4d, 0xd3, 0x10, 0x14, 0x50, 0x00, 0x10, 0x14, 0x50, 0x20,
  0x10, 0x14, 0x00, 0x00, 0x10, 0x14, 0x00, 0x90, 0x10, 0x14, 0x00, 0x70,
  0x10, 0x14, 0x00, 0x98, 0x10, 0x14, 0x00, 0x84, 0x10, 0x14, 0x03, 0xe8,
  0x10, 0x14, 0x00, 0x3c, 0x00, 0x00, 0x01, 0x73, 0x00, 0x00, 0x01, 0x76,
  0xe9, 0x2d, 0x4f, 0xf0, 0xe2, 0x4d, 0xde, 0x17, 0xeb, 0x00, 0xb9, 0x92,
  0xe3, 0xa0, 0x10, 0x00, 0xe3, 0xa0, 0x20, 0x03, 0xe5, 0x9f, 0x0e, 0x68,
  0xeb, 0x00, 0xb3, 0x20
};
static const unsigned int arm_kernel_bin_len = 736;
