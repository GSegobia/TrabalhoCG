#include "TexturePixMap.h"

typedef unsigned short ushort;
typedef unsigned long ulong;
fstream file_content;

/*
	Implementação de métodos de apoio
*/

ushort getShort(){

	char byte;
	ushort s_byte;

	file_content.get(byte);
	s_byte = byte;

	file_content.get(byte);
	s_byte |= ((ushort)byte << 8);

	return s_byte;
}

ulong getLong(){

	ulong l_byte;
	char byte;
	unsigned char uc;

	file_content.get(byte);
	uc = byte;
	l_byte = uc;

	file_content.get(byte);
	uc = byte;
	l_byte |= ((ulong)uc << 8);

	file_content.get(byte);
	uc = byte;
	l_byte |= ((ulong)uc << 16);

	file_content.get(byte);
	uc = byte;
	l_byte |= ((ulong)uc << 24);

	return l_byte;
}

/*
	Implementação de métodos da Classe TexturePixMap
*/

TexturePixMap::TexturePixMap(){

	number_of_rows = 0;
	number_of_columns = 0;
	pixel_map = 0;
}

TexturePixMap::TexturePixMap(int rows, int cols){

	number_of_rows = rows;
	number_of_columns = cols;
	pixel_map = new RGB[number_of_rows * number_of_columns];
}

int TexturePixMap::readBMPFile(string file_name, bool has_alpha){

	file_content.open(file_name.c_str(), ios::in|ios::binary);
	if(!file_content){

		cout << "Can not open file " << file_name << "." << endl;
		return 0;
	}

	int num_pad_bytes, num_bytes_in_row;
	int count = 0;
	char ch1, ch2, dum;

	file_content.get(ch1);
	file_content.get(ch2);

	ulong file_size			= getLong();
	ushort reserved1    	= getShort();	// always 0
	ushort reserved2    	= getShort();	// always 0 
	ulong off_bits      	= getLong();	// offset to image - unreliable
	ulong header_size   	= getLong();	// always 40
	ulong num_cols      	= getLong();	// number of columns in image
	ulong num_rows      	= getLong();	// number of rows in image
	ushort planes			= getShort();	// always 1 
	ushort bits_per_pixel	= getShort();	//8 or 24; allow 24 here
	ulong compression   	= getLong();	// must be 0 for uncompressed 
	ulong image_size    	= getLong();	// total bytes in image 
	ulong x_pels         	= getLong();	// always 0 
	ulong y_pels         	= getLong();	// always 0 
	ulong num_LUT_entries 	= getLong();	// 256 for 8 bit, otherwise 0 
	ulong imp_colors     	= getLong();	// always 0

	if(bits_per_pixel != 24){

		cout << "Not a 24 bit/pixel image or compressed." << endl;
		file_content.close();
		return 0;
	}

	number_of_rows = num_rows;
	number_of_columns = num_cols;

	num_bytes_in_row = ((3 * number_of_columns + 3)/4) * 4;
	num_pad_bytes = num_bytes_in_row -3 * number_of_columns;

	pixel_map = new RGB[num_rows * number_of_columns];

	if(!pixel_map)
		return 0;


	for(int row = 0; row < number_of_rows; row++){

		for(int col = 0; col < number_of_columns; col++){

			char r, g, b;

			file_content.get(b);
			file_content.get(g);
			file_content.get(r);

			pixel_map[count].red 	= r;
			pixel_map[count].green	= g;
			pixel_map[count].blue 	= b;

			if((has_alpha) && (r == -1) && (g == -1) && (b == -1))
				pixel_map[count].alpha = 0;
			else
				pixel_map[count].alpha = 255;

			count++;
		}

		for(int i = 0; i < num_pad_bytes; i++)
			file_content >> dum;
	}

	file_content.close();

	return 1;
}

void TexturePixMap::setTexture(GLuint texture_name){

	glBindTexture(GL_TEXTURE_2D,texture_name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, number_of_columns, number_of_rows,0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_map);
}