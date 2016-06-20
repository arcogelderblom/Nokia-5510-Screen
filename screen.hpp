/*
============================================================================
	File: 		screen.hpp
	Part of:	program for IPASS
	Contains:	Everything necessary for the Nokia 5510 screen
	Made by:	Arco Gelderblom 2016
	Distributed under the Boost Software License, Version 1.0.		
 	(See accompanying file LICENSE_1_0.txt in folder 'License' or 
	copy at http://www.boost.org/LICENSE_1_0.txt) 
============================================================================
*/
/// @file

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "hwlib.hpp"

/// Screen class
//
/// This class sets everything up for a Nokia-5510 screen, in it the options to
/// setup the screen for use, set any desired pixel and draw it to let it see
/// on the actual screen.
class screen {
private:
	/// Nessecary pin output for the reset pin on the screen
	due::pin_out reset;
	/// Nessecary pin output for the chip enable pin on the screen
	due::pin_out sce;
	/// Nessecary pin output for the data/command pin on the screen
	due::pin_out dc;
	/// Nessecary pin output for the data in pin on the screen
	due::pin_out din;
	/// Nessecary pin output for the clock pin on the screen
	due::pin_out sclk;
	/// Array for all the pixels sorted in individual bytes for own access
	int pixels[6][84][8]; // array with all pixels in it represented
public:
	/// Constructor screen
	//
	/// Constructor which initializes everything so the screen and it’s functions can be used
	screen( due::pin_out reset, due::pin_out sce, due::pin_out dc, due::pin_out din, due::pin_out sclk );
	/// Setup the screen
	// 
	/// This needs to be called to setup everything. WITHOUT THIS CALLED THE SCREEN CANNOT BE USED.
	void setup( void );
	/// Draw function
	// 
	/// Every pixel in the array of the screen is gone through and put on screen if the value is 1.
	void draw( void );
	/// Set pixel value
	// 
	/// Give the x and y values of a pixel and give a value (1 or 0) to display the pixel with the next draw or don’t display it
	void set_pixel( int x, int y, int value );
	/// Clear the pixel array
	// 
	/// This function clears the pixel array. If it was for some reason still filled with values everything get’s set to zero. Useful to call before after the setup and before any other things.
	void clear_pixelarray( void );
};

#endif //SCREEN_HPP