#include <CL/cl.h>
#include <iostream>

const char * source = "__kernel void getID () { int gl_id = get_global_id(0); int lc_id = get_local_id(0); int gr_id = get_group_id(0); printf(\"I am from %d block, %d thread (global thread: %d)\\n\", gr_id, lc_id, gl_id); }";

const char * source_2 = "__kernel void getVectorSum (__global int * a, __global int * b, const unsigned int count) { int ind = get_global_id(0); int tr_gl_ind = get_local_id(0); if (ind < count) b[ind] = a[ind] + tr_gl_ind; }";

const unsigned int SIZE = 50;

int main () 
{
	//cl_uint platformCount = 0;
 //   clGetPlatformIDs(0, nullptr, &platformCount);

 //   cl_platform_id* platform = new cl_platform_id[platformCount];
 //   clGetPlatformIDs(platformCount, platform, nullptr);

 //   for (cl_uint i = 0; i < platformCount; ++i) {
 //       char platformName[128];
 //       clGetPlatformInfo(platform[i], CL_PLATFORM_NAME,
	//	128, platformName, nullptr);
 //       std::cout << platformName << std::endl;
 //   }

	// ---------------------------------- Вывод I am from %d block, %d thread (global thread: %d) ----------------------------------------------

	//cl_int error = 0;

	//cl_uint numPlatforms = 0;
	//clGetPlatformIDs(0, NULL, &numPlatforms); 
	//cl_platform_id platform = NULL;

	//if (0 < numPlatforms)
	//{
	//	cl_platform_id * platforms = new cl_platform_id [numPlatforms];
	//	clGetPlatformIDs(numPlatforms, platforms, NULL);
	//	platform = platforms[0];

	//	//char platform_name[128];
	//	//clGetPlatformInfo(platform, CL_PLATFORM_NAME, 128, platform_name, nullptr);
	//	//std::cout << platform_name << std::endl;

	//	delete[] platforms;
	//}


	//// Создание контекста

	//cl_context_properties properties [3] = { 
	//	CL_CONTEXT_PLATFORM, ( cl_context_properties ) platform, 0 };

	//cl_context context = clCreateContextFromType (
	//	( NULL == platform ) ? NULL : properties,
	//	CL_DEVICE_TYPE_GPU,
	//	NULL,
	//	NULL,
	//	&error );

	////if (error != CL_SUCCESS) {
	////	std::cout << "Create context from type failed" << std::endl;
	////}

	//size_t size = 0;

	//clGetContextInfo (
	//	context,
	//	CL_CONTEXT_DEVICES,
	//	0,
	//	NULL,
	//	&size );


	//// Выбор устройства

	//cl_device_id device;

	//if (size > 0)
	//{
	//	cl_device_id * devices = ( cl_device_id * ) alloca ( size );
	//	clGetContextInfo (
	//		context,
	//		CL_CONTEXT_DEVICES,
	//		size,
	//		devices,
	//		NULL );
	//	device = devices[0];
	//	
	//	//char device_name[128];
	//	//clGetDeviceInfo(device, CL_DEVICE_NAME, 128, device_name, nullptr);
	//	//std::cout << device_name << std::endl;
	//}


	//// Создание очереди команд

	//cl_command_queue queue = clCreateCommandQueue(
	//	context,		
	//	device,
	//	0,
	//	&error );

	////if (error != CL_SUCCESS) {
	////	std::cout << "Create command queue with properties failed" << std::endl;
	////}


	//// Создание объектов программы и ядра

	//size_t srclen[] = { strlen(source) };

	//cl_program program = clCreateProgramWithSource(
	//	context,
	//	1,
	//	&source,
	//	srclen,
	//	&error );

	////if (error != CL_SUCCESS) {
	////	std::cout << "Create program with source failed" << std::endl;
	////}

	//clBuildProgram(
	//	program,
	//	1,
	//	&device,
	//	NULL,
	//	NULL,
	//	NULL );

	//cl_kernel kernel = clCreateKernel(program,
	//	"getID",
	//	&error);

	////if (error != CL_SUCCESS) {
	////	std::cout << "Create kernel failed" << std::endl;
	////}


	//// Создание входного и выходного буферов

	//size_t count = SIZE;
	//size_t group = 0;

	//// Запуск ядра

	//clGetKernelWorkGroupInfo (
	//	kernel,
	//	device,
	//	CL_KERNEL_WORK_GROUP_SIZE,
	//	sizeof (size_t),
	//	&group,
	//	NULL );

	//error = clEnqueueNDRangeKernel (
	//	queue,
	//	kernel,
	//	1,
	//	NULL,
	//	&count,
	//	NULL,
	//	0,
	//	NULL,
	//	NULL );

	////if (error != CL_SUCCESS) {
	////	std::cout << "Enqueue failed: " << error << std::endl;
	////}

	//// Освобождение ресурсов

	//clReleaseProgram(program);
	//clReleaseKernel(kernel);
	//clReleaseCommandQueue(queue);
	//clReleaseContext(context);

	// ----------------------------- Сумма элементов вектора и ThreadGlobalIndex -----------------------------

	cl_int error = 0;

	cl_uint numPlatforms = 0;
	clGetPlatformIDs(0, NULL, &numPlatforms); 
	cl_platform_id platform = NULL;

	if (0 < numPlatforms)
	{
		cl_platform_id * platforms = new cl_platform_id [numPlatforms];
		clGetPlatformIDs(numPlatforms, platforms, NULL);
		platform = platforms[0];

		char platform_name[128];
		clGetPlatformInfo(platform, CL_PLATFORM_NAME, 128, platform_name, nullptr);
		std::cout << platform_name << std::endl;

		delete[] platforms;
	}


	// Создание контекста

	cl_context_properties properties [3] = { 
		CL_CONTEXT_PLATFORM, ( cl_context_properties ) platform, 0 };

	cl_context context = clCreateContextFromType (
		( NULL == platform ) ? NULL : properties,
		CL_DEVICE_TYPE_GPU,
		NULL,
		NULL,
		&error );

	if (error != CL_SUCCESS) {
		std::cout << "Create context from type failed" << std::endl;
	}

	size_t size = 0;

	clGetContextInfo (
		context,
		CL_CONTEXT_DEVICES,
		0,
		NULL,
		&size );


	// Выбор устройства

	cl_device_id device;

	if (size > 0)
	{
		cl_device_id * devices = ( cl_device_id * ) alloca ( size );
		clGetContextInfo (
			context,
			CL_CONTEXT_DEVICES,
			size,
			devices,
			NULL );
		device = devices[0];
		
		char device_name[128];
		clGetDeviceInfo(device, CL_DEVICE_NAME, 128, device_name, nullptr);
		std::cout << device_name << std::endl;
	}


	// Создание очереди команд

	cl_command_queue queue = clCreateCommandQueue(
		context,		
		device,
		0,
		&error );

	if (error != CL_SUCCESS) {
		std::cout << "Create command queue with properties failed" << std::endl;
	}


	// Создание объектов программы и ядра

	size_t srclen[] = { strlen(source_2) };

	cl_program program = clCreateProgramWithSource(
		context,
		1,
		&source_2,
		srclen,
		&error );

	if (error != CL_SUCCESS) {
		std::cout << "Create program with source failed" << std::endl;
	}

	clBuildProgram(
		program,
		1,
		&device,
		NULL,
		NULL,
		NULL );

	cl_kernel kernel = clCreateKernel(program,
		"getVectorSum",
		&error);

	if (error != CL_SUCCESS) {
		std::cout << "Create kernel failed" << std::endl;
	}


	// Создание входного и выходного буферов

	size_t count = SIZE;
	size_t group = 0;

	int data[SIZE];
	int results[SIZE];

	for (int i = 0; i < SIZE; i++) {
		data[i] = rand();
	}

	//for (int i = 0; i < SIZE; i++) {
	//	printf("data[%d] = %d\n", i, data[i]);
	//}

	cl_mem a = clCreateBuffer (
		context,
		CL_MEM_READ_ONLY,
		sizeof(int) * SIZE,
		NULL,
		NULL);

	cl_mem b = clCreateBuffer (
		context,
		CL_MEM_WRITE_ONLY,
		sizeof(int) * SIZE,
		NULL,
		NULL);

	error = clEnqueueWriteBuffer (
		queue,
		a,
		CL_TRUE,
		0,
		sizeof(int) * SIZE,
		data,
		0,
		NULL,
		NULL);

	if (error != CL_SUCCESS) {
		std::cout << "Enqueue write buffer failed: " << error << std::endl;
	}

	error = clSetKernelArg (
		kernel,
		0,
		sizeof(cl_mem),
		&a);

	if (error != CL_SUCCESS) {
		std::cout << "Set kernel args for input failed: " << error << std::endl;
	}

	error = clSetKernelArg (
		kernel,
		1,
		sizeof(cl_mem),
		&b);

	if (error != CL_SUCCESS) {
		std::cout << "Set kernel args for output failed: " << error << std::endl;
	}

	error = clSetKernelArg (
		kernel,
		2,
		sizeof(unsigned int),
		&count);

	if (error != CL_SUCCESS) {
		std::cout << "Set kernel args for count failed: " << error << std::endl;
	}

	// Запуск ядра

	clGetKernelWorkGroupInfo (
		kernel,
		device,
		CL_KERNEL_WORK_GROUP_SIZE,
		sizeof (size_t),
		&group,
		NULL );

	error = clEnqueueNDRangeKernel (
		queue,
		kernel,
		1,
		NULL,
		&count,
		NULL,
		0,
		NULL,
		NULL );

	clFinish(queue);

	if (error != CL_SUCCESS) {
		std::cout << "Enqueue failed: " << error << std::endl;
	}

	clEnqueueReadBuffer (
		queue,
		b,
		CL_TRUE,
		0,
		sizeof(int) * count,
		results,
		0,
		NULL,
		NULL);

	printf("RESULTS\n");
	for (int i = 0; i < SIZE; i++) {
		printf("data[%d] = %d; \tresult[%d] = %d\n", i, data[i], i, results[i]);
	}

	// Освобождение ресурсов

	clReleaseMemObject(a);
	clReleaseMemObject(b);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	return 0;
}