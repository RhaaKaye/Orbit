////////////////////////////////////////////////////////////////////////
//  Matthew Kavanagh 
// 
//  Orbit 
//  Run Length Encoding Tester
//  *********
////////////////////////////////////////////////////////////////////////
//
//  ###                                                  
//   #  #    #  ####  #      #    # #####  ######  ####  
//   #  ##   # #    # #      #    # #    # #      #      
//   #  # #  # #      #      #    # #    # #####   ####  
//   #  #  # # #      #      #    # #    # #           # 
//   #  #   ## #    # #      #    # #    # #      #    # 
//  ### #    #  ####  ######  ####  #####  ######  ####  
//
////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

#define ascii 48

////////////////////////////////////////////////////////////////////////
//
// ######  
// #     # #####   ####  #####  ####  ##### #   # #####  ######  ####
// #     # #    # #    #   #   #    #   #    # #  #    # #      #
// ######  #    # #    #   #   #    #   #     #   #    # #####   ####
// #       #####  #    #   #   #    #   #     #   #####  #           #
// #       #   #  #    #   #   #    #   #     #   #      #      #    #
// #       #    #  ####    #    ####    #     #   #      ######  ####
//
////////////////////////////////////////////////////////////////////////


// #define repeats 

////////////////////////////////////////////////////////////////////////
//
//  #     #                                                    
//  #     #   ##   #####  #   ##   #####  #      ######  ####  
//  #     #  #  #  #    # #  #  #  #    # #      #      #      
//  #     # #    # #    # # #    # #####  #      #####   ####  
//   #   #  ###### #####  # ###### #    # #      #           # 
//    # #   #    # #   #  # #    # #    # #      #      #    # 
//     #    #    # #    # # #    # #####  ###### ######  #### 
//
////////////////////////////////////////////////////////////////////////
int inputArrayLength;
char inputArray[] = {'1', '3', '9', 'c', 'A', '6', 'G', '5', 'i', 'j', '*', '3', '7'};
char uncompressedArray;

char testArray[] = {'1', 'c', 'c', 'c', 'A', '6', 'G', '5', 'i', 'j', '7', '7', '7'};

vector<char> outputArray; // Array with unspecified size to hold the uncompressed array

vector<char> testOutputArray; // Array to hold test compressed data

vector<char> compressedArray;

// char outputArray[1] = {'A'};

char markChar = '*';

int value = 0;

int inputArrayindex;
int outputArrayindex;

int uiaIndex; // Uncompressed Input Array Index
int coaIndex; // Compressed Output Array Index

bool run = true;

char currentVal;
char lastVal;
char nextVal;

int count = 0;
int countStart = 0;

bool repeatFound = false;

char repeatChar;

// <Mark> <Number> <Value>

///////////////////////////////////////////////////////////////////////
//
//  #     #                    ######                                            
//  ##   ##   ##   # #    #    #     # #####   ####   ####  #####    ##   #    # 
//  # # # #  #  #  # ##   #    #     # #    # #    # #    # #    #  #  #  ##  ## 
//  #  #  # #    # # # #  #    ######  #    # #    # #      #    # #    # # ## # 
//  #     # ###### # #  # #    #       #####  #    # #  ### #####  ###### #    # 
//  #     # #    # # #   ##    #       #   #  #    # #    # #   #  #    # #    # 
//  #     # #    # # #    #    #       #    #  ####   ####  #    # #    # #    # 
//
//////////////////////////////////////////////////////////////////////
int main()
{  
  // Look at the current value and the next value
  // If they are the same then save the repeat char
  // Save the mark char to the output array

  // If a repeat has been found, look at the current value
  // if its the same as the reeat char then ad one to the count  

  cout << "Initial Array Length: " << sizeof(testArray) << "\n" << endl;

  cout << "Uncompressed Input Array : \t \t";
  for(int i = 0; i < sizeof(testArray); i ++)
  {
    cout << testArray[i];
  }

  cout << endl;

  while(run)
  {
    if(uiaIndex < sizeof(testArray))
    {
      currentVal = testArray[uiaIndex];
      nextVal = testArray[uiaIndex + 1];

      cout << "Index: "          << uiaIndex;
      cout << "\t Current Val: " << currentVal;
      cout << "\t Next Val: "    << nextVal;   

      if(currentVal == nextVal && (currentVal != repeatChar)) // Next val is the same
      {
        cout << "\t Start of repeating chars";
        compressedArray.push_back('*');

        repeatChar  = testArray[uiaIndex];
        repeatFound = true;
      }

      if(repeatFound && (currentVal == repeatChar)) // Check to see if the current char is the same as the repeat char
      {
        count ++;
        cout << "\t Count Added" << count;
      }      

      else // If the current value isnt a repeat char then reset count and the repeat flag
      {
        compressedArray.push_back(testArray[uiaIndex]);
        repeatFound = false;
        count = 0;
        // cout << endl;
      }

      if(repeatFound && (nextVal != repeatChar))
      {
        cout << "\t Final Repeating Char";

        repeatFound = false;

        compressedArray.push_back(count + ascii);
        compressedArray.push_back(testArray[uiaIndex]);
      }


      cout << endl;
      // cout << "\t" << count << endl;

      uiaIndex ++;
    }

    else
    {

      run = false;
      uiaIndex = 0;
    }
  }

  cout << endl << "Compressed Array: \t";
  // cout << "\n\n\n\n\n" << endl;


  for(int i = 0; i < compressedArray.size(); i ++)
  {
    cout << compressedArray[i];
  }

  cout << "\n" << endl;
}



// else if(currentVal == repeatChar) // Current val is a repeat
      // {
      //   count ++;
      // }

      // if(repeatFound && (currentVal == repeatChar) && (nextVal != repeatChar)) // Current val is a repeat
      // {
      //   // compressedArray.push_back(count);
      //   // cout << "Here" << endl;
      // }

      // else if(repeatFound)
      // {
      //   compressedArray.push_back(repeatChar);
      //   // repeatFound = false;
      // }


      // else if(nextVal != repeatChar)
      // {
      //   for(int i = 0; i < count; i ++)
      //   {
      //     compressedArray.push_back(repeatChar);
      //   }
      // }

      // else if(nextVal == repeatChar)
      // {
      //   cout << "Repeat" << endl;
      //   count ++;
      //   uiaIndex ++;
      // }




// int main() // Uncompression 
// {  
//   cout << "Initial Array Length: " << sizeof(inputArray) << "\n" << endl;

//   cout << "Compressed Input Array : \t \t";
//   for(int i = 0; i < sizeof(inputArray); i ++)
//   {
//     cout << inputArray[i];
//   }
//   cout << endl;

//   inputArrayLength = sizeof(inputArray);

//   while(run)
//   {
//     if(inputArrayindex < inputArrayLength)
//     {
//       if(inputArray[inputArrayindex] == markChar)
//       {
//         char repeatChar = inputArray[inputArrayindex + 2]; // Save the repeating value

//         for(int i = 0; i < inputArray[inputArrayindex + 1] - ascii; i ++) // Add the repeating values to the output array
//         {
//           // cout << repeatChar;
//           outputArray.push_back(repeatChar);
//         }

//         outputArrayindex = outputArrayindex + (inputArray[inputArrayindex + 1] - ascii); 

//         inputArrayindex = inputArrayindex + 3; // Increment "Input Array" index to the next unrepeated value

//         value = inputArrayindex;
//       }

//       else
//       {
//         outputArray.push_back(inputArray[inputArrayindex]);
//         value ++;
//         outputArrayindex ++;
//         inputArrayindex ++;
//       }
//     }

//     else
//     {
//       value = 0;
//       run = false;
//     }
//   }

//   // cout << outputArray.size();
//   cout << "Uncompressed Output Array: \t";

//   for(int i = 0; i < outputArray.size(); i ++)
//   {
//     cout << outputArray[i];
//   }

//   cout << "\n" << endl;
// }