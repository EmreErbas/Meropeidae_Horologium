# ESP32 & Offline Clock

## HTML basics

`<!DOCTYPE HTML><html>` indicates that we are sending HTML  
`<head><meta name="viewport" content="width=device-width, initial-scale=1">` makes the web page responsive in any web browser
`<link rel="icon" href="data:,">` prevent requests on the favicon  
`<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}` some CSS text to style the buttons and the web page appearance  
`.button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}`  
`.button2 {background-color: #555555;}</style></head>`

```html
<!DOCTYPE html>  
<html>  
<head>  
  <meta name="viewport" content="width=device-width, initial-scale=1">  
  <link rel="icon" href="data:,">  
  <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}  
    .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; 
      text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}  
    .button2 {background-color: #555555; border: none; color: white; padding: 16px 40px; 
      text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}  
  </style>  
  <p>  
    <a href="/26/on"><button class="button">ON</button></a>  
    <a href="/27/off"><button class="button2">OFF</button></a>  
  </p>  
</head>  
<body>  
  <h1>My First Heading</h1>  
  <p>My first paragraph.</p>  
</body>  
</html>  
```

This [webpage](https://randomnerdtutorials.com/esp32-web-server-arduino-ide/) can be useful for quick start.




