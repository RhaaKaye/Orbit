////////////////////////////////////////////////////////////////////////
//  Matthew Kavanagh 
// 
//  Orbit 
//  Run Length Encoding Tester
//  *********
//  <Mark> <Number> <Value>
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
//  #     #                                                    
//  #     #   ##   #####  #   ##   #####  #      ######  ####  
//  #     #  #  #  #    # #  #  #  #    # #      #      #      
//  #     # #    # #    # # #    # #####  #      #####   ####  
//   #   #  ###### #####  # ###### #    # #      #           # 
//    # #   #    # #   #  # #    # #    # #      #      #    # 
//     #    #    # #    # # #    # #####  ###### ######  #### 
//
////////////////////////////////////////////////////////////////////////
char compressedArray[] = {'1', '3','*' ,'4', 'c', 'A', '6', 'G', '5', 'i', 'j', '*', '3', '7'};

vector<char> uncompressedArray; // Array with unspecified size to hold the uncompressed array

char markChar = '*';

int value = 0;

int compressedArrayIndex;
int unCompressedArrayIndex;

char repeatChar;

bool run = true;

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
int main() // Uncompression 
{ 
  cout << "\nCompressed Array : \t \t";
  
  for(int i = 0; i < sizeof(compressedArray); i ++)
  {
    cout << compressedArray[i];
  }
  cout << endl;

  while(run)
  {
    if(compressedArrayIndex < sizeof(compressedArray))
    {
      if(compressedArray[compressedArrayIndex] == markChar)
      {
        char repeatChar = compressedArray[compressedArrayIndex + 2]; // Save the repeating value

        for(int i = 0; i < compressedArray[compressedArrayIndex + 1] - ascii; i ++) // Add the repeating values to the output array
        {
          uncompressedArray.push_back(repeatChar);
        }

        unCompressedArrayIndex = unCompressedArrayIndex + (compressedArray[compressedArrayIndex + 1] - ascii); 

        compressedArrayIndex = compressedArrayIndex + 3; // Increment "Input Array" index to the next unrepeated value (the 3 is from the MCV)

        value = compressedArrayIndex;
      }

      else
      {
        uncompressedArray.push_back(compressedArray[compressedArrayIndex]);
        value ++;
        unCompressedArrayIndex ++;
        compressedArrayIndex ++;
      }
    }

    else
    {
      value = 0;
      run = false;
    }
  }

  cout << "Uncompressed Array: \t";

  for(int i = 0; i < uncompressedArray.size(); i ++)
  {
    cout << uncompressedArray[i];
  }

  cout << "\n" << endl;
}