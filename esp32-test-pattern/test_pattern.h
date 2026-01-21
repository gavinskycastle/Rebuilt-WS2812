/*!
    @brief   Convert separate red, green and blue values into a single
             "packed" 32-bit RGB color.
    @param   r  Red brightness, 0 to 255.
    @param   g  Green brightness, 0 to 255.
    @param   b  Blue brightness, 0 to 255.
    @return  32-bit packed RGB value, which can then be assigned to a
             variable for later use or passed to the setPixelColor()
             function. Packed RGB format is predictable, regardless of
             LED strand color order.
  */
static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// uint32_t colors[5] = {
//     Color(255, 0, 0),    // Red
//     Color(255, 106, 0),  // Orange
//     Color(255, 216, 0),  // Yellow
//     Color(0, 255, 33),   // Green
//     Color(255, 255, 255) // White
// };

uint32_t frame_1[5] = {Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0)};
uint32_t frame_2[5] = {Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0), Color(255, 216, 0)};

uint32_t* frames[2] = {frame_1, frame_2};

// uint32_t* frames[2][256] = {
//     // Frame 1
//     {
//        /*0*/  &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0],
//        /*1*/  &colors[0], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[0],
//        /*2*/  &colors[0], &colors[4], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[4], &colors[0],
//        /*3*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*4*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*5*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*6*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[4], &colors[3], &colors[3], &colors[3], &colors[3], &colors[4], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*7*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[4], &colors[3], &colors[4], &colors[4], &colors[3], &colors[4], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*8*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[4], &colors[3], &colors[4], &colors[4], &colors[3], &colors[4], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*9*/  &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[4], &colors[3], &colors[3], &colors[3], &colors[3], &colors[4], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*10*/ &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*11*/ &colors[0], &colors[4], &colors[1], &colors[4], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[2], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*12*/ &colors[0], &colors[4], &colors[1], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[1], &colors[4], &colors[0],
//        /*13*/ &colors[0], &colors[4], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[1], &colors[4], &colors[0],
//        /*14*/ &colors[0], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[4], &colors[0],
//        /*15*/ &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0], &colors[0]
//     },
//     // Frame 2
//     {
//        /*0*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*1*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*2*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*3*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*4*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*5*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*6*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*7*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*8*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*9*/  &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*10*/ &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*12*/ &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*13*/ &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*14*/ &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//        /*15*/ &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0], &colors[1], &colors[2], &colors[3], &colors[4], &colors[0],
//     },
// };

// double frame_time = 1.0; // seconds per frame