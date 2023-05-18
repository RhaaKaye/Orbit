  img = new Image();
  img.src="https://i.imgur.com/G3jGFfX.png";
  
  img.onload = function()
  {

  var cv = document.getElementById('cv');
  var originalImageCanvas = document.getElementById("originalImage");
  var outputImage = originalImageCanvas.getContext("2d");


  var originalImageWidth  = originalImage.naturalWidth;
  var originalImageHeight = originalImage.naturalHeight;
  
  outputImage.drawImage(img, 0, 0, originalImageWidth, originalImageHeight);

  var repeats = 4; 
  var LEDs = 55;  

  var xCentrePoint = 200,
      yCentrePoint = 200;

  var innerRadius = 50,
      outerRadius = innerRadius + LEDs;

  var startX = 0,
      endX   = originalImageWidth,
      startY = 0,
      endY   = originalImageHeight;

  // drawRectInCircle(originalImageCanvas, xCentrePoint, yCentrePoint, innerRadius, outerRadius, startX, startY, endX, endY, repeats);

  // draw the part of img defined by the rect (startX, startY, endX, endY) inside 
  //   the circle of center (cx,cy) between radius (innerRadius -> outerRadius) 
  // - no check performed -
  // function drawRectInCircle(img, xCentrePoint, yCentrePoint, innerRadius, outerRadius, startX, startY, endX, endY, repeats) 
  // {
  //   var angle = 0;

  //   var step  = 1 * Math.atan2(1, outerRadius);
  //   var limit = 2 * Math.PI;
    
  //   console.log(step);
  //   console.log(limit);

  //   outputImage.save();
  //   outputImage.translate(xCentrePoint, yCentrePoint);
  //   while (angle < limit) 
  //   {
  //     outputImage.save();
  //     outputImage.rotate(angle);
  //     outputImage.translate(innerRadius, 0);
  //     outputImage.rotate(-Math.PI / 2);
  //     var ratio = angle / limit;
  //     var x = startX + ratio * (endX - startX);
  //     outputImage.drawImage(img, x, startY, 1, (endY - startY), 0, 0, 1, (outerRadius - innerRadius));
  //     outputImage.restore();
  //     angle += step;
  //   }
  //   outputImage.restore();
  // }
}
