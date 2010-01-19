/**
 * Defines for the functions used for the game interface
 *
 * @date	11/12/09
 * @author  Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */

#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include "../interface/interfacebg.h"
#include "../interface/healthbar.h"
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

/* @ note : Dont set sprites on higher numbers then 50 @ */

// Main userinterface init function
extern void initialize_interface();
extern int ship_maxhealth;

// Scores
extern void set_score( int score );
extern void load_highscores();
extern void save_highscore();
extern int get_score();

//Show highscore
extern void show_highscore( int x , int y);
extern int pow(int x,int y);

// Health
extern void set_health( int hp );
extern int get_health();


#endif