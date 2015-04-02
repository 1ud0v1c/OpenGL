#include "utils.h"

char *read_tga(const char *filename, int& width, int& height) {
	struct tga_header {
		char  id_length;
		char  color_map_type;
		char  data_type_code;
		unsigned char  color_map_origin[2];
		unsigned char  color_map_length[2];
		char  color_map_depth;
		unsigned char  x_origin[2];
		unsigned char  y_origin[2];
		unsigned char  width[2];
		unsigned char  height[2];
		char  bits_per_pixel;
		char  image_descriptor;
	} header;
	int i, color_map_size;
	FILE *f;
	size_t read;
	char *pixels;

	f = fopen(filename, "rb");

	if (!f) {
		fprintf(stderr, "Unable to open %s for reading\n", filename);
		return NULL;
	}

	read = fread(&header, 1, sizeof(header), f);

	if (read != sizeof(header)) {
		fprintf(stderr, "%s has incomplete tga header\n", filename);
		fclose(f);
		return NULL;
	}
	if (header.data_type_code != 2) {
		fprintf(stderr, "%s is not an uncompressed RGB tga file\n", filename);
		fclose(f);
		return NULL;
	}
	if (header.bits_per_pixel != 24) {
		fprintf(stderr, "%s is not a 24-bit uncompressed RGB tga file\n", filename);
		fclose(f);
		return NULL;
	}

	for (i = 0; i < header.id_length; ++i)
		if (getc(f) == EOF) {
			fprintf(stderr, "%s has incomplete id string\n", filename);
			fclose(f);
			return NULL;
		}

	color_map_size = le_short(header.color_map_length) * (header.color_map_depth/8);
	for (i = 0; i < color_map_size; ++i)
		if (getc(f) == EOF) {
			fprintf(stderr, "%s has incomplete color map\n", filename);
			fclose(f);
			return NULL;
		}

	width = le_short(header.width); height = le_short(header.height);
	unsigned int pixels_size = width * height * (header.bits_per_pixel/8);
	pixels = new char[pixels_size];

	read = fread(pixels, 1, pixels_size, f);

	if (read != pixels_size) {
		fprintf(stderr, "%s has incomplete image\n", filename);
		fclose(f);
		delete [] pixels;
		return NULL;
	}

	return pixels;
}


std::string file_contents(const std::string &file, int* size){
	std::string resultat;
	std::string line;
	std::ifstream stream(file);
	if (stream.is_open()){
		while(getline(stream,line)){
			resultat += line+"\n";
		}
		stream.close();
	}else {
		std::cout << "Error reading shaders" << std::endl;
	}
	*size=resultat.size();
	return resultat;
}


static short le_short(unsigned char *bytes) {
	return bytes[0] | ((char)bytes[1] << 8);
}


GLuint loadTGATexture(const std::string& imagepath, int width, int height,GLenum wrap_s, GLenum wrap_t, GLenum mag_filter, GLenum min_filter, bool anisotropy)  {
	char *data = read_tga(imagepath.c_str(),width,height);
	GLuint textureID=0;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
	// Interpolation method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D); //Generate mipmaps now!!!

	return textureID;
}

GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path){
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844 
#define FOURCC_DXT5 0x35545844 

GLuint loadDDS(const char * imagepath){
	unsigned char header[124];
	FILE *fp; 

	fp = fopen(imagepath, "rb"); 
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); 
		return 0;
	}

	/* verify the type of file */ 
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		std::cout << "L'extension que vous utilisez semble eronnée !" << std::endl;
		fclose(fp); 
		return 0; 
	}

	/* get the surface desc */ 
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width           = *(unsigned int*)&(header[12]);
	unsigned int linearSize  = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 
	/* close the file pointer */ 
	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC){ 
		case FOURCC_DXT1: 
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
			break; 
		case FOURCC_DXT3: 
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
			break; 
		case FOURCC_DXT5: 
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
			break; 
		default: 
			free(buffer); 
			return 0; 
	}
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);   

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	/* load the mipmaps */ 
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) { 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
				0, size, buffer + offset); 

		offset += size; 
		width  /= 2; 
		height /= 2; 

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	free(buffer); 
	return textureID;
}

glm::vec3 getMaxPosition(std::vector<glm::vec3> positions){
	double x=0.0,y=0.0,z=0.0;
	for(std::vector<glm::vec3>::iterator it = positions.begin(); it != positions.end(); it++) {
		if ((*it).x > x){
			x= (*it).x;
		}
		if ((*it).y > y){
			y= (*it).y;
		}
		if ((*it).z > z){
			z= (*it).z;
		}
	}
	return glm::vec3(x,y,z);
}

glm::vec3 getMinPosition(std::vector<glm::vec3> positions){
	double x=600.0,y=600.0,z=600.0;
	for(std::vector<glm::vec3>::iterator it = positions.begin(); it != positions.end(); it++) {
		if ((*it).x < x){
			x= (*it).x;
		}
		if ((*it).y < y){
			y= (*it).y;
		}
		if ((*it).z < z){
			z= (*it).z;
		}
	}
	return glm::vec3(x,y,z);
}
