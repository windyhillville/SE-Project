import peasy.*;
import java.io.*;
import controlP5.*;
import http.requests.*;

void setup() {
  size(1280, 720, P3D);
  
  // Setup PeasyCam for viewing
  cam = new PeasyCam(this, 0, 0, 0, 500);
  cam.setMinimumDistance(2000);
  cam.setMaximumDistance(80000);
  cam.setActive(false);
  perspective(PI/3, float(width)/float(height), 100, 200000);
  
  // Sets up solar system, Earth, and climate scenario Earth
  sun = setSolarSystem();
  earth = setEarth();
  climateEarth = setClimateEarth();
  // Overloaded function because I was getting a NullPointerException after adding logic
  random = setRandom("Random", 0, 0.0, "Terrestrial", 800);
  tinyPlanet = setComparison();
  
  // Load's star background
  starTexture = loadImage("data/stars.jpg");
  starSphere = createShape(SPHERE, 100000);
  starSphere.setTexture(starTexture);
  starSphere.setStroke(false);
  
  // Add Username and Password Text Boxes
  UsernameText = new TextBox(width/2 - 200, height/2 - 50, 400, 50, "Username");
  PasswordText = new TextBox(width/2 - 200, height/2 + 50, 400, 50, "Password");
  PasswordText.addEyeToggle("data/eyeClosed.png", "data/eyeOpened.png");
  
  // primary option buttons
  LoginButton = new Button(width/2 - 200, height/2 + 200, 400, 50, "Log In");
  CreateAccountButton = new Button(width/2 - 200, height/2 + 275, 400, 50, "Create an Account");
  SolarButton = new Button(width/2 - 75 + 300, height/2 - 25, 150, 50, "Solar System");
  EarthButton = new Button(width/2 - 75 - 300, height/2 - 25, 150, 50, "Earth");
  RandomButton = new Button(width/2 - 75, height/2 - 25 + 200, 150, 50, "Random Exoplanet");
  ComparisonButton = new Button(width/2 - 75, height/2 - 25, 150, 50, "Comparison to Earth");
  
  // exit buttons
  QuitButton = new Button(100, 50, 100, 50, "Quit");
  ExitButton = new Button(20, 650, 150, 50, "Exit");
  
    // used to switch to another random planet when in Random Exoplanets and Comparison to Earth respectively
  NextPlanetButton = new Button(width-300, 50, 200, 50, "Next Random Exoplanet");
  NextComparisonButton = new Button(width-300, 50, 200, 50, "Next Random Exoplanet");
  
  // used in the Climate section to control climate variables like temperature and Earth's visuals
  ClimateButton = new Button(width/2 - 75 - 300, height/2 - 25 + 200, 150, 50, "Climate Scenarios");
  GreenButton = new Button(width-300, 485, 200, 50, "Green Future");
  ModerateButton = new Button(width-300, 565, 200, 50, "Moderate Warming");
  ExtremeButton = new Button(width-300, 645, 200, 50, "Extreme Warming");
  ResetButton = new Button(width-300, 405, 200, 50, "Reset to Today");
  
  // used for favorites
  FavoriteMenuButton = new Button(width/2 - 75 + 300, height/2 - 25 + 200, 150, 50, "Favorites Menu");
  AddFavButton = new Button(width-150, 425, 150, 30, "Add Favorite");
  RemoveFavButton = new Button(width-150, 455, 150, 30, "Remove Favorite");
  
  // used to display organized information in various parts of the program
  LeftBox = new InfoBox(0, 485, 400, height-485);
  RightBox = new InfoBox(width-400, 485, 400, height-485);
  // used specifically for climate change action tips
  ClimateBox = new InfoBox(400, height-50, width-750, 50);
  
  // climate variables
  climateTint = color(255, 255, 255);
  climateDesc = "Earth's climate is stable, but signs of stress are emerging. Rising temperature, melting ice, an extreme weather hint at a shifting future.";
  climateTemp = "288 K (14.85 C)";
  climateHab = 100;
  climateTips = new ArrayList<String>();
  climateTips.add("Climate Tip: Switch to LED lights, which use up to 90% less energy.");
  climateTips.add("Climate Tip: Take shorter showers to conserve water.");
  climateTips.add("Climate Tip: Unplug devices when not in use to save phantom energy.");
  climateTips.add("Climate Tip: Use reusable bags and bottles to reduce plastic waste.");
  climateTips.add("Climate Tip: Walk, bike, or carpool to reduce carbon emissions.");
  
  actionTip = climateTips.get((int)random(4.99));
  
  // favorites buttons
  FavoriteButtons = new ArrayList<Button>();
  for (int i = 0; i < 5; i++) {
    Button b = new Button(width/2 - 200, 50 + i*125, 400, 100, "Empty");
    FavoriteButtons.add(b);
  }
  
  font = createFont("Arial Bold", 32);
  earthImg = loadImage("data/earth.jpg");
  
}

void draw() {
  // Generate entire login screen
  if (inLogin) {
    background(126);
    resetCameraToFaceMenu();
    cam.beginHUD();
    fill(0);
    textSize(128);
    textAlign(CENTER, TOP);
    text("Elysium", width/2, 100);
    UsernameText.draw();
    PasswordText.draw();
    LoginButton.draw();
    CreateAccountButton.draw();
    text(message, width/2, height/2 + 120);
    cam.endHUD();
  }
  // Draws entire menu screen
  else if (inMenu) {
    //textAlign(LEFT, BASELINE); // reset text alignment
    background(255);
    setStars();
    resetCameraToFaceMenu();
    
    cam.beginHUD();
    image(earthImg, width/2 - 200, 150, 400, 100);
    fill(255);
    textFont(font);
    text("Welcome To Elysium!", width/2, 200);
    SolarButton.draw();
    EarthButton.draw();
    ComparisonButton.draw();
    RandomButton.draw();
    ExitButton.draw();
    ClimateButton.draw();
    FavoriteMenuButton.draw();
    text("Elysium Version 1.0\nNASA custom dataset retrieval date: 4/2/25\nhttps://exoplanetarchive.ipac.caltech.edu/cgi-bin/TblView/nph-tblView?app=ExoTbls&config=PSCompPars", width/2, height-50);
    cam.endHUD();
  // Draws Solar System screen
  } else if (inSolar) {
    // 3D rendering
    background(0);
    setStars();
    sun.show(); 
    pointLight(255, 255, 255, 0, 0, 0);
    cam.setMinimumDistance(sun.radius*4);
    cam.beginHUD();
    QuitButton.draw();
    cam.endHUD();
    // Draws Earth screen
  } else if (inEarth) {
    background(0);
    setStars();
    earth.show(); 
    pointLight(255, 255, 255, 0, 0, 0);
    cam.setMinimumDistance(earth.radius*4);
    cam.beginHUD();
    QuitButton.draw();
    cam.endHUD();
    // Draws random exoplanet screen 
  } else if (inRandom) {
    background(0);
    setStars();
    random.show(); 
    pointLight(255, 255, 255, 0, 0, 0);
    cam.setMinimumDistance(random.radius*4);
    cam.beginHUD();
    textLeading(15);
    textAlign(LEFT, TOP);
    text(message, width-200, 375, 190, 200);
    QuitButton.draw();
    NextPlanetButton.draw();
    RightBox.draw(random);
    AddFavButton.draw();
    RemoveFavButton.draw();
    cam.endHUD();
    // Draws comparison screen
  } else if (inComparison) {
    background(0);
    setStars();
    tinyPlanet.show(); 
    random.show();
    pointLight(255, 255, 255, 0, 0, 0);
    cam.setMinimumDistance(3000);
    cam.beginHUD();
    textLeading(15);
    textAlign(LEFT, TOP);
    text(message, width-200, 375, 190, 200);
    QuitButton.draw();
    NextComparisonButton.draw();
    LeftBox.draw(tinyPlanet.planets.get(2));
    RightBox.draw(random);
    AddFavButton.draw();
    RemoveFavButton.draw();
    cam.endHUD();
    // Draws climate scenario screen
  } else if (inClimate) {
    background(0);
    setStars();
    ambientLight(red(climateTint), green(climateTint), blue(climateTint));
    climateEarth.show();
    // pointLight(255, 255, 255, 0, 0, 3000);
    cam.setMinimumDistance(earth.radius*4);
    cam.beginHUD();
    QuitButton.draw();
    LeftBox.draw(climateEarth);
    ClimateBox.draw();
    GreenButton.draw();
    ModerateButton.draw();
    ExtremeButton.draw();
    ResetButton.draw();
    cam.endHUD();
    // Draws favorites screen
  } else if (inFavorites) {
    background(0);
    setStars();
    pointLight(255, 255, 255, 0, 0, 0);
    cam.beginHUD();
    QuitButton.draw();
    // Sets button labels equal to user defined favorites
    for (int i = 0; i < 5; i++) {
      if (i < favoritesJSON.size()) {
        JSONObject planet = favoritesJSON.getJSONObject(i);
        FavoriteButtons.get(i).label = planet.getString("name");
      }
      else
        FavoriteButtons.get(i).label = "Empty";
        
      FavoriteButtons.get(i).draw();
    }
    cam.endHUD();
  }
}

void mousePressed() {
  
  // Enter Log In Screen
  if (inLogin) {
    UsernameText.handleMousePressed();
    // Click username textbox
    if (UsernameText.isPressed) {
      PasswordText.isPressed = false;
      PasswordText.isTyping = false;
      // ...
    }
    // Click username textbox
    PasswordText.handleMousePressed();
    if (PasswordText.isPressed) {
      UsernameText.isPressed = false;
      UsernameText.isTyping = false;
      // ...
    } 
    // Click Log in button
    LoginButton.handleMousePressed();
    if (LoginButton.isPressed) {
      // implement function for JSON object handling
      if (isLoginSuccessful()) {
        favoritesJSON = loadFavorites();
        message = "";
        inMenu = true;
        inLogin = false;
      }
      else {
        textSize(50);
        message = "Incorrect Username/Password!";
      } 
    }
    // Click Create Account Button 
    CreateAccountButton.handleMousePressed();
    if (CreateAccountButton.isPressed) {
      String result = isAccountCreated();
      if (result != "Account successfully created!") {
        message = result;
      }
      else {
        message = result;
      }
    }
  }
  // Check for menu button clicks
  else if (inMenu) {
    // Click Solar System Button
    SolarButton.handleMousePressed();
    if (SolarButton.isPressed) {
      inMenu = false;
      inSolar = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
      setSolarSystem();
    }
    // Click Earth button
    EarthButton.handleMousePressed();
    if (EarthButton.isPressed) {
      inMenu = false;
      inEarth = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Random Exoplanet button
    RandomButton.handleMousePressed();
    if (RandomButton.isPressed) {
      //testServerConnection();
      setRandom();
      
      inMenu = false;
      inRandom = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Comparison button
    ComparisonButton.handleMousePressed();
    if (ComparisonButton.isPressed) {
      
      // constructs random planet
      setRandom();
      inMenu = false;
      inComparison = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Climate button
    ClimateButton.handleMousePressed();
    if (ClimateButton.isPressed) {
      inMenu = false;
      inClimate = true;
      actionTip = climateTips.get((int)random(4.99));
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Favorites button
    FavoriteMenuButton.handleMousePressed();
    if (FavoriteMenuButton.isPressed) {
      inMenu = false;
      inFavorites = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // CLick Exit button
    ExitButton.handleMousePressed();
    if (ExitButton.isPressed) {
      exit();
    }
  } 
  // Click Random Exoplanet button
  else if (inRandom) {
    // Click Next button
    NextPlanetButton.handleMousePressed();
    if (NextPlanetButton.isPressed) {
      message = "";
      setRandom();
      inMenu = false;
      inRandom = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Add Favorite button
    AddFavButton.handleMousePressed();
    if (AddFavButton.isPressed) {
      // add favorite
      message = editFavorites("/mainMenu/addFavorite");
      favoritesJSON = updateFavorites();
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Remove Favorite button
    RemoveFavButton.handleMousePressed();
    if (RemoveFavButton.isPressed) {
      // remove favorite
      message = editFavorites("/mainMenu/removeFavorite");
      favoritesJSON = updateFavorites();
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
  }
  // Click Comparison button
  else if (inComparison) {
    // Click Next button
    NextComparisonButton.handleMousePressed();
    if (NextComparisonButton.isPressed) {
      message = "";
      // constructs random planet
      setRandom();
      inMenu = false;
      inComparison = true;
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Add Favorite button
    AddFavButton.handleMousePressed();
    if (AddFavButton.isPressed) {
      // add favorite
      message = editFavorites("/mainMenu/addFavorite");
      favoritesJSON = updateFavorites();
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
    // Click Remove Favorite button
    RemoveFavButton.handleMousePressed();
    if (RemoveFavButton.isPressed) {
      // remove favorite
      message = editFavorites("/mainMenu/removeFavorite");
      favoritesJSON = updateFavorites();
      cam.setActive(true);
      cam.lookAt(0, 0, 0, 1000);
    }
  }
  // Click Climate Scenario button
  else if (inClimate) {
    message = "";
    // Click Green button
    GreenButton.handleMousePressed();
    if (GreenButton.isPressed) {
      climateTint = color(255);
      climateDesc = "A hopeful future. Emmissions are curbed, renewable energy prevails, and Earth's climate stabilizes. Most ecosystems and human habitats remain livable, with only minor changes in temperature.";
      climateTemp = "289.5 K (16.35 C)";
      climateHab = 95;
      actionTip = climateTips.get((int)random(4.99));
    }
    // Click Moderate button
    ModerateButton.handleMousePressed();
    if (ModerateButton.isPressed) {
      climateTint = color(150);
      climateDesc = "A future shaped by partial action. Temperatures rise noticeably, weather grows more unpredictable, and some regions become less habitable. The world adapts, but not without consequence.";
      climateTemp = "290.5 K (17.35 C)";
      climateHab = 80;
      actionTip = climateTips.get((int)random(4.99));
    }
    // Click Extreme button
    ExtremeButton.handleMousePressed();
    if (ExtremeButton.isPressed) {
      climateTint = color(100);
      climateDesc = "A future of unchecked emissions. Earth's average temperature surges, habitability plummets, and once-thriving regions become hostile. Drought, flooding, and heat reshape the planet.";
      climateTemp = "293.0 K (19.85 C)";
      climateHab = 50;
      actionTip = climateTips.get((int)random(4.99));
    }
    // Click Reset Button
    ResetButton.handleMousePressed();
    if (ResetButton.isPressed) {
      climateTint = color(255);
      climateDesc = "Earth's climate is stable, but signs of stress are emerging. Rising temperature, melting ice, an extreme weather hint at a shifting future.";
      climateTemp = "288 K (14.85 C)";
      climateHab = 100;
      actionTip = climateTips.get((int)random(4.99));
    }
  }
  // Click Favorites button
  else if (inFavorites) {
    message = "";
    // Selects User's favorite exoplanet
    for (int i = 0; i < 5; i++) {
      FavoriteButtons.get(i).handleMousePressed();
      if (FavoriteButtons.get(i).isPressed) {
        for (int j = 0; j < favoritesJSON.size(); j++) {
          JSONObject planet = favoritesJSON.getJSONObject(j);
          
          if (FavoriteButtons.get(i).label.equals(planet.getString("name"))) {
            setPlanet(planet);
            inRandom = true;
            inFavorites = false;
          }
          
        }
        print(i);
        cam.setActive(true);
        cam.lookAt(0, 0, 0, 1000);
      }
    }
  }
  // Click Quit button
  QuitButton.handleMousePressed();
  if (QuitButton.isPressed) {
    message = "";
    inMenu = true;
    inSolar = false; inEarth = false; 
    inComparison = false; inRandom = false; 
    inClimate = false; inFavorites = false;
    cam.setActive(false);
  }
  
}
  

// Resets buttons
void mouseReleased() {
  if (inLogin) {
    LoginButton.handleMouseReleased();
    CreateAccountButton.handleMouseReleased();
  }
  else if (inMenu) {
    SolarButton.handleMouseReleased();
    EarthButton.handleMouseReleased();
    RandomButton.handleMouseReleased();
    ComparisonButton.handleMouseReleased();
    ClimateButton.handleMouseReleased();
    FavoriteMenuButton.handleMouseReleased();
    QuitButton.handleMouseReleased();
  }
  else {
    NextPlanetButton.handleMouseReleased();
    NextComparisonButton.handleMouseReleased();
    GreenButton.handleMouseReleased();
    ModerateButton.handleMouseReleased();
    ExtremeButton.handleMouseReleased();
    ResetButton.handleMouseReleased();
    for (int i = 0; i < 5; i++)
      FavoriteButtons.get(i).handleMouseReleased();
    AddFavButton.handleMouseReleased();
    RemoveFavButton.handleMouseReleased();
  }
}
// Enters characters into active textbox fields
void keyPressed() {
  if (UsernameText.isTyping) {
    UsernameText.keyPressed(key);
  } 
    
  else if (PasswordText.isTyping) {
    PasswordText.keyPressed(key);
  }
    
}
// Sends out HTTP request for resetting internal container for User Favorites upon exiting system
void exit() {
  println("Exit called!");
  PostRequest post = new PostRequest("http://localhost:5001/resetUser");
  post.addHeader("Content-Type", "application/json");
  post.send();
  super.exit();
}
// Resets Camera
void resetCameraToFaceMenu() {
  cam.lookAt(width / 2, height / 2, 0, 100);  // Face the 2D plane at z = 0
}
// Draws galaxy
void setStars() {
  pushMatrix();
  hint(DISABLE_DEPTH_TEST);
  shape(starSphere);
  hint(ENABLE_DEPTH_TEST);
  popMatrix();
}
// Sets up planets in our Solar System
Planet setSolarSystem() {
  PImage sunImg = loadImage("data/GoldiLock.jpg");
  PImage mercuryImg = loadImage("data/mercury.jpg");
  PImage venusImg = loadImage("data/venus.jpg");
  PImage earthImg = loadImage("data/earth.jpg");
  PImage marsImg = loadImage("data/mars.jpg");
  PImage jupiterImg = loadImage("data/jupiter.jpg");
  PImage saturnImg = loadImage("data/saturn.jpg");
  PImage uranusImg = loadImage("data/uranus.jpg");
  PImage neptuneImg = loadImage("data/neptune.jpg");
  sun = new Planet("sun", 30000, 0, "type", 800, 0, 0, sunImg);
  sun.spawnMoons(8);
  float offset = sun.radius + 100;
  sun.addPlanet(new Planet("Mercury", 3.3e23f,  1.89e-6f, "Terrestrial", 24.4,  (offset + 570),   1/(570 + offset),   mercuryImg));
  sun.addPlanet(new Planet("Venus",   4.87e24f, 3.49e-6f, "Terrestrial", 60.5,  (offset + 1080),  1/(1080 + offset),  venusImg));
  sun.addPlanet(new Planet("Earth",   5.97e24f, 0.0,      "Terrestrial", 63.7,  (offset + 1490),  1/(1490 + offset),  earthImg));
  sun.addPlanet(new Planet("Mars",    6.42e23f, 7.39e-6f, "Terrestrial", 33.9,  (offset + 2270),  1/(2270 + offset),  marsImg));
  sun.addPlanet(new Planet("Jupiter", 1.90e27f, 2.52e-5f, "Gas Giant",   699.1, (offset + 7780),  1/(7780 + offset),  jupiterImg));
  sun.addPlanet(new Planet("Saturn",  5.68e26f, 4.64e-5f, "Gas Giant",   582.3, (offset + 14300), 1/(14300 + offset), saturnImg));
  sun.addPlanet(new Planet("Uranus",  8.68e25f, 9.29e-5f, "Ice Giant",   253.6, (offset + 28700), 1/(28700 + offset), uranusImg));
  sun.addPlanet(new Planet("Neptune", 1.02e26f, 1.46e-4f, "Ice Giant",   246.2, (offset + 45000), 1/(45000 + offset), neptuneImg));
  return sun;
}
// Sets Earth parameters
Planet setEarth() {
  PImage earthImg = loadImage("data/earth.jpg");
  earth = new Planet("Earth", 5.97e24f, 0.0, "Terrestrial", 800,  0,  0,  earthImg, 9.81, 100);
  return earth;
}
// Sets Climate Scenario Earth parameters
Planet setClimateEarth() {
  PImage earthImg = loadImage("data/earth.jpg");
  climateEarth = new Planet("Climate Earth", 5.97e24f, 0.0, "Terrestrial", 800,  0,  0,  earthImg, 9.81, 100);
  return climateEarth;
}

// For setup (probably could be combined with setRandom())
Planet setRandom(String name, float mass, float dfe, String type, float radius) {
  String jpg = setPlanetImage(type, radius);
  PImage randomImg = loadImage(jpg);
    random = new Planet(name, mass, dfe, type, radius,  0,  0,  randomImg);
  //random = new Planet("Random", 0, 0.0, "Terrestrial", 800,  0,  0,  randomImg);
  return random;
}
// Changes current planet to User favorite
void setRandom() {
  JSONObject planetJSON = getRandomPlanetJson();
  setPlanet(planetJSON);
}
// Sets current planet
void setPlanet(JSONObject planet) {
  // FIXME:: Sometimes "type" returns null and causes a NullPointerException
  String jpg = setPlanetImage(planet.getString("type"), planet.getFloat("radius"));
  PImage randomTexture = loadImage(jpg);
  
  // radius is a multiple of Earth's size, so I'm multiplying each radius by Earth's radius found in setSolarSystem()
  random = new Planet(planet.getString("name"), planet.getFloat("mass"), 
                      planet.getFloat("distanceFromEarth"), planet.getString("type"), 
                      planet.getFloat("radius")*63.7,  0,  0,  randomTexture,
                      planet.getFloat("gravity"), planet.getFloat("habitability")
                      );
}
// Sets up Earth comparison screen
Planet setComparison() {
  PImage randomImg = loadImage("data/generic.jpg");
  PImage earthImg = loadImage("data/earth.jpg");
  tinyPlanet = new Planet("tiny", 0, 0.0, "base", 1,  0,  0,  randomImg);
  tinyPlanet.spawnMoons(2);
  tinyPlanet.addPlanet(new Planet("Earth", 5.97e24f, 0.0, "Terrestrial", 63.7,  earth.radius + 400,  0,  earthImg, 9.81, 100));
  //tinyPlanet.addPlanet(new Planet("Random", 5.97e24f, 0.0, "question", 800,  random.radius + 400,  0,  randomImg));
  return tinyPlanet;
}
// Determines planet texture based off of type and radius of exoplanet
String setPlanetImage(String type, float radius) {
  
  // Placeholders
  switch(type) {
    case "Terrestrial":
      return "data/generic.jpg";
    case "Super Earth": {
      if (radius < 1.5)
        return "data/SuperEarth2.png";
      else if (radius < 1.6)
        return "data/SuperEarth3.png";
      else if (radius < 1.7)
        return "data/SuperEarth4.png";
      else
        return "data/SuperEarth1.png";
    }
    case "Mini-Neptune":
      return "data/uranus.jpg";
    case "Neptune-like":
      return "data/neptune.jpg";
    case "Gas Giant": {
      if (radius <= 7.0)
        return "data/GasGiant1.png";
      else if (radius <= 8.0)
        return "data/GasGiant2.png";
      else if (radius <= 9.0)
        return "data/GasGiant3.png";
      else if (radius <= 10.0)
        return "data/GasGiant4.png";
      else if (radius <= 11.0)
        return "data/GasGiant5.png";
      else if (radius <= 12.0)
        return "data/GasGiant6.png";
      else if (radius <= 13.0)
        return "data/GasGiant7.png";
      else if (radius <= 14.0)
        return "data/GasGiant8.png";
      else if (radius <= 15.0)
        return "data/GasGiant9.png";
      else
        return "data/GasGiant10.png";
    }
      
    default:
      return "data/question.jpg";
  }
  
}

// Tests for server connection (it works!)
void testServerConnection() {
  PostRequest post = new PostRequest("http://localhost:5001/test");
  post.addHeader("Content-Type", "application/json");
  post.addData("{\"input\": \"Random planet button clicked\"}");
  post.send();
    
  JSONObject json = parseJSONObject(post.getContent());
  println(json.getString("result"));
}

// Generates a Random Planet JSON Object
JSONObject getRandomPlanetJson() {
  PostRequest post = new PostRequest("http://localhost:5001/planet/random");
  post.addHeader("Content-Type", "application/json");
  post.send();
  
  String content = post.getContent();
  if (content == null || content.isEmpty())
    return null;
  
  return parseJSONObject(content);
}

// Authenticates user data
JSONObject authenticateUser(String route) {
  PostRequest post = new PostRequest("http://localhost:5001" + route);
  post.addHeader("Content-Type", "application/json");
  
  JSONObject body = new JSONObject();
  body.setString("username", UsernameText.input);
  body.setString("password", PasswordText.input);
  
  post.addData(body.toString());
  post.send();
  
  String content = post.getContent();
  if (content == null || content.isEmpty())
    return null;
    
  return parseJSONObject(content);
}

// Checks if user profile exists
boolean isLoginSuccessful() {
  JSONObject result = authenticateUser("/loginScreen/signIn");
  return result.getBoolean("truthValue");
}

// Checks account state --> Does this account exist?
String isAccountCreated() {
  JSONObject userState = authenticateUser("/loginScreen/createAccount");
  return userState.getString("result");
}

// Add or removes favorites from backend
String editFavorites(String route) {
  PostRequest post = new PostRequest("http://localhost:5001" + route);
  post.addHeader("Content-Type", "application/json");
  post.addData("{\"planetName\": " + "\"" + random.name + "\"}");
  post.send();
  
  String content = post.getContent();
  
  if (content == null || content.isEmpty())
    return null;
    
  JSONObject message = parseJSONObject(content);
  return message.getString("result");
}

// Loads User favorites for program initialization
JSONArray loadFavorites() {
  PostRequest post = new PostRequest("http://localhost:5001/mainMenu/loadFavorites");
  post.addHeader("Content-Type", "application/json");
  post.send();
  
  String content = post.getContent();
  if (content == null || content.isEmpty())
    return null;
  
  JSONArray favorites = parseJSONArray(content);
  return favorites;
}

// Updates User favorites during runtime
JSONArray updateFavorites() {
  PostRequest post = new PostRequest("http://localhost:5001/mainMenu/updateFavorites");
  post.addHeader("Content-Type", "application/json");
  post.send();
  
  String content = post.getContent();
  if (content == null || content.isEmpty())
    return null;
  
  JSONArray favorites = parseJSONArray(content);
  return favorites;
}
