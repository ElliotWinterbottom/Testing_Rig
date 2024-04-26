**Testing_Rig**
This repository is for the code used to test two tactile illusions as well as the results from a round of said testing. The two illusions both use vibrations and are
1) phantom senstaion
2) apprent tactile motion
This was done for the 3rd year project of Elliot Winterbottom at the University of Manchester in 2023 to 2024

Vibrotactile illusions
Phantom sensation uses two vibrational stimuli of constant amplitude in close proximity on the skin to create what appears to be a single vibration somewhere inbetween. 
Apparent tactile motion uses a delay (called stimulus onset asynchrony or SOA) of the activation of two motors to create a moving or "brushing" stimulus between the motors. More information about said illusions can be found here:
https://www.researchgate.net/publication/221518352_Tactile_Brush_Drawing_on_skin_with_a_tactile_grid_display/figures?lo=1
This paper should also explain any terms or equations used in the code although it should be kept in mind that the attempted position of the phantom sensation is central between the the motors.

Testing 
The aim of the test which this code supports was to determine whether the harware used could be made to induce the illusions described above. The hardware for used this project was:
1) 1 X an arduino nano (ATMEGA) - https://store.arduino.cc/products/arduino-nano
2) 1 X TCA9548A  - https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/arduino-wiring-and-test
3) 2 X Adafruit DRV2605L Haptic Controller Breakout - https://learn.adafruit.com/adafruit-drv2605-haptic-controller-breakout/overview
4) 2 X ERM vibration motors - https://catalogue.precisionmicrodrives.com/product/310-122-10mm-vibration-motor-3mm-type

Once wired this harware could then be attached directly to a user with sports tape as shown below 
![image](https://github.com/ElliotWinterbottom/Testing_Rig/assets/149702598/b9c92607-f741-4373-8158-36c10bb8638d)

The results for this test found that this hardware is incabable of producing such illusions so be carefull coppying this setup directly 
The test script is also included for ease of reporducability although double checking with your institutions ethical guidelines for human testing is highly recommended as this test was checked before commencing.
https://www.manchester.ac.uk/research/environment/governance/ethics/approval/

Code
the code itself was written for arduino platforms using the visual micro tool for visual studio both of which which can be downloaded here:
https://visualstudio.microsoft.com/downloads/
https://www.visualmicro.com/
Once dowloaded the Git repository can be cloned and the project opened as shown here:
https://learn.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2022

Alternatively you can run the code through the arduino IDE available here:
https://www.arduino.cc/en/software
by going to 
https://github.com/ElliotWinterbottom/Testing_Rig/tree/a30117e9c307c6c9e27cfeb85e567795b839c437
and downloading only the .ino file.
However several libaries will be missing, more specifically:
 "Wire.h"
 <Adafruit_DRV2605.h>
which will need to be dowloaded using the library manager tool:
https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/

Results and script
Test results are both available here as excel and word file respectively. A guide to using and opening these files can be found here:
https://www.customguide.com/word/open-word-documents
https://www.customguide.com/excel/open-excel-workbook

the results sheet also holds calculations used for a chi-squared goodness of fit test comparing results to an estimated binomial distribution. more info about such a test can be found here:
https://social-policy.org.uk/wordpress/wp-content/uploads/2015/02/workbook-4-01.2.15-BEST-FOR-SPA.pdf

Best of luck to those attempting to render these illusions using off the shelf hardware and woe betide those who stray from the reccomendations of D. Alles.

