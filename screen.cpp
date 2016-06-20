/*
============================================================================
	File: 		screen.cpp
	Part of:	program for IPASS
	Contains:	Implementation of the functions declared in
	the header file screen.hpp
	Made by:	Arco Gelderblom 2016
	Distributed under the Boost Software License, Version 1.0.		
 	(See accompanying file LICENSE_1_0.txt in folder 'License' or 
	copy at http://www.boost.org/LICENSE_1_0.txt) 
============================================================================
*/

#include "screen.hpp"

screen::screen( due::pin_out reset, due::pin_out sce, due::pin_out dc, due::pin_out din, due::pin_out sclk ) :
	reset( reset ),
	sce( sce ),
	dc( dc ),
	din( din ),
	sclk( sclk )
{}

void screen::setup( void ) {
	reset.set(0);
	reset.set(1);
	dc.set(0);
	sce.set(1);
	sce.set(0);
	int bytes[8][8] = { {0,0,1,0,0,0,0,1}, // LCD extended commands with horizontal adressing
						{1,1,0,0,1,0,0,0}, // set contrast
						{0,0,0,0,0,1,1,0}, // set temp coefficient
						{0,0,0,1,0,0,1,1}, // LCD bias mode
						{0,0,1,0,0,0,0,0}, // basic commands
						{0,0,0,0,1,1,0,0}, // set normal mode
						{0,1,0,0,0,0,0,0}, // set y-address to 0
						{1,0,0,0,0,0,0,0} }; // set x-address to 0
	for(int i = 0; i<8;i++) {
		for(int j = 0; j<8;j++) {
			sclk.set(0);
			din.set(bytes[i][j]);
			sclk.set(1);
		}
	}
	//set every pixel to 0 (clear the screen in memory)
	for( int y = 0; y<6; y++ ) {
		for( int x = 0; x<84; x++ ) {
			for( int bit = 7; bit>=0; bit-- ) {
				pixels[y][x][bit] = 0;
			}
		}
	}
	sce.set(1);
}

void screen::draw( void ) {
	reset.set(0);
	reset.set(1);
	dc.set(1);
	sce.set(1);
	sce.set(0);
	for( int y = 0; y<6; y++ ) {
		for( int x = 0; x<84; x++ ) {
			for( int bit = 7; bit>=0; bit-- ) { // First din is MSB, zo read byte backwards
				sclk.set(0);
				din.set(pixels[y][x][bit]);
				sclk.set(1);
				hwlib::wait_us(10);
			}
		}
	}
	sce.set(1);
}

void screen::set_pixel( int x, int y, int value ) {
	// loads of if statements needed because of the way the screen handles data, data is
	// stored in bytes so 6 bytes per x row for all y's.
	if( y >= 0 && y <= 7) {
		pixels[0][x][y] = value;
	}
	else if ( y >= 8 && y <= 15) {
		pixels[1][x][y-8] = value;
	}
	else if ( y >= 16 && y <= 23) {
		pixels[2][x][y-16] = value;
	}
	else if( y >= 24 && y <= 31) {
		pixels[3][x][y-24] = value;
	}
	else if( y >= 32 && y <= 39) {
		pixels[4][x][y-32] = value;
	}
	else if( y >= 40 && y <= 47) {
		pixels[5][x][y-40] = value;
	}
}

void screen::clear_pixelarray( void ) {
	// complicated loop but in short it does the following: it sets every object in the array to value 0
	for( int y = 0; y<6; y++ ) {
		for( int x = 0; x<84; x++ ) {
			for( int bit = 7; bit>=0; bit-- ) {
				pixels[y][x][bit] = 0;
			}
		}
	}
}