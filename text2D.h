#ifndef TEXT2D_H
#define TEXT2D_H


class Text2D {
	public:
		void initText2D(const char * texturePath);
		void printText2D(const char * text, int x, int y, int size);
		void cleanupText2D();

	private:
		unsigned int text2DTextureID;
		unsigned int text2DVertexBufferID;
		unsigned int text2DUVBufferID;
		unsigned int text2DShaderID;
		unsigned int text2DUniformID;
};

#endif
