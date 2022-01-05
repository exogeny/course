#ifndef HOMEWORK_IMAGE_IO_H
#define HOMEWORK_IMAGE_IO_H

#include <FreeImage.h>

namespace Homework
{

struct Image
{
  /* rgb in the image*/
  unsigned char *value;

  size_t width;
  size_t height;
};

namespace IO
{

// read the image from `filename`.
bool LoadImage(char const *filename, Image *image);

// save the image to `filename`.
bool SaveImage(char const *filename, Image *image);

}  // namespace IO
}  // namespace Homework

#endif  // HOMEWORK_IMAGE_IO_H
