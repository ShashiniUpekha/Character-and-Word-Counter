# Character-and-Word-Counter

## Introduction
One of the most important features of any written language is the occurrence of particular characters or words in general. For example, in the English language, all 26 characters are not used in
the same frequency. Generally, characters like e,a,t more frequently appear in text. These kinds of
information can be used in different applications such as Machine Learning, OCR, Cryptography,
etc. The same applies for words. Prepositions and articles like the, a, and, in are more frequently
used than other words. In project 2, you are supposed to observe this characteristic in the English
language using a program. A file or multiple files containing English text will be sent to the program, and the program should give an output (word or character frequencies) as a horizontal bar
chart printed on the terminal

## Control arguments for the program
File name/ File Names
The program should be able to accept any number of file names in any order. File names will not
start with ‘-’. eg: -file.txt

### Number of rows in the chart
The argument specifies the number of rows in the bar chart. It should be given as -l 10 where 10 is
the limit. It can be any positive integer. A number should always follow the -l argument. The pair
can be in any place of the arguments list.

## Scaled option
When –scaled argument is given, the first row of the graph should fully occupy the max print width.
Any other row should scale to be matched with first row scale factor.

## Word/Character toggle
The program can analyse two modes of frequencies, characters and words. If the output should be
given as words, the -w should be given whereas -c argument will give character frequency output.

## Default options
The program must take at least one file name to work. All other arguments are optional. If not
given, the program will work as non-scaled, will output frequencies for words and limit the output
rows to 10
