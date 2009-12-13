
//{{BLOCK(Spacemap)

//======================================================================
//
//	Spacemap, 512x512@8, 
//	+ palette 256 entries, not compressed
//	+ 140 tiles (t reduced) not compressed
//	+ affine map, not compressed, 64x64 
//	Total size: 512 + 8960 + 4096 = 13568
//
//	Time-stamp: 2009-12-13, 16:07:52
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
// 	@date	13/12/09
// 	@author	Sebastiaan Seegers
// 	@email	Sseegers@gmail.com
//======================================================================

#ifndef GRIT_SPACEMAP_H
#define GRIT_SPACEMAP_H

#define SpacemapTilesLen 8960
extern const unsigned short SpacemapTiles[4480];

#define SpacemapMapLen 4096
extern const unsigned short SpacemapMap[2048];

#define SpacemapPalLen 512
extern const unsigned short SpacemapPal[256];

#endif // GRIT_SPACEMAP_H

//}}BLOCK(Spacemap)
