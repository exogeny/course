#include "image_io.h"
#include "mean_shift.h"

#include <iostream>

struct Parameter
{
  const char *image_path;
  const char *saved_path;
  double threshold = 50.0;
  int window_size = 50;
};

void PrintHelp(const char *name) {
  printf("Parse the value Error\n");
  printf(
      "Usage: %s imagepath [--output savedpath [--threshold th "
      "[--window-size size]]].\n",
      name);
}

bool ParseArgument(int argc, char **argv, Parameter *parameter) {
  if (argc == 0) {
    return false;
  }

  if (argc >= 1 && strncmp("--", argv[0], 2) != 0) {
    parameter->image_path = argv[0];
    parameter->saved_path = "output.png";
  }

  int index = 1;
  bool valid = true;
  while (index < argc) {
    if (index + 1 == argc) {
      valid = false;
      break;
    }

    if (strcmp("--output", argv[index]) == 0) {
      parameter->saved_path = argv[index + 1];
    } else if (strcmp("--threshold", argv[index]) == 0) {
      parameter->threshold = atof(argv[index + 1]);
      if (parameter->threshold <= 0) {
        printf("The parameter of threshold must be bigger than 0.\n");
        printf("The value will changed to 50.\n");
        parameter->threshold = 50.0;
      }
    } else if (strcmp("--window-size", argv[index]) == 0) {
      parameter->window_size = atoi(argv[index + 1]);
      if (parameter->window_size <= 0) {
        printf("The parameter of window_size must be bigger than 0.\n");
        printf("The value will changed to 50.\n");
        parameter->window_size = 50;
      }
    }
    index += 2;
  }

  return valid;
}

int main(int argc, char **argv) {
  Parameter paramter;
  if (!ParseArgument(argc - 1, argv + 1, &paramter)) {
    PrintHelp(argv[0]);
    return -1;
  }

  Homework::Image image;
  if (!Homework::IO::LoadImage(paramter.image_path, &image)) {
    printf("Read the image Error!\n");
    return -1;
  }
  printf("Loaded the image: %zu x %zu\n", image.height, image.width);

  printf("Start mean shift: window size = %d, threshold = %lf\n",
         paramter.window_size, paramter.threshold);
  unsigned char *output = new unsigned char[image.height * image.width * 3];
  Homework::MeanShift(image.value, output, image.height, image.width,
                      paramter.window_size, paramter.threshold);
  delete[] image.value;

  image.value = output;
  printf("Done! save the result to \"%s\"\n", paramter.saved_path);
  Homework::IO::SaveImage(paramter.saved_path, &image);
  delete[] output;

  return 0;
}
