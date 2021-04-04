# CSCI-4727 Operating Systems
### 3. Memory Hierarchy Simulator

A console-based simulation for individual elements of the memory hierarchy—a page table (PT), a data cache (DC), and a data translation look-aside buffer (DTLB)—and how a data reference (virtual and/or physical) traverses the hierarchy.

Trace: a memory reference has the following format:\
accesstype:hexaddress>
    
accesstype is one of the two following characters:\
R – a read access\
W – a write access
    
hexaddress is the starting address of the reference (expressed as a hexadecimal number) with a reference size ranging from 8 bits to 32 bits. 

See trace.dat, real_tr.dat, and the example section for examples of memory references.\
Before processing the trace file, the memory hierarchy simulator will read a configuration file (named trace.config), located in the present working directory, that specifies the configuration for the individual modules. See trace.configand the example section for the required format and expected key:value pairs

### Example
![Result Header](https://i.ibb.co/jMZFM8q/Image1.jpg)

![Result Table](https://i.ibb.co/MpSGZkb/Image2.jpg)


