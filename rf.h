#ifndef RF_H
#define RF_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "type.h"

void LoadBmp(char *filename, TEXTUREIMAGE *textureImg)
{
	int i, j;
	FILE *file;
	BMPFILEHEADER bmpFile;
	BMPINFOHEADER bmpInfo;
	int pixel_size;

	// 初始化纹理数据
	
	textureImg->imgWidth = 0;
	textureImg->imgHeight = 0;
	if (textureImg->data != NULL)
	{
		delete []textureImg->data;
	}

	// 打开文件
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		return;
	}
	// 获取文件头
	rewind(file);
	fread(&bmpFile, sizeof(BMPFILEHEADER), 1, file);
	fread(&bmpInfo, sizeof(BMPINFOHEADER), 1, file);
	// 验证文件类型
	if (bmpFile.bfType != 0x4D42)
	{
		return;
	}
	// 获取图像色彩数
	pixel_size = bmpInfo.biBitCount >> 3;
	
	// 读取文件数据
	textureImg->data = new unsigned char[bmpInfo.biWidth * bmpInfo.biHeight * pixel_size];
	
	
	for(i = 0 ; i < bmpInfo.biHeight; i++)
	{
		fseek(file, bmpFile.bfOffBits + (bmpInfo.biHeight - i - 1) * bmpInfo.biWidth * pixel_size, SEEK_SET);	

		for (j = 0; j < bmpInfo.biWidth; j++)
		{
			// 红色分量
			fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 2, sizeof(unsigned char), 1, file);
			// 绿色分量
			fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 1, sizeof(unsigned char), 1, file);
			// 蓝色分量
			fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 0, sizeof(unsigned char), 1, file);
			// Alpha分量
			if (pixel_size == 4)
			{
				fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 3, sizeof(unsigned char), 1, file);
			}
		}
	}
	// 记录图像相关参数
	textureImg->imgWidth = bmpInfo.biWidth;
	textureImg->imgHeight = bmpInfo.biHeight;
	textureImg->byteCount = pixel_size;
	fclose(file);
}

#endif