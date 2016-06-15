#ifndef TYPE_H
#define TYPE_H

/*------------- 
     类型定义
 --------------*/


// 纹理图像结构
typedef struct
{
    int imgWidth;				// 纹理宽度
    int imgHeight;				// 纹理高度
    unsigned char byteCount;	// 每个象素对应的字节数，3：24位图，4：带alpha通道的24位图
    unsigned char *data;		// 纹理数据
}TEXTUREIMAGE;

// BMP文件头
#pragma pack(2)
typedef struct {
    unsigned short	bfType;			// 文件类型
    unsigned long   bfSize;			// 文件大小
    unsigned short	bfReserved1;	// 保留位
    unsigned short	bfReserved2;	// 保留位
    unsigned long	bfOffBits;		// 数据偏移位置
}BMPFILEHEADER;
#pragma pack()

// BMP信息头
typedef struct {
    unsigned long	biSize;			// 此结构大小
    long			biWidth;		// 图像宽度
    long			biHeight;		// 图像高度
    unsigned short	biPlanes;		// 调色板数量
    unsigned short	biBitCount;		// 每个象素对应的位数，24：24位图，32：带alpha通道的24位图
    unsigned long	biCompression;	// 压缩
    unsigned long	biSizeImage;	// 图像大小
    long			biXPelsPerMeter;// 横向分辨率
    long			biYPelsPerMeter;// 纵向分辨率
    unsigned long	biClrUsed;		// 颜色使用数
    unsigned long	biClrImportant;	// 重要颜色数
}BMPINFOHEADER;

// 材质结构
typedef struct
{
    float ambient[4];			// 环境光反射
    float diffuse[4];    		// 漫反射
    float specular[4];    		// 镜面反射
    float shininess;    		// 镜面反射强度
}MATERIAL;

// 光照结构
typedef struct
{
    float lightAmbient[4];			// 环境光参数
    float lightDiffuse[4];			// 漫射光参数
    float lightSpecular[4];			// 镜面光参数
    float lightPosition[4];			// 光源位置
}LIGHT;
#endif
