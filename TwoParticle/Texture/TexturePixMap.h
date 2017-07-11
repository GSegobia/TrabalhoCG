#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned char uchar;

GLuint tex;

class RGB{

public: 

	uchar red;
	uchar green;
	uchar blue;
	uchar alpha;
	
	RGB(){
		
		red = green = blue = 0;
		alpha = 255;
	}
};

class TexturePixMap{

private:
	RGB *pixel_map;

public:
	int number_of_rows, number_of_columns;
	TexturePixMap();
	TexturePixMap(int rows, int cols);
	int readBMPFile(string file_name, bool has_alpha);
	void setTexture(GLuint texture_name);
};