import peasy.*;
// Abstract base class called UI which contains four subclasses --> TextBox, InfoBox, Button, and Toggle
abstract class UI {
  float x, y, w, h;
  String label;
  color bgColor, hoverColor, textColor;
  boolean isHovered = false;
  boolean isPressed = false;
  // Checks if mouse is over button
  boolean isMouseOver() {
  return mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h;
  }
  // Checks if button is clicked
  boolean clicked() {
    return isHovered && isPressed;
  }
  // Handles boolean switches for when mouse has been clicked
  void handleMousePressed() {
    if (isMouseOver()) {
      isPressed = true;
    }
  }
  // Handles mouse release after button has been pressed
  void handleMouseReleased() {
    isPressed = false;
  }
}
// Used for button interface
class Button extends UI {

  Button(float x, float y, float w, float h, String label) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.label = label;

    // Default colors
    bgColor = color(100, 150, 250);
    hoverColor = color(70, 120, 220);
    textColor = color(255);
  }
  // Draws button to screen
  void draw() {
    isHovered = isMouseOver();
    fill(isHovered ? hoverColor : bgColor);
    stroke(0);
    rect(x, y, w, h, 8);

    fill(textColor);
    textAlign(CENTER, CENTER);
    textSize(14);
    text(label, x + w / 2, y + h / 2);
  }
  
  // Override this method when subclassing or set with an interface
  void onClick() {
    println("Button '" + label + "' clicked.");
  }
}
// Used for Username and Password text fields in Log In screen
class TextBox extends UI {
  
  String input = "";
  String hiddenInput = "";
  boolean isTyping = false;
  boolean isTextBoxEmpty = true;
  
  Toggle eyeIcon;
  boolean isShowing;
  boolean hasEye = false;
  
  TextBox(float x, float y, float w, float h, String label) {
    
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.label = label;
    
    bgColor = color(255);
    hoverColor = color (225);
    textColor = color(0);
    
  }
  // Draws text fields
  void draw() {
    isHovered = isMouseOver();
    fill(isTyping ? hoverColor : bgColor);
    rect(x, y, w, h, 8);
    textAlign(LEFT, TOP);
    
    // Draw label for texboxes
    if (!isTyping && isTextBoxEmpty) {
      fill(color(127));
      textSize(15);
      text(label, x+5, y+17);
    }
    
    // Draw "eye" icons
    if (hasEye) {
      eyeIcon.draw();
    }
    
    // Draw user input
    fill(textColor);
    textSize(25);
    if (hasEye) {
      if (eyeIcon.isShowing) {
        text(input, x+5, y+15);
      }
      // Hides password input
      else {
        text(hiddenInput, x+5, y+20);
      }
        
    }
    else 
      text(input, x+5, y+15);
  }
  // Handles all key interactions between user and system when in Log In screen
  void keyPressed(char key) {
    if (key == BACKSPACE && input.length() > 0) {
      input = input.substring(0, input.length()-1);
      hiddenInput = hiddenInput.substring(0, hiddenInput.length()-1);
    }
      
    else if (key != CODED && key != BACKSPACE && key != ENTER && input.length() < 19) {
      input += key;
      hiddenInput += '*';
    }
    
    if (input.isEmpty())
      isTextBoxEmpty = true;
    else
      isTextBoxEmpty = false;
  }
  // Adds eye toggle object to text field
  void addEyeToggle(String eye1, String eye2) {
    eyeIcon = new Toggle(eye1, eye2, x+360, y+12, 25, 25);
    isShowing = false;
    hasEye = true;
  }
  // Checks if user input is empty
  boolean isEmpty() {
    return input.length() > 0;
  }
  // Overrides method to handle additional boolean called isTyping & to deal with eye icons
  @Override
  void handleMousePressed() {
    if (isMouseOver()) {
      isPressed = true;
      isTyping = true;
    }
    
    if (hasEye)
      eyeIcon.handleMousePressed();
    
  }
  // Same as above, but for mouse releases
  @Override
  void handleMouseReleased() {
    isPressed = false;
    isTyping = false;
  }
  
}
// Toggle class to handle eye icon
class Toggle extends UI {
  PImage image1;
  PImage image2;
  boolean isShowing = false;
  
  Toggle(String image1, String image2, float x, float y, float w, float h) {
    this.image1 = loadImage(image1);
    this.image2 = loadImage(image2);
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
  }
  // Overrides method to handle when eye is and isn't showing
  @Override
  void handleMousePressed() {
    if (isMouseOver()) {
      isPressed = true;
      isShowing = !isShowing;
    }
  }
  // Draws toggle button to the screen
  void draw() {
    
    if (!isShowing)
      image(image1, x, y, w, h);
    else
      image(image2, x, y, w, h);
  }
  
}
// Handles all instances of when displaying climate change information to the user
class InfoBox extends UI {
  
  InfoBox(float x, float y, float w, float h) {
    
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    
    bgColor = color(130, 180, 255);
    textColor = color(255);
  }
  
  String Earth = "The only known planet to support life. With balanced gravity, a temperate climate, and abundant water, Earth serves as the benchmark for habitability across the universe";
  String Terrestrial = "Small, rocky planets with solid surfaces. Similar to Earth or Mars, these planets are the most likely to support life as we know it.";
  String SuperEarth = "Larger and more massive than Earth, but still rocky. They may have stronger gravity and thicker atmospheres, offering both challenges and potential for habitability.";
  String MiniNeptune = "Intermediate in size between Earth and Neptune, these planets likely have thick atmospheres and may lack solid surfaces. Conditions for life are less favorable, but not impossible.";
  String NeptuneLike = "Gas-dominated planets with thick, icy atmospheres and no solid surface. They are cold, dense, and inhospitable, often featuring strong winds and complex weather systems.";
  String GasGiant = "Massive planets composed primarily of hydrogen and helium, with no solid surface. They have deep atmospheres, intense pressures, and extreme temperatures, making them inhospitable to life as we know it.";
  
  // Overloaded function to handle three different instances of when climate information is displayed to the user (i.e., Earth button, Climate Scenario button, and Random Exoplanet button)
  void draw(Planet planet) {
    fill(bgColor);
    rect(x, y, w, h);
    
    fill(textColor);
    textSize(15);
    textLeading(15);
    textAlign(LEFT, TOP);
    if (planet.name.equals("Earth")) {
      text("Present Day Earth: See how mass radius, gravity, and habitability stack up between our home and distant worlds!", x+5, y+5, 390, 200);
      text("Properties", x+5, y+60);
      text("Mass: 5.972e24 kg", x+5, y+75);
      text("Radius: 6,671 km", x+5, y+90);
      text("Gravity: 9.81 m/s^2", x+5, y+105);
      text("Description: " + Earth, x+5, y+130, 350, 200);
      text("Habitability: 100%", x+5, y+215);
    }
    else if (planet.name.equals("Climate Earth")) {
      text("Present Day Earth: Choose from future scenarios to see how rising temperatures affect habitability and surface conditions.", x+5, y+5, 390, 200);
      text("Properties", x+5, y+60);
      text("Mass: 5.972e24 kg", x+5, y+75);
      text("Radius: 6,671 km", x+5, y+90);
      text("Gravity: 9.81 m/s^2", x+5, y+105);
      text("Average Surface Temperature: " + climateTemp, x+5, y+120);
      text("Description: " + climateDesc, x+5, y+140, 390, 200);
      text("Habitability: " + climateHab + "%", x+5, y+215);
      // random(4);
    }
    else {
      text("Exoplanet Name: " + planet.name, x+5, y+5);
      text("Properties", x+5, y+30);
      text("Mass: " + nf(planet.mass, 0, 2) + " Earth Masses", x+5, y+45);
      text("Radius: " + nf((planet.radius)/63.7, 0, 2) + " Earth Radii", x+5, y+60);
      if (planet.gravity != -1)
        text("Gravity: " + planet.gravity + " m/s^2", x+5, y+75);
      text("Distance from Earth: " + nf(planet.distanceFromEarth, 0, 2) + " parsecs", x+5, y+90);
      text("Type: " + planet.type, x+5, y+105);
      if (planet.type.equals("Terrestrial"))
        text("Description: " + Terrestrial, x+5, y+130, 350, 200);
      else if (planet.type.equals("Super Earth"))
        text("Description: " + SuperEarth, x+5, y+130, 350, 200);
      else if (planet.type.equals("Mini-Neptune"))
        text("Description: " + MiniNeptune, x+5, y+130, 350, 200);
      else if (planet.type.equals("Neptune-like"))
        text("Description: " + NeptuneLike, x+5, y+130, 350, 200);
      else if (planet.type.equals("Gas Giant"))
        text("Description: " + GasGiant, x+5, y+130, 350, 200);
      if (planet.habitability != -1)
        text("Habitability: " + planet.habitability + "%", x+5, y+215);
    }
  }
  // draws textboxes to screen
  void draw() {
    fill(bgColor);
    rect(x, y, w, h);
    
    fill(textColor);
    textSize(15);
    textLeading(15);
    textAlign(LEFT, TOP);
    
    text(actionTip, x+5, y+5);
  }
}
