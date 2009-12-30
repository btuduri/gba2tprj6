/**
 * Defines for the functions used for the game interface
 *
 * @date	11/12/09
 * @author  Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */

#ifndef AI_HEADER
#define AI_HEADER

// Main userinterface init function
extern void update_sprite( Sprite s, u16 tiles );
extern void track_ai();
extern void track_bullet();
extern void initialize_ai();
extern void	fire_bullet();
extern int 	random();

#endif