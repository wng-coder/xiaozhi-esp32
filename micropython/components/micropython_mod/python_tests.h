#ifndef PYTHON_TESTS_H
#define PYTHON_TESTS_H

#ifdef __cplusplus
extern "C" {
#endif

// Run comprehensive Python-like tests on the board wrapper
void run_python_like_tests(void* board);

#ifdef __cplusplus
}
#endif

#endif // PYTHON_TESTS_H