On Win11, VS2022, Python 3.12.
Running the project will exit with "access violation":

```powershell
git submodule update --init
cd extern/pybind11
git checkout v2.10
cd ../..
cmake -S. -Bbuild
cmake --build build --config Release --target run_py
```
