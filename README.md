# Cryptanalysis
This repository aims to be a directory of basic stuff used in cryptanalysis.

## freq_anaysis.c
* A first attempt of a frequency analysis tool.
* It does not detect bigrams nor trigrams that helps the cryptanalysis. Therefore, this tool should be efficient only if the input text is long enough and if the letter distribution is similar to the input language reference.
* Implented for the following languages:
  * English.
  * French: to be done based on a Wikipédia article (https://fr.wikipedia.org/wiki/Fr%C3%A9quence_d'apparition_des_lettres_en_fran%C3%A7ais). I need to verify if all characters do have ASCII codes.
