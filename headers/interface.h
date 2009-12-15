/**
 * Defines for the functions used for the game score
 *
 * @date	11/12/09
 * @author  Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */

#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include "../interface/text_1.h"
#include "../interface/text_2.h"
#include "../interface/text_3.h"
#include "../interface/text_4.h"
#include "../interface/text_5.h"
#include "../interface/text_6.h"
#include "../interface/text_7.h"
#include "../interface/text_8.h"
#include "../interface/text_9.h"
#include "../interface/text_0.h"

// Main userinterface init function
extern void initialize_interface();

// Scores
extern void set_score( int score );
extern int get_score();

// Health
extern void set_health( int health );
extern int get_health();

#endif