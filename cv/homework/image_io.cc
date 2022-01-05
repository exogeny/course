#include "image_io.h"

namespace Homework
{
namespace IO
{

bool LoadImage(char const *filename, Image *image) {
  FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);

  if (fif == FIF_UNKNOWN) {
    fif = FreeImage_GetFIFFromFilename(filename);
  }

  if (fif == FIF_UNKNOWN) {
    return false;
  }

  // read the data from image
  FIBITMAP *bitmap = FreeImage_Load(fif, filename, 0);
  if (bitmap) {
    unsigned int width = FreeImage_GetWidth(bitmap);
    unsigned int height = FreeImage_GetHeight(bitmap);

    // convert the image to RGB format
    FIBITMAP *bytes = FreeImage_ConvertTo24Bits(bitmap);

    if (image && bytes && width > 0 && height > 0) {
      int index;
      RGBQUAD pixel;
      image->value = new unsigned char[height * width * 3];
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          index = (y * width + x);
          FreeImage_GetPixelColor(bytes, x, height - y - 1, &pixel);

          image->value[index * 3 + 0] = pixel.rgbRed;
          image->value[index * 3 + 1] = pixel.rgbGreen;
          image->value[index * 3 + 2] = pixel.rgbBlue;
        }
      }
      image->width = width;
      image->height = height;

      return true;
    }
  }
  return false;
}

bool SaveImage(char const *filename, Image *image) {
  FIBITMAP *bitmap = FreeImage_Allocate(image->width, image->height, 24);
  if (!bitmap) {
    return false;
  }

  int index;
  RGBQUAD pixel;
  for (int y = 0; y < image->height; ++y) {
    for (int x = 0; x < image->width; ++x) {
      index = (y * image->width + x);
      pixel.rgbRed   = image->value[index * 3 + 0];
      pixel.rgbGreen = image->value[index * 3 + 1];
      pixel.rgbBlue  = image->value[index * 3 + 2];
      FreeImage_SetPixelColor(bitmap, x, image->height - y - 1, &pixel);
    }
  }
  return FreeImage_Save(FREE_IMAGE_FORMAT::FIF_PNG, bitmap, filename);
}

}  // namespace IO
}  // namespace Homework
