enum icon {
  invisible,
  full_wifi,
  half_wifi,
  small_wifi,
  access_point
};
const uint8_t icons[5][32] = {
  {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 
  0x00, 0x0E, 0x00, 0x03, 0x80, 0xE1, 0xC0, 0x38, 0x40, 0x0C, 0x60, 0xE6, 
  0x20, 0x32, 0x20, 0x1B, 0x20, 0xC9, 0x20, 0xC9
  },
  {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x38, 0x00, 0x0C, 0x00, 0xE6, 
  0x00, 0x32, 0x00, 0x1B, 0x00, 0xC9, 0x00, 0xC9
  },
  {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 
  0x00, 0x30, 0x00, 0x18, 0x00, 0xC8, 0x00, 0xC8
  },
  {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x18, 0x20, 0x20, 0x90, 0x48, 0x50, 0x57, 0x50, 0x52, 0x90, 0x4A, 
  0x20, 0x22, 0xC0, 0x1A, 0x00, 0x02, 0x00, 0x02
  }
};