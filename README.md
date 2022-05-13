Used together, bash scripts will generate new sentences from input text using markov chain based predictive text analysis.

markov-words.sh generates a list of all four word sequences from input text:
$ ./markov-words.sh < file.txt > file_output.txt
$ tail -n 4 file_output.txt

markov-sentences accepts the name of a words file (file_output), and the target output
length, as command line arguments and write output to the terminal, like so:
$ ./markov-sentence.sh alice-words.txt 15

Shuffle program must be compiled and ran if shuf is not present:
$ gcc -o shuffle shuffle.c
$ ./shuffle
