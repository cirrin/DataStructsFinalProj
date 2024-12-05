Group 54 Data Structures Final Project

Repository made public 12/4/2024.

INSTRUCTIONS TO RUN CODE

1. If using CLion, make sure to create CMakeLists.txt.
2. Run the code, and make sure the executable can read in the file. If the file was not able to be read, make sure the executable for the program is in the same directory as the .csv file (which should be named "charts(fixed).csv" or something similar)

That should be all that's needed to properly run the code. However, some notes:

- Some songs are in foreign languages and use non-english characters. If copying directly from the charts.csv file, searching by those names will not work. Unfortunately we were not able to find an easy solution to this issue. However, you can get around this by searching for said song's ID, then copying the name outputted from there.

Example: You search for the song named _"OUTRO. 신곡(神曲) (Divina Commedia)"_, and it does not work. You go into charts(fixed).csv, and find the ID (_"6rRtiujgKHYesXiAEVLjMm"_). You run the code again and go through the menu options, search by ID, and it outputs the name: _"OUTRO. ∞ïáΩ│í(τÑ₧µ¢▓) (Divina Commedia)"_. You copy this, and go through the menu once again, selecting "Search by ID" option. You paste this in, and it will find the song.


