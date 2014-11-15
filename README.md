# WhatsApp
* For a trip to understand what is application and how to develop a good application, 
also know how to build a good platform for application.
* Entry platform according to AUTOSAR 4.0

### OS
* For OS, I don't know how to simulate a perfect OS with all the features should be supported by AUTOSAR OS. 
So I decided to just implement the OSEK BCC1.
* And recently, I am also thinking that whether is there a need for an OS like ucOS or FreeRTOS. As we know,
these Real-Time and Multiply-Task operating system takes a lot of resources, especially for automotive industry,
16 bit CPU is still in use, RAM resource is very limited.
* OSEK BCC1 is good, it is fast and use very little resource.
#### kernel1 & kernel2
* Yes, OSEK BCC1 is kernel1; OSEK ECC2 is kernel2.
    By a lot of thinking, I still think that for a lot of complex applications, kernel1 will not fulfill
the requirement, so kernel2 is absolutely needed.
    But that my ability is not enough to run the kernel2 by simulation method on Qt5.3, so I dropped it. 
But it is OK to run it on a lot of ECUs, such as 9s12 and ARM CM.
    In fact, kernel2 is TOPPERS OSEK.
    For simulation, kernel2 is a shit, use kernel1 for simulation only. For kernel2, it needs a real platform 
to run it.
### Communication
* For applications on Automotive Industries, communication is the most important thing, which is the most 
important part of VFB(Virtual Function Bus).
    Now I know how it works, I want to build all of it by myself, but I found out that it it such a boring
things, I want to quite, there is ArcCore3.1 which is source open, it is usable, but I think that ArcCore
is not good,period.
    So this part of WhatsApp may be a long time work, put it away temporarily.
    ......
    Time is money, my ability is not strong, and I am also very lazy, I will implement a small rough one.
And then make it better if I want to do it.    
### TOOLS
* Any one else who want to use AUTOSAR platform, he must use the tool to do configuration for the application,
such as BSW things and RTE.
* Yes, before I have builded a good tool to configure the BSWs for ArcCore, but never RTE.
* So, maybe I need to know more what is RTE, how to define it. So I decided to learn "Methodology and Templates"
to get more information.
    GOOD FOR ME.




