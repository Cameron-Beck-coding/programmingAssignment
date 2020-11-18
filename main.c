#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
int whatToPrint(int numOfWrongGuesses);
int printer(char file[]);
char *wordGetter(int maxLength);
int main(void)
{
       char playAgain;
       char guess;
       int wrongGuesses = 0;
       int gotright = 0;
       int win = 0;
       int totalWins = 0;
       char allGuesses[250];
       int totalGuesses = 0;
       int totalLosses = 0;
       int maxWordLength = 0;
       printf("Enter a max word length, if you don't care, enter 0\n");
       scanf("%d", &maxWordLength);
       char *mysteryWord = wordGetter(maxWordLength);
       char notGuessed[(strlen(mysteryWord) + 1)];
       for (int i = 0; i < strlen(mysteryWord); i++)
       {
              notGuessed[i] = '_';
       }
       notGuessed[strlen(mysteryWord) + 1] = '\0';
       //ending the character array so it prints properly
       while (1)
       {
              gotright = 0;
              //prints hangman
              win = whatToPrint(wrongGuesses);
              if (win > 1)
              {
                     printf("letters guessed so far:");
                     if (totalGuesses >= 1)
                     {
                            for (int i = 0; i < totalGuesses; i++)
                            {
                                   putchar(allGuesses[i]);
                                   printf(" ");
                            }
                     }
                     printf("\n%s\n", notGuessed);
                     printf("Guess a letter!\n");
                     scanf("%s",&guess);
                     //all guesses gets set incorrectly due to new line, need to ask about this
                     allGuesses[totalGuesses] = guess;
                     totalGuesses++;
                     //determining if guess was correct
                     for (int i = 0; i < strlen(mysteryWord); i++)
                     {
                            if (mysteryWord[i] == guess)
                            {
                                   notGuessed[i] = guess;
                                   gotright++;
                            }
                     }
                     if (gotright == 0)
                     {
                            printf("Incorrect!\n");
                            wrongGuesses++;
                     }
                     else
                     {
                            printf("Correct!\n");
                            continue;
                     }
                     if (strcmp(mysteryWord, notGuessed) == 0)
                     {
                            printf("WOOOOO congrats!!]\n");
                            totalWins++;
                            printf("You've won a total of %d times, and lost %d"
                                   "times\n",
                                   totalWins, totalLosses);
                            printf("Want to play again?\n");
                            scanf("%s", &playAgain);
                            //we do this so we can only check for upper inputs
                            toupper(playAgain);
                            if (playAgain == 'Y')
                            {
                                   //getting new random word, and setting underlines again
                                   mysteryWord = wordGetter(maxWordLength);
                                   for (int i = 0; i < strlen(mysteryWord); i++)
                                   {
                                          notGuessed[i] = '_';
                                   }
                                   notGuessed[strlen(mysteryWord) + 1] = '\0';
                                   continue;
                            }
                            else
                            {
                                   printf("Goodbye!\n");
                                   return 0;
                            }
                     }
              }
              else
              {
                     printf("You got it wrong! The word was %s\n", mysteryWord);
                     printf("You've won a total of %d times, and lost %d"
                            "times\n",
                            totalWins, totalLosses);
                     printf("Want to play again?\n");
                     scanf("%s\n", &playAgain);
                     if (playAgain == 'Y' || playAgain == 'Y')
                     {
                            //getting new random word, and setting underlines again
                            mysteryWord = wordGetter(maxWordLength);
                            for (int i = 0; i < strlen(mysteryWord); i++)
                            {
                                   notGuessed[i] = '_';
                            }
                            notGuessed[strlen(mysteryWord) + 1] = '\0';
                            continue;
                     }
                     else
                     {
                            printf("Goodbye!\n");
                            return 0;
                     }
              }
       }
       return 0;
}
//conditionally prints the hangman based on how many guesses are wrong
int whatToPrint(int numOfWrongGuesses)
{
       if (numOfWrongGuesses == 1)
       {
              printer("head.txt");
       }
       else
       {
              //printing the body based on wrong guesses
              if (numOfWrongGuesses >= 2)
              {
                     if (numOfWrongGuesses >= 3)
                     {
                            printer("arm2.txt");
                     }
                     else
                     {
                            printer("arm1.txt");
                     }
              }
              if (numOfWrongGuesses >= 4)
              {
                     if (numOfWrongGuesses >= 5)
                     {
                            printer("leg2.txt");
                            printf("You lose!");
                            return -1;
                     }
                     else
                     {
                            printer("leg1.txt");
                     }
              }
              printf("\n");
       }
       //no wrong guesses
       if (numOfWrongGuesses == 0)
       {
              printer("base.txt");
       }
       return 2;
}
//prints specified file
int printer(char file[])
{
       FILE *fileToPrint;
       char line;
       fileToPrint = fopen(file, "r");
       line = fgetc(fileToPrint);
       while (line != EOF)
       {
              printf("%c", line);
              line = fgetc(fileToPrint);
       }
       printf("\n");
}
//gets a random word from the words.txt file
char *wordGetter(int maxLength)
{
       //making sure that the seed is random each time a new word is called
       srand(time(0));
       FILE *inputFile;
       int count = 0;
       char word[256];
       //temporary variable so we can count the number of lines
       char temp[256];
       int wordlength = 0;
       inputFile = fopen("words.txt", "r");

       //finding the number of words in the file
       while (fscanf(inputFile, "%s", temp) > 0)
       {
              count++;
       }
       rewind(inputFile);
       //putting all the words into an array, so we can pull them out later
       //we use 45 here because it is the longest word in the english dict
       char words[count][45];
       for (int i = 0; i < count; i++)
       {
              fscanf(inputFile, "%s", words[i]);
       }
       fclose(inputFile);
       //getting random word, and only returning if it matches criteria
       while (1)
       {
              int wordIndex = rand() % count;
              char *mysteryWord = words[wordIndex];
              if (strlen(mysteryWord) <= wordlength && wordlength > 0)
              {
                     return mysteryWord;
              }
              else if (wordlength == 0)
              {
                     return mysteryWord;
              }
       }
}
//setting the underlines, made it as a seperate function for modulization
