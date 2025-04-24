// Cam
PeasyCam cam;
float xPosCam = 0;
float yPosCam = 0;
float zPosCam = 0;

// Planets
Planet sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, random, Crandom, tinyPlanet, climateEarth;
PImage earthImg;

// Background
PShape starSphere;
PImage starTexture;

// TextBox
TextBox UsernameText;
TextBox PasswordText;

//Buttons
Button LoginButton;
Button LogoutButton;
Button CreateAccountButton;
Button SolarButton;
Button EarthButton;
Button ComparisonButton;
Button RandomButton;
Button QuitButton;
Button ExitButton;
Button NextPlanetButton;
Button NextComparisonButton;
Button ClimateButton;
Button GreenButton;
Button ModerateButton;
Button ExtremeButton;
Button ResetButton;
Button FavoriteMenuButton;
Button AddFavButton;
Button RemoveFavButton;

// Favorites buttons
ArrayList<Button> FavoriteButtons;

// InfoBoxes
InfoBox LeftBox;
InfoBox RightBox;
InfoBox ClimateBox;

// Climate Variables
color climateTint;
String climateDesc;
String climateTemp;
float climateHab;
ArrayList<String> climateTips;
String actionTip;

// Booleans
boolean inLogin = true;
boolean inMenu = false;
boolean inSolar = false;
boolean inEarth = false;
boolean inComparison = false;
boolean inRandom = false;
boolean inClimate = false;
boolean inFavorites = false;

// Toggle
Toggle favoriteToggle;

// Font
PFont font;

// Positions
float textBoxX = width/2 - 200;
float textBoxY = height/2 - 50;

// Messages
String message = "";
JSONObject jsonMessage;

JSONArray favoritesJSON;
