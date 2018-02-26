#include <Python.h>
#include <pthread.h>


static void assert_cond(int ok)
{
    if (!ok) {
        abort();
    }
}


static PyObject *run_test(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyThreadState *save = NULL;
    PyGILState_STATE gilsave;

    assert_cond(PyErr_Occurred() == NULL);

    save = PyEval_SaveThread();

    gilsave = PyGILState_Ensure();

    assert_cond(PyErr_Occurred() == NULL);
    PyErr_SetString(PyExc_RuntimeError, "XXX");
    assert_cond(PyErr_Occurred() != NULL);

    PyGILState_Release(gilsave);

    sleep(1);

    PyEval_RestoreThread(save);

    assert_cond(PyErr_Occurred() != NULL);

    return NULL;
}


static PyMethodDef methods[] = {
    {"run_test", (PyCFunction)run_test, METH_VARARGS | METH_KEYWORDS, ""},
    {NULL, NULL}
};


#if PY_VERSION_HEX >= 0x03000000

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "testmodule",
    NULL,
    -1,
    methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyObject *PyInit_testmodule(void)
{
    return PyModule_Create(&moduledef);
}

#else

PyMODINIT_FUNC inittestmodule(void)
{
    Py_InitModule("testmodule", methods);
}

#endif
