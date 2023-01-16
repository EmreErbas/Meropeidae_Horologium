# Nixie-LOG-January2023

<pre>

<b>01-Jun-2023</b>  Started to write documents about the project

<b>02-Jun-2023</b>  Started to take technical notes. Created a file system

<b>12-Jun-2023</b>  NixiePanel PCB is arrived. ESP32-S3-Mini is arrived

<b>15-Jun-2023</b>  ESP32-S3-Mini is not really easy to use :/ I think there are some missing and/or buggy codes on the
             bootloader feature in the current library. Although I could download some simple codes, I cannot 
             download them again without entering the factory-boot-mode

<b>15-Jun-2023</b>  I saw the first light today. The PCB is working like a charm. I didn't have to change anything on the 
             hardware. But probably using two individual I2C will be a bit painful. Maybe it is wise to convert 
             the circuit for a single bus.
             Also, I need to focus on the speed of communication. I am sending all the pixels from the beginning 
             to change a single pixel. Speed is quite essential in that case. But of course, I need to find another 
             way to scan the screen.

</pre>


