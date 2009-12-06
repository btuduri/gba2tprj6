
//{{BLOCK(Spacemap)

//======================================================================
//
//	Spacemap, 512x512@8, 
//	+ palette 256 entries, not compressed
//	+ 81 tiles (t|f|p reduced) not compressed
//	+ affine map, not compressed, 64x64 
//	Total size: 512 + 5184 + 4096 = 9792
//
//	Time-stamp: 2009-12-06, 00:33:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SPACEMAP_H
#define GRIT_SPACEMAP_H

#define SpacemapTilesLen 5184
extern const unsigned short SpacemapTiles[2592];

#define SpacemapMapLen 4096
extern const unsigned short SpacemapMap[2048];

#define SpacemapPalLen 512
extern const unsigned short SpacemapPal[256];

#endif // GRIT_SPACEMAP_H

//}}BLOCK(Spacemap)
