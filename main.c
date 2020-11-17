#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
int whatToPrint(int numOfWrongGuesses);
int printer(char file[]);
int main(void)
{
       FILE *inputFile;
       int count = 0;
       char word[256];
       char playAgain;
       char guess;
       int wrongGuesses = 0;
       int gotright = 0;
       int win = 0;
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
       //getting random word
       int wordIndex = rand() % count;
       char *mysteryWord = words[wordIndex];
       char test[strlen(mysteryWord)];
       //initializing test to the length of msyteryword
       for (int i = 0; i < strlen(mysteryWord); i++)
       {
              test[i] = '_';
       }

       while (strcmp(mysteryWord, test))
       {
              gotright = 0;
              //prints hangman
              win = whatToPrint(wrongGuesses);
              if (win > 1)
              {
                     printf("%s\n", &test);
                     printf("Guess a letter!\n");
                     guess = getchar();
                     //to make sure the loop dosent run twice for each input
                     if (guess == '\n')
                     {
                            continue;
                     }
                     //determining if guess was correct
                     for (int i = 0; i < strlen(mysteryWord); i++)
                     {
                            if (mysteryWord[i] == guess)
                            {
                                   test[i] = guess;
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
                     }
              }
              //case for if they won
              else
              {
                     printf("Want to play again?");
                     scanf("%s", &playAgain);
                     //we do this so we can only check for upper inputs
                     toupper(playAgain);
                     if (playAgain == 'Y')
                     {
                            setWord();
                     }
                     else
                     {
                            return 0;
                     }
              }
       }
       return 0;
}
//conditionally prints the hangman based on how many guesses are wrong
int whatToPrint(int numOfWrongGuesses)
{
       if (numOfWrongGuesses >= 1)
       {
              printer("head.txt");
              //printing the body
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
                            return 1;
                     }
                     else
                     {
                            printer("leg1.txt");
                     }
              }
              printf("\n");
       }
       else
       {
              printer("base.txt");
       }
       return 2;
}
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