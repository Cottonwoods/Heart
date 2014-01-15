#include "Level.h"


Tutorial0_1::Tutorial0_1( float r, int entrance, Alonebot* p, FMOD::System* fsys, FMOD::Channel* sfx ) :
Level( r, entrance, p, fsys, sfx ) {
	// Inititalize area and size of level
	area = 0;
	levelWidth = 1440;
	levelHeight = 480;

	// Initialize backgrounds and music
	bgMusic = "..\\music\\beat496-stag.mp3";
	background = LoadTexture( std::string( "..\\anims\\bg\\bg_01.png" ) );
	backbackground = LoadTexture( std::string( "..\\anims\\bg\\bbg_01.png" ) );
	
	// Create player, placement depending upon the entrance taken
	switch( entrance ) {
	  case 0:
		player = new Alonebot( 20.f, 316.f, p->dir, p ); break;
	  case 1:
		player = new Alonebot( 20.f, 116.f, p->dir, p ); break;
	  case 2:
		player = new Alonebot( levelWidth - 38.f, 316.f, p->dir, p ); break;
	  case 3:
		player = new Alonebot( levelWidth - 38.f, 116.f, p->dir, p ); break;
	}

	// Add static level objects to array
	objects.push_back( new Box( 0.f, 376.f, levelWidth ) );					// Ground floor
	objects.push_back( new Box( 0.f, 176.f, 92 ) );							// Left door platform
	objects.push_back( new Dropbox( 100.f, 234.f, 64 ) );					// Staircase platforms
	objects.push_back( new Dropbox( 180.f, 292.f, 64 ) );
	objects.push_back( new Box( 270.f, 344.f, 57 ) );						//  Last staircase platform before sawblade
	objects.push_back( new Box( 218.f, 180.f, 64 ) );						// Floating platform at start
	objects.push_back( new Box( 378.f, 156.f, 64 ) );						// Floating platforms leading to edge
	objects.push_back( new Box( 538.f, 132.f, 64 ) );
	objects.push_back( new Box( 698.f, 108.f, 72 ) );						// Highest platform, slightly longer
	objects.push_back( new Box( 874.f, 156.f, 128 ) );						// Two long platforms
	objects.push_back( new Box( 1126.f, 166.f, 128 ) );						//  before the edge
	objects.push_back( new Box( 1368.f, 176.f, 72 ) );						// Edge platform with door
	objects.push_back( new Box( 452.f, 360.f, 75 ) );						// Three bottom platforms between sawblades
	objects.push_back( new Box( 652.f, 360.f, 75 ) );
	objects.push_back( new Box( 852.f, 360.f, 75 ) );
	objects.push_back( new Box( 1052.f, 360.f, 75 ) );

	// Add doors
	doors.push_back( new Door( 0.f, 112.f, 1, false, 0, 2 ) );				// Top left door
	doorToppers.push_back( new Door( 0.f, 112.f, 1, true ) );
	objects.push_back( new Box( 0.f, 112.f, 16, 4 ) );

	doors.push_back( new Door( 0.f, 312.f, 1, false, 0, 1 ) );				// Bottom left door
	doorToppers.push_back( new Door( 0.f, 312.f, 1, true ) );
	objects.push_back( new Box( 0.f, 312.f, 16, 4 ) );
	
	doors.push_back( new Door( levelWidth - 32.f, 112.f, -1, false, 2, 1 ) );// Top right door
	doorToppers.push_back( new Door( levelWidth - 32.f, 112.f, -1, true ) );
	objects.push_back( new Box( levelWidth - 16.f, 112.f, 16, 4 ) );

	doors.push_back( new Door( levelWidth - 32.f, 312.f, -1, false, 2, 0 ) );// Bottom right door
	doorToppers.push_back( new Door( levelWidth - 32.f, 312.f, -1, true ) );
	objects.push_back( new Box( levelWidth - 16.f, 312.f, 16, 4 ) );

	// Add enemies
	enemies.push_back( new Sawblade( 125, Vector2D( 327.f, 360.f ) ) );
	enemies.push_back( new Sawblade( 125, Vector2D( 527.f, 360.f ) ) );
	enemies.push_back( new Sawblade( 125, Vector2D( 727.f, 360.f ) ) );
	enemies.push_back( new Sawblade( 125, Vector2D( 927.f, 360.f ) ) );

	// Start the heart
	player->init( fmodSystem );
	heartBeat.start( );
	
	// Try to center the camera
	cameraX = player->pos.x - 320;
	cameraY = player->pos.y - 240;
}

Tutorial0_1::~Tutorial0_1( ) {
	typedef unsigned short sho;
	
	sfxChannel->stop( );
	delete player;
	for( sho i=0; i<NPCs.size( ); i++ )
		delete NPCs[i];
	for( sho i=0; i<items.size( ); i++ )
		delete items[i];
	for( sho i=0; i<doors.size( ); i++ )
		delete doors[i];
	for( sho i=0; i<doorToppers.size( ); i++ )
		delete doorToppers[i];
	for( sho i=0; i<objects.size( ); i++ )
		delete objects[i];
	for( sho i=0; i<enemies.size( ); i++ )
		delete enemies[i];
	for( sho i=0; i<bullets.size( ); i++ )
		delete bullets[i];
	glDeleteTextures( 1, &background );
	glDeleteTextures( 1, &backbackground );
}

void Tutorial0_1::process_events( float dt ) {
	logic( dt );

	collision( );

	maintenence( dt );
}