### FP theory module

This folder contains all the work (except CMakeLists.txt) on 
floating point integration to boolector. 

Be sure that you have done everything to required for usual boolector
installation before trying to build some experimental stuff from here.

As it is work in progress it would not compile without some new dependecies.

To get them one must go to deps folder and run:
```bash
> pwd
<path_to_project_dir>/boolector/deps
> git clone https://github.com/martin-cs/symfpu.git
> git clone https://github.com/amrayn/easyloggingpp.git
```

This should be enough to then run the test code:
```bash
> pwd
<path_to_project_dir>/boolector/build
> cmake .. && make test_symb 
> ./bin/examples/test_symb
```
Expected output is huge log from all the operations performed during test and the error in the end.

