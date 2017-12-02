#include "texture.h"
#include <fstream>
#include <iostream>
#include "stdlib.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#define GL_GLEXT_PROTOTYPES
#endif

// JPEG Lib
#include "jpeglib.h"
#include "jerror.h"

using namespace std;

Texture::Texture(char const* FileName, bool Fast) {
	// Function to load a JPEG file to be used as a texture
	FILE* file = fopen(FileName, "rb");  //open the file
	struct jpeg_decompress_struct info;  //the jpeg decompress info
	struct jpeg_error_mgr err;           //the error handler

	info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
	jpeg_create_decompress(&info);       //sets info to all the default stuff

	//if the jpeg file didnt load exit
	if(!file)
	{
		fprintf(stderr, "Error reading JPEG file %s!!!", FileName);
		this->loaded = false;
	}

	jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we're reading

	jpeg_read_header(&info, TRUE);   //tell it to start reading it

	//if it wants to be read fast or not
	if(Fast)
	{
		info.do_fancy_upsampling = FALSE;
	}

	jpeg_start_decompress(&info);    //decompress the file

	//set the x and y
	this->x = info.output_width;
	this->y = info.output_height;
	this->channels = info.num_components;

	this->type = GL_RGB;

	if(channels == 4)
	{
		this->type = GL_RGBA;
	}

	this->bpp = channels * 8;

	this->size = this->x * this->y * 3;

	//read turn the uncompressed data into something ogl can read
	this->texData = new GLbyte[this->size];      //setup data for the data its going to be handling

	GLbyte* p1 = this->texData;
	GLbyte** p2 = &p1;
	int numlines = 0;

	while(info.output_scanline < info.output_height)
	{
		numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
		*p2 += numlines * 3 * info.output_width;
	}

	jpeg_finish_decompress(&info);   //finish decompressing this file

	fclose(file);                    //close the file
	this->loaded = true;
}