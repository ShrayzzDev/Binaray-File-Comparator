# Binary-File-Comparator
Compare 2 binary files to check if they're the same.

Input the path to 2 binary, and it will check every byte to see if they are the same. 
You can choose to make the software close is they're not the same
Either way, it's gonna save in the folder saves/ the offset, the data in the first file, 
and the data in the second ALL IN DECIMAL i don't how to write in hexa (im dumb)

Options : 
  - You can chose to else : - stop when it finds a difference
                            OR
                            - Don't stop until the end.
    In each cases, saves the differences in the "byte_difference" file (creates it at the root if it doesn't already exist)
    Asks you to continue without it if it can't open it (or create it)
  - You can chose to endian swap each file independantly, just the first one for example (or none, or both)
