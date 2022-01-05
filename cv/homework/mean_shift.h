#ifndef HOMEWORK_MEAN_SHIFT_H
#define HOMEWORK_MEAN_SHIFT_H

namespace Homework
{

// Mean shift method.
// Arguments:
//  value for the raw value of image.
//  height, width, channel of image.
//  sw is the size of window for the method, and th is the threshold
//  for stoping.
void MeanShift(unsigned char* value, unsigned char* output, size_t height,
               size_t width, int sw, double th, size_t channel = 3,
               size_t max_iter = 5);

}  // namespace Homework

#endif
