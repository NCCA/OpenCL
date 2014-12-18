#ifndef OPENCL_H__
#define OPENCL_H__

#include <OpenCL/opencl.h>
#include <string>

class OpenCL
{
  public :
    OpenCL(std::string _kernel);
    OpenCL();
    void loadKernelSource(const std::string &_fname);
    inline cl_context getContext() const {return m_context;}
    inline cl_kernel getKernel() const {return m_kernel;}
    inline cl_command_queue getCommands() const {return m_commands;}
    inline cl_device_id getID()const {return m_deviceID;}
    void createKernel(const std::string &_name);
    ~OpenCL();

  private :
    void initCL();
    size_t m_global;                      // global domain size for our calculation
    size_t m_local;                       // local domain size for our calculation

    cl_device_id m_deviceID;             // compute device id
    cl_context m_context;                 // compute context
    cl_command_queue m_commands;          // compute command queue
    cl_program m_program;                 // compute program
    cl_kernel m_kernel;                   // compute kernel




};


#endif
