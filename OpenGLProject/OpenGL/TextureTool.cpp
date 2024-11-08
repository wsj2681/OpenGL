#define _CRT_SECURE_NO_WARNINGS
#include "TextureTool.h"

GLuint TextureTool::loadBMP_custom(const char* imagepath)
{
    return GLuint();
}

GLuint TextureTool::LoadDDS(const char* imagepath)
{
    unsigned char header[124];

    FILE* fp = fopen(imagepath, "rb");
    if (!fp)
    {
        cout << "Failed File open :" << imagepath << endl;
        return 0;
    }

    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0)
    {
        fclose(fp);
        cout << imagepath<< "is not DDS File." << endl;
        return 0;
    }

    fread(&header, 124, 1, fp);

    unsigned int height     = *(unsigned int*)&(header[8]);
    unsigned int width      = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount= *(unsigned int*)&(header[24]);
    unsigned int fourCC     = *(unsigned int*)&(header[80]);

    unsigned int buffersize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    unsigned char* buffer = (unsigned char*)malloc(buffersize * sizeof(unsigned char));

    fread(buffer, 1, buffersize, fp);

    fclose(fp);
    
    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;

    switch (fourCC)
    {
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
        cout << "Cannot Define format. fourCC : "<< fourCC << endl;
        free(buffer);
        return 0;
    }

    GLuint textureID = 0;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        if (width < 1)
        {
            width = 1;
        }

        if (height < 1) 
        {
            height = 1;
        }

    }

    free(buffer);

    this->textureID = textureID;
    return textureID;
}
