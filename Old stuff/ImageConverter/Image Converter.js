////////////////////////////////////////////////////////////////////////
//  Matthew Kavanagh 
// 
//  Orbit 
//  Image Converter.js
//  2018
//  *********
////////////////////////////////////////////////////////////////////////
var name = '';

////////////////////////////////////////////////////////////////////////
//
// ###                            
//  #  #    # #####  #    # ##### 
//  #  ##   # #    # #    #   #   
//  #  # #  # #    # #    #   #   
//  #  #  # # #####  #    #   #   
//  #  #   ## #      #    #   #   
// ### #    # #       ####    #  
//
////////////////////////////////////////////////////////////////////////
function readPic(input) // This function reads the input picture
{
  if(input.files && input.files[0])
  {
    var extName = input.files[0].name;
    name = extName.substring(0, extName.lastIndexOf('.'));
    var reader = new FileReader();
    reader.onload = function(e)
    {
      $('#inputImage').attr('src', e.target.result);  
      clearData();
    };
    reader.readAsDataURL(input.files[0]);
  }
}

function Convert() 
{
  /////////////
  // Startup //
  /////////////
  clearData();
  var counter = -1; // Such a cheat but it works

  var picsInRot = document.getElementById('numOfPics').value; // Number of pictures per rotation

  // Input Image
  var inputImage       = document.getElementById('inputImage'),               // Create image objects for manipulation (original and two outputs)
      inputImageWidth  = document.getElementById('inputImage').naturalWidth,  // Get original picture width
      inputImageHeight = document.getElementById('inputImage').naturalHeight; // Get original picture height

  var outputHeight = document.getElementById('numOfLEDs').value,                      // Set output picture dimensions (Scaled correctly) (defined by number of LEDs)
      outputWidth  = Math.ceil(inputImageWidth / (inputImageHeight / outputHeight));  // Divide input image width by scalar to get output width
      console.log(outputWidth);

  ////////////////////////////////////////////////////////////////////////
  // Calculation Image (image code is generated from)
  ////////////////////////////////////////////////////////////////////////
  var calculationImageCanvas = document.getElementById('calculationImageCanvas'),
      calculationImage       = calculationImageCanvas.getContext('2d');

  calculationImageCanvas.width  = outputHeight;  // Set widths of canvases 
  calculationImageCanvas.height = outputWidth;

  calculationImage.transform(0, 1, -1, 0, outputHeight, 0);// Rotate the calculation image canvas ready to extract image data

  calculationImage.drawImage(inputImage, 0, 0, outputWidth, outputHeight); // Draw calculation image
  ////////////////////////////////////////////////////////////////////////
  

  ////////////////////////////////////////////////////////////////////////
  // Upsidedown image (Image preview is generated from)
  ////////////////////////////////////////////////////////////////////////
  var upsideDownCanvas = document.getElementById('upsideDownCanvas'),
      upsideDownImage  = upsideDownCanvas.getContext('2d');

  upsideDownCanvas.width  = outputWidth * picsInRot;
  upsideDownCanvas.height = outputHeight;

  upsideDownImage.transform(1, 0, 0, -1, 0, outputHeight);

  for(var i = 0; i < picsInRot; i ++)
  {
    upsideDownImage.drawImage(inputImage, outputWidth * i, 0, outputWidth, outputHeight);
  }
  ////////////////////////////////////////////////////////////////////////

  /////////////////////
  // Picture Preview //
  /////////////////////
  var innerRadius = 75,
      outerRadius = (innerRadius + calculationImageCanvas.width) * 1.4, // Should use output height but its not working for some reason

      xCentrePoint = outerRadius,
      yCentrePoint = outerRadius,

      startX = 0,
      endX   = upsideDownCanvas.width,
      startY = 0,
      endY   = upsideDownCanvas.height;

  // drawRectInCircle(upsideDownCanvas, outerRadius + innerRadius / 2, outerRadius, 50, (innerRadius + 55) * 1.2, 0, 0, upsideDownCanvas.width, upsideDownCanvas.height, picsInRot);
  drawRectInCircle(upsideDownCanvas, xCentrePoint, yCentrePoint, innerRadius, outerRadius, startX, startY, endX, endY);

  ////////////////////
  // Get image data //
  ////////////////////
  var imageData = calculationImage.getImageData(0, 0, outputHeight, outputWidth).data; // Extract image data from the rotated calculation image (Height and Width swapped to compensate for rotation)
  
  /////////////////////
  // Save Image Data //
  /////////////////////
  // Width, LEDs, Data
  var result = "const char " + name + "[][totalLEDs][3] = {{"; // Generate image data output string

  for(var i = 0; i < imageData.length; i += 4) 
  {
    counter ++; // Counter is used to progress on to next image slice
    var red     = imageData[i], // Extract pixel data from image
        green   = imageData[i + 1],
        blue    = imageData[i + 2];
      

    result += "{" + red.toString() + "," + green.toString() + "," + blue.toString() + "}";  // RGB value being stored here (spaces removed 17/02/2019)

    // var outputValue = (imageData[i] << 16) + (imageData[i + 1] << 8) + (imageData[i + 2]);
    // result += "{0x" + outputValue.toString(16) + "}"; // RGB stored as a single decimal number

    // Goes to the next column in the picture
    if((counter == outputHeight-1) && (i < imageData.length - 4)) // Adds the next line in the array when the end of a picture slice has been reached
    {
      result += "},{"; // (spaces removed 17/02/2019)
      counter = -1;  // Such a bodge
    }

    else if(i < imageData.length - 4) // Adds a "," everywhere but the end
    {
      result += ","; // (spaces removed 17/02/2019)
    }
  }

  result += "}};";
  document.getElementById("OutPutTextArea").innerHTML += result; // Update the output text area
  
  console.log(imageData);  // Print out image data
  // console.log(result);
  
  /////////////////
  // Update Info //
  /////////////////
  document.getElementById("OriginalWidth").innerHTML        += inputImageWidth; // Display the image data on the web page
  document.getElementById("OriginalHeight").innerHTML       += inputImageHeight;
  document.getElementById("Scalar").innerHTML               += (inputImageHeight / outputHeight).toFixed(2);
  document.getElementById("OutputWidth").innerHTML          += outputWidth;
  document.getElementById("OutputHeight").innerHTML         += outputHeight;
  document.getElementById("TotalPixelsInPicture").innerHTML += imageData.length / 4;
  document.getElementById("SizeInMemory").innerHTML         += (((imageData.length / 4) * 8) / 1000) + "Kb";
}

// document.getElementById("numOfPics").addEventListener("keyup", function(event) // not working
// {
//   event.preventDefault();
//   if(event.keyCode == 13)
//   {
//     document.getElementById("Get").click();
//   }
// });

////////////////////////////////////////////////////////////////////////
//
//  #####                                 ######                      
// #     # #      ######   ##   #####     #     #   ##   #####   ##   
// #       #      #       #  #  #    #    #     #  #  #    #    #  #  
// #       #      #####  #    # #    #    #     # #    #   #   #    # 
// #       #      #      ###### #####     #     # ######   #   ###### 
// #     # #      #      #    # #   #     #     # #    #   #   #    # 
//  #####  ###### ###### #    # #    #    ######  #    #   #   #    #
//
////////////////////////////////////////////////////////////////////////
function clearData() // Clear all output data
{
  document.getElementById('OutPutTextArea').innerHTML       = '';
  document.getElementById("OriginalWidth").innerHTML        = '';
  document.getElementById("OriginalHeight").innerHTML       = '';
  document.getElementById("Scalar").innerHTML               = '';
  document.getElementById("OutputWidth").innerHTML          = '';
  document.getElementById("OutputHeight").innerHTML         = '';
  document.getElementById("TotalPixelsInPicture").innerHTML = '';
  document.getElementById("SizeInMemory").innerHTML         = '';
}

////////////////////////////////////////////////////////////////////////
//
//  #####                                                     
// #     # #      # #####  #####   ####    ##   #####  #####  
// #       #      # #    # #    # #    #  #  #  #    # #    # 
// #       #      # #    # #####  #    # #    # #    # #    # 
// #       #      # #####  #    # #    # ###### #####  #    # 
// #     # #      # #      #    # #    # #    # #   #  #    # 
//  #####  ###### # #      #####   ####  #    # #    # ##### 
//
////////////////////////////////////////////////////////////////////////
function copyToClipboard(element) // This function automatically copies the data to the clipboard
{
  var temp = $("<input>");

  $("body").append(temp);

  temp.val($(element).text()).select();

  document.execCommand("copy");

  temp.remove();
}

////////////////////////////////////////////////////////////////////////
//
// ######                                         ######                                       
// #     # #  ####  ##### #    # #####  ######    #     # #####  ###### #    # # ###### #    # 
// #     # # #    #   #   #    # #    # #         #     # #    # #      #    # # #      #    # 
// ######  # #        #   #    # #    # #####     ######  #    # #####  #    # # #####  #    # 
// #       # #        #   #    # #####  #         #       #####  #      #    # # #      # ## # 
// #       # #    #   #   #    # #   #  #         #       #   #  #       #  #  # #      ##  ## 
// #       #  ####    #    ####  #    # ######    #       #    # ######   ##   # ###### #    # 
//
////////////////////////////////////////////////////////////////////////
function drawRectInCircle(originalImage, xCentrePoint, yCentrePoint, innerRadius, outerRadius, startX, startY, endX, endY) 
{
  var picturePreviewCanvas = document.getElementById("picturePreviewCanvas");
  var picturePreview       = picturePreviewCanvas.getContext("2d");

  picturePreviewCanvas.width  = (2 * outerRadius);
  picturePreviewCanvas.height = (2 * outerRadius);
  var angle = 0;

  var step  = Math.atan2(1, outerRadius);
  var limit = Math.PI * 2;

  picturePreview.save();
  
  picturePreview.translate(xCentrePoint, yCentrePoint);
  while (angle < limit) 
  {
    picturePreview.save();
    picturePreview.rotate(angle);
    picturePreview.translate(innerRadius, 0);
    picturePreview.rotate(-Math.PI / 2);
    
    var ratio = angle / limit;
    var x     = startX + ratio * (endX - startX);

    picturePreview.drawImage(originalImage, x, startY, 1, (endY - startY), 0, 0, 1, (outerRadius - innerRadius));
    picturePreview.restore();
    angle += step;
  }
  picturePreview.restore(); 
}