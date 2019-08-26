#include <stdio.h>
#include <Python.h>
#include "numpy/ndarraytypes.h"
#include "numpy/ufuncobject.h"
#include "numpy/npy_3kcompat.h"

// Module method definitions
static PyObject* hello_world_c(PyObject *self, PyObject *args) {
    printf("Hello, world!\n");
    Py_RETURN_NONE;
}
#define r(obj, x0, x1) (*(npy_float64*)((PyArray_DATA(obj) +                \
                                    (x0) * PyArray_STRIDES(obj)[0] +   \
                                    (x1) * PyArray_STRIDES(obj)[1])))

static PyObject* hello_numpy_c(PyObject *dummy, PyObject *args)
{
    PyObject *arg1=NULL;
    PyObject *arr1=NULL;
    int nd;

    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &arg1))
        return NULL;

    arr1 = PyArray_FROM_OTF(arg1, NPY_DOUBLE, NPY_IN_ARRAY);
    /*
     * my code starts here
     */

	//PyArg_ParseTuple(
    nd=PyArray_NDIM(arr1);

	npy_intp *dims = PyArray_DIMS(arr1);
	for (int i = 0; i < nd; i++)
	{
		printf("%d,", dims[i]);
	}
	printf("\n");

    npy_intp *sp=PyArray_SHAPE(arr1);

    printf("array dimentsion: %ld\n",*sp);

    printf("Print array elements:\n");
    
	//PyArray_GETPTR1(arr1, 0);

	//__attribute__((unused)) npy_intp*  dims = PyArray_DIMS(arr);
	//npy_intp*  dims = PyArray_DIMS(arr1);
	char*      data0 = PyArray_DATA(arr1);
	npy_intp  *strides = PyArray_STRIDES(arr1);

	double d0 = *(double*)PyArray_GetPtr(arr1, (npy_intp[]){0, 0});
    for (int i=0; i < dims[0]; i++)
    {
		for (int j = 0; j < dims[1]; j++)
		{
			double d1 = *(double*)&data0[i*strides[0] + j*strides[1]];
			printf("%f,", d1);
		}
		printf("\n");


		//PyArray_GetPtr(arr1, )
//        printf("%lf(%x) ",*((npy_double*)PyArray_GETPTR1(arr1,i)), PyArray_GETPTR1(arr1, i));
		//PyArray_GetPT
    }
	printf("------------------\n");
	//NPY_LONGDOUBLE_FMT

	npy_float64  *myarray = (npy_float64*)PyArray_DATA(arg1);
	PyArrayObject_fields *ptr = PyArray_DATA(arg1);

	
	//pydim.nd
	npy_int s0 = PyArray_STRIDES(arg1)[0];
	npy_int s1 = PyArray_STRIDES(arg1)[1];
	printf("strides :%d, %d", s0, s1);
	printf("---------------\n");
	npy_float64 kk;

    

    if (arr1 == NULL)
        return NULL;

    nd = PyArray_NDIM(arr1);   //number of dimensions

    Py_DECREF(arr1);

    return PyInt_FromLong(nd);
}


static PyMethodDef hello_methods[] = {
        {
                "hello_python", hello_world_c, METH_VARARGS,
                "Print 'hello xxx'"
        },
        {
                "hello_numpy", hello_numpy_c, METH_VARARGS,
                "numpy function tester",
        },
        {NULL, NULL, 0, NULL}
};


static struct PyModuleDef hello_definition = {
        PyModuleDef_HEAD_INIT,
        "hello",
        "A Python module that prints 'hello world' from C code.",
        -1,
        hello_methods
};


PyMODINIT_FUNC PyInit_hello(void) {
    Py_Initialize();
    import_array();
    return PyModule_Create(&hello_definition);
}