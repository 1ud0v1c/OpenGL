#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>

char *read_tga(const char *filename, int& width, int& height);
std::string file_contents(const char* file, int* size);
static short le_short(unsigned char *bytes);

#endif
