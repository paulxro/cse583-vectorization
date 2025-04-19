# Running Project

Use the **bin** directory to run tests.

Ensure that all scripts are executable: `chmod +x ./bin/*.sh`

- `pass.sh [test_name]`: include the test name without a filetype (e.g. `test.c` --> `test`)

> Runs the pass on `tests/[test_name].c`, outputs IR to `tests/llvm/[test_name].ll`

- `viz.sh [test_name]`: include the test name without a filetype (e.g. `test.c` --> `test`)

> Runs the visualization script on `tests/[test_name].c`, outputs to `tests/viz/[test_name].pdf`
