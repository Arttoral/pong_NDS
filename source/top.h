
//{{BLOCK(top)

//======================================================================
//
//	top, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 403 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 25792 + 1536 = 27840
//
//	Time-stamp: 2025-10-08, 21:37:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TOP_H
#define GRIT_TOP_H

#define topTilesLen 25792
extern const unsigned int topTiles[6448];

#define topMapLen 1536
extern const unsigned short topMap[768];

#define topPalLen 512
extern const unsigned short topPal[256];

#endif // GRIT_TOP_H

//}}BLOCK(top)
