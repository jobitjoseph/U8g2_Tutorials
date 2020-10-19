/*
 * This example uses 3 sprites that take up 3952 bytes of dynamic memory
 * Make sure that your microcontroller has more than 10KB of RAM otherwise
 * this code will not work. In tutorial 8 we will store the spirtes in PROGMEM freeing up RAM.
 * 
 * The bird animation will play and the dragon animation will play both animations will block the micro controller and loop forever
 * 
 * L33T_Animation Class Example
 * 
 * Copyright David Bradshaw 2020
 * 
 * To view the tutorial go to www.L33t.uk/U8G2
 *                            https://www.youtube.com/watch?v=hP_Iinhm-J8&list=PLO2D4fDkIZCVG0tF_QvZqrIN6djy4-Z6i
 *                            https://github.com/L33t-dot-UK/U8g2_Tutorials
 * 
 */

#include <L33T_Animation.h> //import animation library
#include <U8g2lib.h> //Import the U8G2 library

U8G2_SH1106_128X64_NONAME_F_HW_I2C auxScreen(U8G2_R0); //Create a U8G2 object for our SH1106 chipset

//ICON 1 THIS IS A PICTURE OF A BIRD RUNNING ALONG THE FLOOR
const int sizeBytes = 376; //Number of bytes per frame 
const int frames = 4; //Number of frames
const int icHeight = 47;
const int icWidth = 64;
static const unsigned char icon[frames][sizeBytes] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
   0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x03, 0xe4, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
   0xe2, 0x03, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xd9, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x0c, 0x80, 0xf9, 0x0e, 0x00, 0x00, 0x00, 0x60, 0x06, 0x80,
   0x78, 0x18, 0x00, 0x00, 0x00, 0x60, 0x03, 0x40, 0x3a, 0x18, 0x00, 0x00,
   0x00, 0xa0, 0x03, 0x40, 0x3c, 0x20, 0x00, 0x00, 0x00, 0x20, 0x01, 0x40,
   0x1a, 0x60, 0x00, 0x00, 0x00, 0x60, 0x02, 0x60, 0x1e, 0xc0, 0x00, 0x00,
   0x00, 0x60, 0x08, 0x60, 0x0f, 0xc0, 0x00, 0x00, 0x18, 0xd0, 0x12, 0xf0,
   0x1f, 0x80, 0x01, 0x00, 0x78, 0xa0, 0x01, 0x10, 0x20, 0x80, 0x01, 0x00,
   0xf8, 0x20, 0x26, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0xf3, 0x00, 0x48,
   0x31, 0x00, 0x03, 0x00, 0x70, 0x7e, 0x57, 0xf8, 0x37, 0x62, 0x03, 0x00,
   0xb0, 0x7c, 0x00, 0xe9, 0x75, 0x66, 0x03, 0x00, 0xc0, 0x9b, 0x4a, 0xd8,
   0x2b, 0x04, 0x02, 0x00, 0x00, 0x1e, 0x0a, 0xf8, 0x35, 0xc0, 0xff, 0x0f,
   0x80, 0x1b, 0x00, 0xd8, 0x7b, 0x78, 0x00, 0x3d, 0xf0, 0x3c, 0x00, 0xf8,
   0x37, 0x06, 0x00, 0x18, 0x78, 0x16, 0x00, 0xf8, 0x3f, 0x04, 0x00, 0x08,
   0xf8, 0x33, 0x00, 0xe0, 0x1f, 0x0c, 0x00, 0x0c, 0xe0, 0x20, 0x00, 0x00,
   0x04, 0x08, 0x07, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x90, 0x3f, 0x03,
   0x00, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x01, 0x00, 0xc0, 0x01, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x78, 0x00, 0x00,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x01,
   0x40, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x55, 0xd5, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x0c, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
   0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0xfb, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0xff, 0x03, 0x00, 0x00, 
   
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x07, 0xee, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0x86, 0x03, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xf3, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x80, 0xe9, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x80,
   0x70, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x34, 0x18, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x40, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x80, 0x01, 0x40,
   0x1a, 0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x60, 0x1c, 0x40, 0x00, 0x00,
   0x00, 0xc0, 0x00, 0x60, 0x1d, 0xc0, 0x00, 0x00, 0x18, 0x60, 0x00, 0xf0,
   0x1f, 0x80, 0x00, 0x00, 0x3c, 0x7c, 0x00, 0x18, 0x30, 0x80, 0x01, 0x00,
   0xfc, 0xf8, 0x01, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0x33, 0x1f, 0x48,
   0x21, 0x01, 0x03, 0x00, 0x78, 0xbe, 0x60, 0xd8, 0x6b, 0x62, 0x03, 0x00,
   0x30, 0xbc, 0x87, 0xe8, 0x6b, 0x66, 0x02, 0x00, 0xe0, 0xf9, 0x00, 0xd9,
   0x71, 0x06, 0x03, 0x00, 0x00, 0x5f, 0x17, 0xd8, 0x23, 0x80, 0xff, 0x03,
   0x00, 0x1f, 0x00, 0xd8, 0x6b, 0xf8, 0xf7, 0x3f, 0xe0, 0x18, 0x00, 0xd8,
   0x35, 0x0e, 0x00, 0x18, 0x78, 0x3c, 0x00, 0x78, 0x3f, 0x06, 0x00, 0x18,
   0xf8, 0x33, 0x00, 0xf0, 0x3f, 0x0c, 0x00, 0x0c, 0xe0, 0x31, 0x00, 0x40,
   0x05, 0x98, 0x03, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x98, 0x3f, 0x03,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0xb0, 0xf1, 0x03, 0x00, 0xc0, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x01, 0x00, 0x80, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00,
   0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
   0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xbf, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x31, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xee, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x3e, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
   0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x7f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x0f, 0xee, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01,
   0xa6, 0x03, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xa3, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x80, 0xe9, 0x07, 0x00, 0x00, 0x00, 0x20, 0x0c, 0x80,
   0xe8, 0x0c, 0x00, 0x00, 0x00, 0x60, 0x06, 0xc0, 0x74, 0x18, 0x00, 0x00,
   0x00, 0xe0, 0x03, 0xc0, 0x3c, 0x30, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x40,
   0x1a, 0x60, 0x00, 0x00, 0x00, 0x20, 0x03, 0x40, 0x1c, 0x60, 0x00, 0x00,
   0x00, 0x60, 0x06, 0x60, 0x1d, 0xc0, 0x00, 0x00, 0x08, 0x70, 0x18, 0xe0,
   0x1f, 0x80, 0x00, 0x00, 0x3c, 0x90, 0x21, 0xb8, 0x35, 0x80, 0x01, 0x00,
   0x7c, 0x20, 0x63, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0x71, 0x82, 0x08,
   0x60, 0x00, 0x03, 0x00, 0x78, 0xf7, 0x01, 0xd8, 0x65, 0xa3, 0x03, 0x00,
   0x30, 0x7c, 0x4f, 0xe8, 0x2b, 0x6e, 0x02, 0x00, 0xe0, 0x58, 0x00, 0xd9,
   0x71, 0x46, 0x02, 0x00, 0x00, 0x9f, 0x01, 0xd8, 0x65, 0x00, 0x7f, 0x00,
   0x00, 0x3e, 0x16, 0xd8, 0x73, 0xf0, 0xff, 0x3f, 0xc0, 0x19, 0x00, 0xd8,
   0x35, 0x3e, 0x00, 0x38, 0x78, 0x3c, 0x00, 0x78, 0x3b, 0x06, 0x00, 0x18,
   0xf8, 0x36, 0x00, 0xf0, 0x3f, 0x0c, 0x00, 0x0c, 0xf0, 0x31, 0x00, 0xe0,
   0x0f, 0x98, 0x01, 0x06, 0x00, 0x20, 0x00, 0x00, 0x00, 0x98, 0x1f, 0x06,
   0x00, 0x60, 0x00, 0x00, 0x00, 0xb0, 0xf9, 0x03, 0x00, 0xc0, 0x00, 0x00,
   0x00, 0xe0, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x00, 0x60, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
   0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x80, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0xf0, 0x0b, 0xf5, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x78, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xc0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x70, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00,
   0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x0f, 0xf8, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f,
   0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x07, 0xee, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0x86, 0x03, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xf3, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x80, 0xe9, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x80,
   0x70, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x34, 0x18, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x40, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x80, 0x01, 0x40,
   0x1a, 0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x60, 0x1c, 0x40, 0x00, 0x00,
   0x00, 0xc0, 0x00, 0x60, 0x1d, 0xc0, 0x00, 0x00, 0x18, 0x60, 0x00, 0xe0,
   0x1f, 0x80, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x18, 0x30, 0x80, 0x01, 0x00,
   0xfc, 0xf8, 0x01, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0x3b, 0x1f, 0x48,
   0x21, 0x01, 0x03, 0x00, 0x78, 0x7e, 0x70, 0xd8, 0x6b, 0x62, 0x03, 0x00,
   0x30, 0xfc, 0x83, 0xd8, 0x6b, 0x66, 0x03, 0x00, 0xe0, 0xf9, 0x02, 0xd9,
   0x71, 0x06, 0x02, 0x00, 0x00, 0xbf, 0x16, 0xd8, 0x23, 0x80, 0xff, 0x03,
   0x00, 0x17, 0x00, 0xd8, 0x7b, 0xf8, 0xdb, 0x3f, 0xe0, 0x18, 0x00, 0xd8,
   0x32, 0x0e, 0x00, 0x18, 0x78, 0x3e, 0x00, 0xf8, 0x3f, 0x06, 0x00, 0x18,
   0xf8, 0x33, 0x00, 0xf0, 0x3f, 0x4c, 0x00, 0x0c, 0xe0, 0x31, 0x00, 0x40,
   0x05, 0x98, 0x03, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x98, 0x3f, 0x03,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0x03, 0x00, 0xc0, 0x00, 0x00,
   0x00, 0xe0, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x00, 0x70, 0x00, 0x00,
   0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
   0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xbf, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0x0c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x3e, 0x03, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03,
   0x18, 0x70, 0x00, 0x00, 0x00, 0x80, 0xe7, 0x03, 0x38, 0xfc, 0x00, 0x00,
   0x00, 0xc0, 0x83, 0x01, 0x30, 0x7e, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00,
   0x30, 0x1f, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0xe0, 0x07, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x40, 0x00, 0x00, 0x00

   };


//ICON2 THIS IS A PICTURE OF A DRAGON FLYING
const int sizeBytes_IC2 = 276; //Number of bytes per frame 
const int frames_IC2 = 7; //Number of frames
const int icHeight_IC2 = 46;
const int icWidth_IC2 = 47;

static const unsigned char icon2[frames_IC2][sizeBytes_IC2] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x8f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x97, 0x33, 0x00, 0x00,
   0x00, 0x00, 0xaa, 0x53, 0x08, 0x00, 0x00, 0x00, 0xd6, 0x1e, 0x10, 0x00,
   0x00, 0x00, 0x28, 0x11, 0x24, 0x00, 0x00, 0x00, 0xef, 0x10, 0x04, 0x00,
   0x00, 0x00, 0xd2, 0x30, 0x48, 0x00, 0x00, 0x00, 0xf6, 0x44, 0x18, 0x00,
   0x00, 0x20, 0xdb, 0x02, 0xc0, 0x00, 0x00, 0x20, 0xc6, 0x80, 0x84, 0x00,
   0x00, 0x20, 0x6e, 0x02, 0x00, 0x01, 0x00, 0x20, 0xc9, 0x00, 0x00, 0x02,
   0x00, 0x72, 0x30, 0x01, 0x00, 0x02, 0x00, 0x02, 0x60, 0x00, 0x50, 0x02,
   0x00, 0x02, 0xe0, 0x01, 0x18, 0x02, 0x00, 0x0e, 0x00, 0x80, 0x71, 0x01,
   0x40, 0x83, 0x00, 0x00, 0x00, 0x01, 0x40, 0xe0, 0x00, 0x00, 0x00, 0x01,
   0x00, 0x30, 0x03, 0x00, 0x86, 0x00, 0xc0, 0x0d, 0x01, 0x00, 0xe2, 0x00,
   0x40, 0xc6, 0x7c, 0x00, 0x60, 0x00, 0xe0, 0x71, 0x1e, 0x00, 0x30, 0x00,
   0x00, 0x1c, 0x3b, 0x00, 0x0c, 0x00, 0x00, 0xf8, 0xef, 0x82, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf1, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xd6, 0x08, 0x00, 0x00, 0x00, 0x60, 0x16, 0x10, 0x00,
   0x00, 0x00, 0xb0, 0x18, 0x24, 0x00, 0x00, 0x00, 0x3c, 0x11, 0x04, 0x00,
   0x00, 0x00, 0xe8, 0x20, 0x48, 0x00, 0x00, 0x00, 0x88, 0x4d, 0x18, 0x00,
   0x00, 0x20, 0xbd, 0x01, 0xc0, 0x00, 0x00, 0x20, 0xce, 0x81, 0x84, 0x00,
   0x00, 0x20, 0xf8, 0x00, 0x00, 0x01, 0x00, 0x20, 0xdd, 0x00, 0x00, 0x02,
   0x00, 0x32, 0xb0, 0x00, 0x00, 0x02, 0x00, 0x22, 0xb0, 0x00, 0x70, 0x02,
   0x00, 0x02, 0xc0, 0x01, 0x18, 0x02, 0x00, 0x0e, 0x00, 0x80, 0x51, 0x01,
   0x40, 0x83, 0x00, 0x00, 0x00, 0x01, 0x40, 0xe0, 0x01, 0x00, 0x00, 0x01,
   0x00, 0x30, 0x03, 0x00, 0x8e, 0x00, 0xc0, 0x0d, 0x03, 0x00, 0xe0, 0x00,
   0x40, 0x86, 0x39, 0x00, 0x60, 0x00, 0xe0, 0x61, 0x2c, 0x00, 0x30, 0x00,
   0x00, 0x38, 0x3f, 0x00, 0x0c, 0x00, 0x00, 0xfc, 0xef, 0xa3, 0x03, 0x00,
   0x00, 0x80, 0x03, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x14, 0x10, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x00, 0x28, 0x11, 0x06, 0x00,
   0x00, 0x00, 0xc0, 0x21, 0x40, 0x00, 0x00, 0x00, 0x80, 0x4c, 0x18, 0x00,
   0x00, 0x20, 0x27, 0x00, 0xc0, 0x00, 0x00, 0x20, 0x0e, 0x80, 0x84, 0x00,
   0x00, 0x20, 0x0e, 0x00, 0x00, 0x01, 0x00, 0x20, 0x0c, 0x00, 0x00, 0x02,
   0x00, 0x72, 0x34, 0x00, 0x00, 0x02, 0x00, 0x22, 0x04, 0x00, 0x78, 0x02,
   0x00, 0x02, 0x5a, 0x80, 0x10, 0x02, 0x00, 0x0e, 0x22, 0x80, 0x71, 0x01,
   0x40, 0xc3, 0xab, 0x01, 0x00, 0x01, 0x40, 0xe0, 0x2f, 0x03, 0x00, 0x01,
   0x00, 0xf0, 0xff, 0x01, 0x8e, 0x00, 0xc0, 0x3d, 0x03, 0x00, 0xe0, 0x00,
   0x40, 0x86, 0x79, 0x00, 0x60, 0x00, 0xe0, 0xc1, 0x2c, 0x00, 0x30, 0x00,
   0x00, 0x30, 0x3e, 0x00, 0x0c, 0x00, 0x00, 0xb8, 0xff, 0xcb, 0x03, 0x00,
   0x00, 0xf0, 0x07, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x14, 0x10, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x00, 0x28, 0x11, 0x04, 0x00,
   0x00, 0x00, 0xc0, 0x21, 0x48, 0x00, 0x00, 0x00, 0x80, 0x4c, 0x18, 0x00,
   0x00, 0x20, 0x25, 0x00, 0xc0, 0x00, 0x00, 0x20, 0x06, 0x80, 0x84, 0x00,
   0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x01, 0x00, 0x00, 0x02,
   0x00, 0xb2, 0x00, 0x00, 0x00, 0x02, 0x00, 0x22, 0x00, 0x00, 0x78, 0x02,
   0x00, 0x02, 0x00, 0x80, 0x10, 0x03, 0x00, 0x0e, 0x00, 0x80, 0x31, 0x01,
   0x40, 0x83, 0x00, 0x00, 0x00, 0x01, 0x40, 0xe0, 0x41, 0x01, 0x00, 0x01,
   0x00, 0x30, 0x45, 0x00, 0x8f, 0x00, 0xc0, 0x0d, 0x62, 0x00, 0xe0, 0x00,
   0x40, 0x06, 0x59, 0x01, 0x60, 0x00, 0xe0, 0xc1, 0x7c, 0x00, 0x30, 0x00,
   0x00, 0x60, 0xbe, 0x00, 0x0e, 0x00, 0x00, 0x18, 0xaf, 0xab, 0x03, 0x00,
   0x00, 0xf8, 0xdf, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xd7, 0x19, 0x00, 0x00,
   0x00, 0x00, 0x3b, 0x07, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x06, 0x00, 0x00,
   0x00, 0x00, 0x8f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x87, 0x01, 0x00, 0x00,
   0x00, 0x80, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x14, 0x10, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x00, 0x28, 0x11, 0x06, 0x00,
   0x00, 0x00, 0xc0, 0x21, 0x40, 0x00, 0x00, 0x00, 0x80, 0x4c, 0x18, 0x00,
   0x00, 0x20, 0x25, 0x00, 0xc0, 0x00, 0x00, 0x20, 0x06, 0x80, 0x84, 0x00,
   0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x01, 0x00, 0x00, 0x02,
   0x00, 0x32, 0x00, 0x00, 0x00, 0x02, 0x00, 0x22, 0x00, 0x00, 0x70, 0x02,
   0x00, 0x02, 0x00, 0x00, 0x18, 0x02, 0x00, 0x0e, 0x00, 0x80, 0x71, 0x01,
   0x40, 0x83, 0x50, 0x01, 0x00, 0x01, 0x40, 0xe0, 0x50, 0x00, 0x00, 0x01,
   0x00, 0x30, 0xbf, 0x00, 0x8a, 0x00, 0xc0, 0x0d, 0xae, 0x00, 0xe2, 0x00,
   0x40, 0x06, 0x57, 0x00, 0x40, 0x00, 0xe0, 0x81, 0x63, 0x01, 0x30, 0x00,
   0x00, 0xc0, 0x77, 0x00, 0x0c, 0x00, 0x00, 0x30, 0x6d, 0x83, 0x03, 0x00,
   0x00, 0xf8, 0xf3, 0x7e, 0x01, 0x00, 0x00, 0x80, 0x6b, 0x6e, 0x00, 0x00,
   0x00, 0x00, 0x7a, 0xab, 0x00, 0x00, 0x00, 0x00, 0x4e, 0xab, 0x00, 0x00,
   0x00, 0x00, 0x53, 0x53, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x54, 0x00, 0x00,
   0x00, 0x00, 0xa4, 0x34, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x3c, 0x00, 0x00,
   0x00, 0x00, 0x54, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x34, 0x0c, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00,
   0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x14, 0x10, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x00, 0x28, 0x11, 0x04, 0x00,
   0x00, 0x00, 0xc0, 0x21, 0x48, 0x00, 0x00, 0x00, 0x80, 0x4c, 0x18, 0x00,
   0x00, 0x20, 0x25, 0x00, 0xc0, 0x00, 0x00, 0x20, 0x06, 0x80, 0x84, 0x00,
   0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x01, 0x00, 0x00, 0x02,
   0x00, 0xb2, 0x00, 0x00, 0x00, 0x02, 0x00, 0x22, 0x00, 0x00, 0x78, 0x02,
   0x00, 0x02, 0x00, 0x80, 0x10, 0x03, 0x00, 0x0e, 0x00, 0x80, 0x31, 0x01,
   0x40, 0x83, 0x00, 0x00, 0x00, 0x01, 0x40, 0xe0, 0x41, 0x01, 0x00, 0x01,
   0x00, 0x30, 0x45, 0x00, 0x8f, 0x00, 0xc0, 0x0d, 0x62, 0x00, 0xe0, 0x00,
   0x40, 0x06, 0x59, 0x01, 0x60, 0x00, 0xe0, 0xc1, 0x7c, 0x00, 0x30, 0x00,
   0x00, 0x60, 0xbe, 0x00, 0x0e, 0x00, 0x00, 0x18, 0xaf, 0xab, 0x03, 0x00,
   0x00, 0xf8, 0xdf, 0x7d, 0x00, 0x00, 0x00, 0x00, 0xd7, 0x0e, 0x00, 0x00,
   0x00, 0x00, 0xbb, 0x07, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xcf, 0x01, 0x00, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00,
   0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x14, 0x10, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x00, 0x28, 0x11, 0x04, 0x00,
   0x00, 0x00, 0xc0, 0x21, 0x48, 0x00, 0x00, 0x00, 0x80, 0x4c, 0x18, 0x00,
   0x00, 0x20, 0x25, 0x00, 0xc0, 0x00, 0x00, 0x20, 0x06, 0x80, 0x84, 0x00,
   0x00, 0x20, 0x02, 0x00, 0x00, 0x01, 0x00, 0xe0, 0xfe, 0x00, 0x00, 0x02,
   0x00, 0xf2, 0x3f, 0x03, 0x00, 0x02, 0x00, 0x22, 0xa3, 0x01, 0x78, 0x02,
   0x00, 0x02, 0xaa, 0x80, 0x10, 0x02, 0x00, 0x0e, 0x2a, 0x80, 0x71, 0x01,
   0x40, 0xc3, 0x55, 0x00, 0x00, 0x01, 0x40, 0xe0, 0x0d, 0x00, 0x00, 0x01,
   0x00, 0x30, 0x0f, 0x00, 0x8e, 0x00, 0xc0, 0x0d, 0x0f, 0x00, 0xe0, 0x00,
   0x40, 0x86, 0x7d, 0x00, 0x40, 0x00, 0xe0, 0x41, 0x1f, 0x00, 0x30, 0x00,
   0x00, 0x30, 0x3f, 0x00, 0x0c, 0x00, 0x00, 0xb8, 0xff, 0xcb, 0x03, 0x00,
   0x00, 0xf0, 0x07, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
   
   };

const int groundWidth =  128;
const int groundHeight = 33;
static const unsigned char ground[][552] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x59, 0x05, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x48,
   0xa5, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xc0, 0x54, 0x00, 0xa8, 0x5a, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xa8, 0x2a, 0x00, 0xa8, 0x55, 0x15, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x0d, 0x00, 0x50, 0xd5, 0x00, 0xb4,
   0xb6, 0xad, 0x0d, 0x00, 0x50, 0x01, 0x00, 0x04, 0x00, 0xa0, 0x2a, 0x00,
   0x68, 0xab, 0x35, 0xac, 0x6d, 0x6b, 0xbb, 0x02, 0xa8, 0x02, 0x80, 0x15,
   0x00, 0x58, 0x55, 0x00, 0xd8, 0x6e, 0x6d, 0x7c, 0xd5, 0xae, 0x56, 0x0d,
   0xb4, 0x4a, 0x40, 0x15, 0x00, 0xe8, 0xb6, 0x17, 0xb8, 0xad, 0xdb, 0xa9,
   0xdf, 0xfa, 0x7d, 0xbb, 0xd5, 0xb6, 0xe0, 0xf6, 0x03, 0xa8, 0xad, 0x16,
   0x68, 0x7b, 0x6d, 0x79, 0xb5, 0x57, 0x6b, 0x6d, 0xbb, 0x6d, 0x41, 0x5b,
   0x0f, 0xb8, 0x7b, 0x1d, 0x48, 0x42, 0xa2, 0x7f, 0x25, 0x24, 0xd5, 0x57,
   0x22, 0x49, 0xe0, 0xff, 0x16, 0x78, 0x42, 0x11, 0x24, 0x94, 0x14, 0xf4,
   0xff, 0xff, 0x2f, 0x88, 0x94, 0x24, 0x01, 0x52, 0xf5, 0x85, 0x14, 0x4a,
   0xa5, 0x25, 0x65, 0x45, 0xaa, 0x2a, 0xd0, 0x2a, 0x25, 0x49, 0xb6, 0x4a,
   0x85, 0x54, 0xa5, 0x52, 0x2a, 0xaa, 0x4a, 0x55, 0x55, 0xa5, 0x2d, 0x55,
   0xa9, 0xaa, 0x48, 0x55, 0x55, 0x55, 0x59, 0xa8, 0xd5, 0x55, 0x55, 0x55,
   0x55, 0xad, 0xaa, 0xaa, 0xb6, 0xa2, 0x5b, 0x55, 0x55, 0x55, 0x55, 0x55,
   0x2d, 0xad, 0xaa, 0xb6, 0xad, 0x6a, 0xed, 0xff, 0xff, 0xff, 0xb7, 0x5a,
   0xad, 0xaa, 0xb5, 0xd5, 0x75, 0xab, 0xb5, 0xad, 0xda, 0xed, 0xff, 0xff,
   0xff, 0x7f, 0xff, 0xb7, 0xeb, 0x6e, 0x6d, 0xb7, 0xef, 0xde, 0x6e, 0xfb,
   0x6d, 0xff, 0xff, 0x6f, 0x55, 0xd5, 0xf6, 0xff, 0x5e, 0xdb, 0xdb, 0xda,
   0xdd, 0xfb, 0xff, 0xb7, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

   };

//Create the Animation Objects
/*
ICON WIDTH = Width of the icon in pixels 
ICON HEIGHT = Height of the icon in pixels
FRAME_DELAY = How long between drawing the next frame in milliseconds
XINCREMENT = How many pixels to increment the animation for the x axis
YINCREMENT = How many pixels to increment the animation for the Y axis
XSTART = X coordinate start position
XEND = X coordinate end position
YSTART = Y coordinate start position
YEND = Y coordinate end position
FRAMES = How many frame are there in the animation
IF THE ANIMATION IS TO STAY STILL X AND Y START AND END POSITIONS SHOULD BE THE SAME
The Animation class allows us to create new animations with ease and to draw these animations in a non blocking way
*/
//                   ICON WIDTH    ICON HEIGHT    FRAME_DELAY Ms     XINCREMENT   YINCREMENT   XSTART  XEND   YSTART   YEND       FRAMES
L33T_Animation BIRD(icWidth,        icHeight,            200,            2,             1,        -64,    160,   15,      15,       frames);
L33T_Animation DRAGON(icWidth_IC2, icHeight_IC2,         150,            6,             6,        -96,    128,     15,    -8,       frames_IC2);

void setup() {
    // put your setup code here, to run once:
    auxScreen.begin();//Start the screen object
    auxScreen.setBitmapMode(1); //set the background to transparant
    Serial.begin(9600); //Start serial port for debugging
    Serial.println("Ani Class Started"); //Send a message to let us know that the controller has started up
}

void loop() {
    // put your main code here, to run repeatedly: 

    //The Bird animation will play and after it has finished the dragon animation will play
    //this will block your micro controller which can be helpful in some cases. For instance
    //if you want a splash screen animation at startup this method could be used in the setup()
    //function
   while (BIRD.getBarEndX() || BIRD.getBarEndY())
   {
        auxScreen.clearBuffer();
        BIRD.chkAnimation(true); //true == move animation
        auxScreen.drawXBM(BIRD.getXpos(), BIRD.getYpos(), BIRD.getWidth(), BIRD.getHeight(), icon[BIRD.getCurrentFrame()]);
        auxScreen.sendBuffer();
   }
   BIRD.resetAni(); //This will check the BIRD animaiton object and set barEndX and barEndY to true, if this wasn't here then the animation would only play once
   
   while (DRAGON.getBarEndX() || DRAGON.getBarEndY())
   {
        auxScreen.clearBuffer();
        DRAGON.chkAnimation(true); //true == move animation
        auxScreen.drawXBM(DRAGON.getXpos(), DRAGON.getYpos(), DRAGON.getWidth(), DRAGON.getHeight(), icon2[DRAGON.getCurrentFrame()]);
        auxScreen.sendBuffer();
   }
   DRAGON.resetAni(); //This will make the dragin animation loop by setting the barEndX and barEndY values to true
}
