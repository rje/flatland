//
//  Texture.cpp
//  flatland
//
//  Created by Ryan Evans on 6/5/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Texture.h"
#include "TextureBindings.h"
#include "FileIO.h"
#include <png.h>

TextureMap Texture::sm_textures;

Texture::Texture() {
    
}

Texture::~Texture() {
    
}

void Texture::InitWithFile(string& filepath) {
    FILE* fd = FileIO::OpenFileDescriptor(filepath);
    png_byte header[8];
    fread(header, 1, 8, fd);
    
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
        printf("ERROR: %s is not a valid png file\n", filepath.c_str());
        fclose(fd);
        return;
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fd);
        return;
    }
    
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        fclose(fd);
        return;
    }
    
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fd);
        return;
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fd);
        return;
    }
    png_init_io(png_ptr, fd);
    
    png_set_sig_bytes(png_ptr, 8);
    
    png_read_info(png_ptr, info_ptr);
    
    GLint bit_depth, color_type;
    
    png_get_IHDR(png_ptr, info_ptr, &m_width, &m_height, &bit_depth, &color_type, NULL, NULL, NULL);
    
    png_read_update_info(png_ptr, info_ptr);
    
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    
    png_byte *image_data = new png_byte[rowbytes * m_height];
    if (!image_data) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fd);
        return;
    }
    
    png_bytep *row_pointers = new png_bytep[m_height];
    if (!row_pointers) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        fclose(fd);
        return;
    }
    
    for (int i = 0; i < m_height; ++i) {
        row_pointers[m_height - 1 - i] = image_data + i * rowbytes;
    }
    
    png_read_image(png_ptr, row_pointers);
    
    glGenTextures(1, &m_glTextureID);
    m_dataType = GL_UNSIGNED_BYTE;
    m_pixelFormat = GL_RGBA;
    m_targetType = GL_TEXTURE_2D;
    
    glBindTexture(m_targetType, m_glTextureID);
    glTexImage2D(m_targetType,0, m_pixelFormat, m_width, m_height, 0, m_pixelFormat, m_dataType, (GLvoid*) image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    delete[] row_pointers;
    fclose(fd);

}

void Texture::SetAsActive() {
    glBindTexture(GL_TEXTURE_2D, m_glTextureID);
}

void Texture::SetWrappedObject(Persistent<Object>& handle) {
    m_wrappedObj = handle;
}

Persistent<Object> Texture::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedObj.IsEmpty()) {
        m_wrappedObj = Persistent<Object>::New(TextureBindings_WrapTexture(this)->ToObject());
    }
    return m_wrappedObj;
}

Texture* Texture::TextureForFile(string& filepath) {
	if(sm_textures.find(filepath) != sm_textures.end()) {
		return sm_textures[filepath];
	}
	else {
		Texture* t = new Texture();
		t->InitWithFile(filepath);
		sm_textures[filepath] = t;
		return t;
	}
}