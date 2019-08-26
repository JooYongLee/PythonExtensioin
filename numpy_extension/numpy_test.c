#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <stdio.h>
// Forward function declaration.
static PyObject *evolve(PyObject *self, PyObject *args); 

// Boilerplate: method list.
static PyMethodDef methods[] = {
  { "evolve", evolve, METH_VARARGS, "Doc string."},
  { NULL, NULL, 0, NULL } /* Sentinel */
};

// Boilerplate: Module initialization.
//PyMODINIT_FUNC initsimple1(void) {
//  (void) Py_InitModule("numpy_test", methods);
//  import_array();
//}

static struct PyModuleDef hello_definition = {
	PyModuleDef_HEAD_INIT,
	"numpy_test",
	"A Python module that prints 'hello world' from C code.",
	-1,
	methods
};

PyMODINIT_FUNC PyInit_numpy_test(void) {
	Py_Initialize();
	import_array();
	return PyModule_Create(&hello_definition);
}
/*****************************************************************************
 * Array access macros.                                                      *
 *****************************************************************************/
#define m(x0) (*(npy_float64*)((PyArray_DATA(py_m) +                \
                                (x0) * PyArray_STRIDES(py_m)[0])))
#define m_shape(i) (py_m->dimensions[(i)])

#define r(x0, x1) (*(npy_float64*)((PyArray_DATA(py_r) +                \
                                    (x0) * PyArray_STRIDES(py_r)[0] +   \
                                    (x1) * PyArray_STRIDES(py_r)[1])))
#define r_shape(i) (py_r->dimensions[(i)])

#define v(py_v, x0, x1) (*(npy_float64*)((PyArray_DATA(py_v) +                \
                                    (x0) * PyArray_STRIDES(py_v)[0] +   \
                                    (x1) * PyArray_STRIDES(py_v)[1])))
#define v_shape(i) (py_v->dimensions[(i)])

#define F(x0, x1) (*(npy_float64*)((PyArray_DATA(py_F) +              \
                                    (x0) * PyArray_STRIDES(py_F)[0] +   \
                                    (x1) * PyArray_STRIDES(py_F)[1])))
#define F_shape(i) (py_F->dimensions[(i)])


/*****************************************************************************
 * compute_F                                                                 *
 *****************************************************************************/
//static inline void compute_F(npy_int64 N,
//                             PyArrayObject *py_m,
//                             PyArrayObject *py_r,
//                             PyArrayObject *py_F) {
//  npy_int64 i, j;
//  npy_float64 sx, sy, Fx, Fy, s3, tmp;
//  
//  // Set all forces to zero. 
//  for(i = 0; i < N; ++i) {
//    F(i, 0) = F(i, 1) = 0;
//  }
//  
//  // Compute forces between pairs of bodies.
//  for(i = 0; i < N; ++i) {
//    for(j = i + 1; j < N; ++j) {
//      sx = r(j, 0) - r(i, 0);
//      sy = r(j, 1) - r(i, 1);
//
//      s3 = sqrt(sx*sx + sy*sy);
//      s3 *= s3 * s3;
//
//      tmp = m(i) * m(j) / s3;
//      Fx = tmp * sx;
//      Fy = tmp * sy;
//
//      F(i, 0) += Fx;
//      F(i, 1) += Fy;
//
//      F(j, 0) -= Fx;
//      F(j, 1) -= Fy;
//    }
//  }
//}

/*****************************************************************************
 * evolve                                                                    *
 *****************************************************************************/
static PyObject *evolve(PyObject *self, PyObject *args) {
  // Declare variables. 
  //npy_int64 N, threads, steps, step, i;
  npy_float64 dt;
  //PyArrayObject *py_m, *py_r, *py_v, *py_F;
  PyArrayObject *py_v;

  // Parse arguments. 
  //if (!PyArg_ParseTuple(args, "ldllO!O!O!O!",
  //                      &threads,
  //                      &dt,
  //                      &steps,
  //                      &N,
  //                      &PyArray_Type, &py_m,
  //                      &PyArray_Type, &py_r,
  //                      &PyArray_Type, &py_v,
  //                      &PyArray_Type, &py_F))
	  if (!PyArg_ParseTuple(args, "O!",
		  &PyArray_Type, &py_v
		  )) {
    return NULL;
  }

	npy_intp *dims = PyArray_DIMS(py_v);

	npy_int s0 = PyArray_STRIDES(py_v)[0];
	npy_int s1 = PyArray_STRIDES(py_v)[1];

	printf("%d X %d\n", dims[0], dims[1]);


	npy_float64  *myarray = (npy_float64*)PyArray_DATA(py_v);
  // Evolve the world.   
    
    
	for (int i = 0; i < dims[0]; ++i) {
		//double v1 = (double)(v(py_v, i, 0));
		//double v2 = (double)(v(py_v, i, 1));
		double v1 = (*(npy_float64*)((myarray + \
			(i)* s0 + \
			(0)* s1)));
		double v2 = (*(npy_float64*)((myarray + \
			(i)* s0 + \
			(1)* s1)));
		printf("%f, %f\n", v1, v2);
      //v(i, 0) += F(i, 0) * dt / m(i);
      //v(i, 1) += F(i, 1) * dt / m(i);
      //
      //r(i, 0) += v(i, 0) * dt;
      //r(i, 1) += v(i, 1) * dt;
    }
  

  Py_RETURN_NONE;
}