# Reactor-Simulator
## Compilation instructions
Boost libraries must be used to compile code.

## Instrucitons
### NuclearReactior.exe
* Note: This program is in its early stages. If it crashes or closes automatically unexpectedly you have done something wrong
 * Known issues:
  * If unidentified contents were added (including nothing) the program will crash immediately.
  * If a save is corrupt or from a diffrent version the program may crash immediately.
* Note: Input type limits: 
 * INTIGER: Only numaric numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}. Any spaces ' ', decmals '.' are not allowed. Max: 2147483647. Min: -2147483648
  * WARNING: For LL (long long), ULL (unsigned long long), SHORT, USHORT (unsigned short) see c++ refrence documents
 * UNSIGNED INTIGER: Only numaric numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}. Any spaces ' ', decmals '.' are not allowed. Max: 4294967295. Min: 0
 * LINT: Only numaric numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}. Any spaces ' ', decmals '.' are not allowed. Max: 170141183460469231731687303715884105727. Min: −170141183460469231731687303715884105728.
 * ULINT: Only numaric numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}. Any spaces ' ', decmals '.' are not allowed. Max: 340282366920938463463374607431768211455. Min: 0.
  * WARNING: UINTBIT128 is not applied to the program. Use INTBIT128 when UINTBIT128 is recomended
 * BOOL: Only numaric numbers {1, 0}. Any spaces ' ', decmals '.' are not allowed. Max: 1. Min 0.
 * FLOAT: Floating point decmals allowed any spaces ' ' are not allowed. Max: 2,147,483,647 Min: -2,147,483,648
  * WARNING: FLOAT as well as other floating point types are dynamic and may not exibit normal or predictable rules. For example a float can show 2,147,483,646 but can round 2,147,483,646.1 down to 2,147,483,646 if there are not enough bits to store all the data given. For more information about this limit read about it in c++ documents.
 * DOUBLE: Floating point decmals allowed any spaces ' ' are not allowed. 
  * WARNING: See float warning.
 * LDOUBLE:Floating point decmals allowed any spaces ' ' are not allowed. 
  * WARNING: See float warning.
 * BF50: Floating point decmals allowed any spaces ' ' are not allowed. Max: 340282366920938463463374607431768211455. Min: -340282366920938463463374607431768211455
  * WARNING: See float warning. This goes out 50 digits. See Boost c++ documents about multipresision floating points.
 * BF100: Floating point decmals allowed any spaces ' ' are not allowed. Max: 340282366920938463463374607431768211455. Min: -340282366920938463463374607431768211455
  * WARNING: See float warning. This goes out 100 digits. See Boost c++ documents about multipresision floating points.
 * STRING: See c++ documents about strings.
* Note: File names
 * *.samp Sample file. 
  * Contains all the information about samples. 
  * This flie is formated as a text document and can be edited and is delimited by line ends.
 * *.srec Sample recording file.
  * Contains history of the current recording.
  * File is tab delimited and can be opened in Microsoft Excel

1. Open the program to start.
 * If the program has not created the file already it will create a file named "saves".
 * If at the end of the console window it says "press any key to continue..." do so.
2. SHORT enter your method of adding atoms of each element into the program corasponding to the number that is displayed.
 1. LINT enter the amount of grams.
  * WARNING: LINT is still limited by the number of ATOMS not grams.
 2. LINT enter the amount Mols.
  * WARNING: LINT is still limited by the number of ATOMS not Mols.
 3. LINT enter the amout of atoms.
 4. STRING enter the name of a save.
  * WARNING: Entering the incorrect name will cause the program to crash and close immediately.
  * NOTE: The program will display all information about the save before continueing.
 5. LINT enter the TOTAL amount of atoms. FLOAT enter the percentage of the total atoms.
  * WARNING: The program does not check if the total equals 100%
  * WARNING: The program will round the number of atoms following the rules of the .convert_to~ method in the boost libraries.
3. LINT enter the number of milliseconds the program will wait before updating the screen again.
 * NOTE: This is not a operations per second limit though keeping it higher will reduce CPU activity. Recomended setting 250
4. Multiple keys can be pressed once the simulation has started.
 * WARNING: This will read the state of the keys though the application is not focused.
 1. Esc: Will start the closing proccess of the simulation. The program wil ask you if you want to save the sample.
  * Entering 'y' would save the sample. Entering anyting else including capital y 'Y' would defalut to no.
  * There is no override warning. Save with caution.
 2. R: Will start a recording. 
  * WARNING: Starting a new recording will override any other recording.
  * WARNING: A recording can only be started and not stopped. Closing out of the aplicaion will stop the recording.