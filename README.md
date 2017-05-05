## introduction
deal with signal in one thread

## how to build 

 1.run the scripts **lib_update_posix.sh** in **tools dir,**automatically install depended-debs  
 2.run the scripts **build_without_libs_update.sh** in **tools dir,**build the project
 3.run the scripts **collect_profile_pdf.sh**  in **tools dir, **collet profile message

## Usage
```
 refer to https://github.com/echopairs/how-to-deal-with-signal-in-Multi-threading/blob/master/examples/signal_example.cpp
```
**tips:**

    we need build BaseServiceProcess object and call installSignalHandle at the begin of program before create thread
