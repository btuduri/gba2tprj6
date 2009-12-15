/**
 * Defines for the functions used for the game score
 *
 * @date	11/12/09
 * @author  Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */

#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include "../text/text_1.h"
#include "../text/text_2.h"
#include "../text/text_3.h"
#include "../text/text_4.h"
#include "../text/text_5.h"
#include "../text/text_6.h"
#include "../text/text_7.h"
#include "../text/text_8.h"
#include "../text/text_9.h"
#include "../text/text_0.h"

extern int segment_1, segment_2, segment_3, segment_4;
extern Sprite score_1, score_2;


// Main userinterface init function
extern void initialize_interface();

// Scores
extern void set_score( int score );
extern int get_score();

// Health
extern void set_health( int health );
extern int get_health();

#endif