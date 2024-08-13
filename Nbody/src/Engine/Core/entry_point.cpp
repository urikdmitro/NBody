#include "Program/draw_layer.h"
#include "application.h"

#include <CL/cl.h>
#include <iostream>
#include <ostream>

/* void Sandbox(); */

int main() {
  Application &application = Application::GetInstance();

  application.PushLayer(new DrawLayer);
  application.Run();

  /* Sandbox(); */
}

/* void Sandbox() { */
/*   cl_platform_id platform_id = NULL; */
/*   cl_device_id device_id = NULL; */
/*   cl_uint ret_num_devices; */
/*   cl_uint ret_num_platforms; */
/*   cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms); */
/*   ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, */
/*                        &ret_num_devices); */
/**/
/*   std::cout << ret_num_devices << "   " << ret_num_platforms << std::endl; */
/**/
/*   char str[1024]; */
/*   size_t size; */
/*   ret = clGetDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(str), str, &size);
 */
/**/
/*   std::cout << str << std::endl; */
/**/
/*   // Create an OpenCL context */
/*   cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL,
 * &ret); */
/**/
/*   // Create a command queue */
/*   cl_command_queue command_queue = */
/*       clCreateCommandQueue(context, device_id, 0, &ret); */
/* } */
