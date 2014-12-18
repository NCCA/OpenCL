#include "OpenCL.h"
#include <fstream>
#include <string>
#include <iostream>


OpenCL::OpenCL()
{
  initCL();
}

OpenCL::OpenCL(std::string _kernel)
{
  initCL();
  loadKernelSource(_kernel);
}

OpenCL::~OpenCL()
{
  clReleaseProgram(m_program);
  clReleaseKernel(m_kernel);
  clReleaseCommandQueue(m_commands);
  clReleaseContext(m_context);
}

void OpenCL::initCL()
{
  int err;                            // error code returned from api calls

  // Connect to a compute device
  //
  int gpu = 1;
  err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &m_deviceID, NULL);
  if (err != CL_SUCCESS)
  {
      std::cerr<<"Error: Failed to create a device group!\n";
      exit( EXIT_FAILURE);
  }

  // Create a compute context
  //
  m_context = clCreateContext(0, 1, &m_deviceID, NULL, NULL, &err);
  if (!m_context)
  {
      std::cerr<<"Error: Failed to create a compute context!\n";
      exit( EXIT_FAILURE);
  }

  // Create a command commands
  //
  m_commands = clCreateCommandQueue(m_context, m_deviceID, 0, &err);
  if (!m_commands)
  {
      std::cerr<<"Error: Failed to create a command commands!\n";
      exit( EXIT_FAILURE);
  }

}


void OpenCL::loadKernelSource(const std::string &_fname)
{
  std::ifstream kernelSource(_fname.c_str());
  std::string *source;
  if (!kernelSource.is_open())
  {
   std::cerr<<"File not found "<<_fname.c_str()<<"\n";
   exit(EXIT_FAILURE);
  }
  // now read in the data
  source = new std::string((std::istreambuf_iterator<char>(kernelSource)), std::istreambuf_iterator<char>());
  kernelSource.close();
  *source+="\0";

  const char* data=source->c_str();
  int err;                            // error code returned from api calls

  m_program = clCreateProgramWithSource(m_context, 1, (const char **) & data, NULL, &err);
  if (!m_program)
  {
      std::cerr<<"Error: Failed to create compute program!\n";
      exit (EXIT_FAILURE);
  }
  delete source;

  // Build the program executable
  //
  err = clBuildProgram(m_program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS)
  {
      size_t len;
      char buffer[2048];

      std::cerr<<"Error: Failed to build program executable!\n";
      clGetProgramBuildInfo(m_program, m_deviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
      std::cerr<<buffer<<"\n";
      exit(EXIT_FAILURE);
  }
}

void OpenCL::createKernel(const std::string &_name)
{
  int err;
  m_kernel = clCreateKernel(m_program, _name.c_str(), &err);
  if (!m_kernel || err != CL_SUCCESS)
  {
      std::cerr<<"Error: Failed to create compute kernel!\n";
      exit(EXIT_FAILURE);
  }
}
