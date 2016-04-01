# CamelUpPredictor
Predictor library for the Camel Up game.

C/C++ library written to compile with Clang on OS X via make

various make options are enabled:
make software    - compiles the library
make alltests   - compiles the unit test code
make test       - compiles and runs the unit test code
make all        - compiles the library and runs the unit test code
make docs       - generates Doxygen documentation for the code in: build/docs
make clean      - cleans up all folders above

Additional flags
COV=Y           - executes the unit tests with LCOV. Test output will be written to build/cov.info
CCACHE=Y        - enables CCACHE for faster compilation time.
TEST_FILTER=*   - allows filtering of test titles using * as a wildcard
