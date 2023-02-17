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
char testArray[] = {'1', 'c', 'c', 'c', 'A', '4', '4', '4', '4', '6', '6', '6', '6', 'G', '5', 'i', 'j', '7', '7', '7'};
char markChar = '*';
char repeatChar;
char currentVal;
char nextVal;

vector<char> compressedArray;

int count;

int uiaIndex; // Uncompressed Input Array Index

bool run         = true;
bool repeatFound = false;

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

  cout << "\nUncompressed Array : \t";
  
  for(int i = 0; i < sizeof(testArray); i ++)
  {
    cout << testArray[i];
  }

  while(run)
  {
    if(uiaIndex < sizeof(testArray))
    {
      currentVal = testArray[uiaIndex];
      nextVal = testArray[uiaIndex + 1];

      if(currentVal == nextVal && (currentVal != repeatChar)) // Next val is the same
      { 
        count = 0;
        compressedArray.push_back(markChar);
        repeatChar  = testArray[uiaIndex];
        repeatFound = true;
      }

      if(repeatFound && (currentVal == repeatChar)) // Check to see if the current char is the same as the repeat char
      {
        count ++;
      }      

      else // If the current value isnt a repeat char then reset count and the repeat flag
      {
        compressedArray.push_back(testArray[uiaIndex]);
        // repeatFound = false;
      }

      if(repeatFound && (nextVal != repeatChar))
      {
        repeatFound = false;

        compressedArray.push_back(count + ascii);
        compressedArray.push_back(testArray[uiaIndex]);
      }

      uiaIndex ++;
    }

    else
    {

      run = false;
      uiaIndex = 0;
    }
  }

  cout << endl << "Compressed Array: \t \t";

  for(int i = 0; i < compressedArray.size(); i ++)
  {
    cout << compressedArray[i];
  }

  cout << endl;
}