import java.io.*;
// Planet class for all exoplanets and planets within our solar system
class Planet {
  // For Backend
  String name;
  float mass;
  float distanceFromEarth;
  String type;
  float gravity;
  float habitability;
  // For both
  float radius;
  // For UI
  float angle;
  float distance;
  ArrayList<Planet> planets = new ArrayList<Planet>();
  float orbitspeed;
  PVector v;
  
  PShape globe;
  
  // Default Constructor
  Planet() {
    name = "generic"; mass = 0; distanceFromEarth = 0; type = "null";
    
    v = PVector.random3D();
    radius = 0;
    //angle = random(2*PI);
    distance = 0;
    orbitspeed = 0;
    v.mult(distance);
    noStroke();
    noFill();
    globe = createShape(SPHERE, radius);
    globe.setTexture(loadImage("data/question.jpg"));
  }
  
  // Constructor that takes in additional parameters gravity and habitability
  Planet(String n, float m, float dfe, String t, float r, float d, float o, PImage img, float g, float h) {
    
    name = n;
    mass = m;
    distanceFromEarth = dfe;
    type = t;
    gravity = g;
    habitability = h;
    
    v = PVector.random3D();
    radius = r;
    //angle = random(2*PI);
    distance = d;
    orbitspeed = o;
    v.mult(distance);
    
    noStroke();
    noFill();
    globe = createShape(SPHERE, radius);
    globe.setTexture(img);
  }
  
  // Constructor that takes in name, mass, distance from Earth, type, distance, orbit speed, and image
  Planet(String n, float m, float dfe, String t, float r, float d, float o, PImage img) {
  
    name = n;
    mass = m;
    distanceFromEarth = dfe;
    type = t;
    gravity = -1;
    habitability = -1;

    v = PVector.random3D();
    radius = r;
    angle = random(2*PI);
    distance = d;
    orbitspeed = o;
    v.mult(distance);
    
    noStroke();
    noFill();
    globe = createShape(SPHERE, radius);
    globe.setTexture(img);
  }
  
  // Updates parameters with gravity and habitability
  void Update(String n, float m, float dfe, String t, float r, float d, float o, PImage image, float g, float h) {
    name = n; mass = m; distanceFromEarth = dfe; type = t;
    gravity = g; habitability = h;
    radius = r; distance = d; orbitspeed = o;
    globe.setTexture(image);
  }
  // Updates parameters
  void Update(String n, float m, float dfe, String t, float r, float d, float o, PImage image) {
    name = n; mass = m; distanceFromEarth = dfe; type = t;
    gravity = -1; habitability = -1;
    radius = r; distance = d; orbitspeed = o;
    globe.setTexture(image);
  }
  // Add planet to planet array (used for solar system set up)
  void addPlanet(Planet planet) {
    planets.add(planet);
  }
  // Sets a planets orbit
  void orbit() {
    angle = angle + orbitspeed;
  }
  
  void spawnMoons(int total) {
    for (int i = 0; i < total; i++) {
      Planet planet = new Planet();
      planets.add(planet);
    }
  }
  // Drawz planet to display
  void show() {
    pushMatrix();
    noStroke();
    fill(255);
    
    PVector v2 = new PVector(0,1,0);
    PVector p = v.cross(v2);
    rotate(angle, p.x, p.y, p.z);

    
    translate(v.x, v.y, v.z);
    shape(globe);
    if (planets != null) {
      for (Planet planet : planets) {
        planet.orbit();
        planet.show();
      }
    }
    popMatrix();
  }
  
  // Debugging print statements
  void printStats() {
    println("Planet Name: " + name);
    println("Planet Type: " + type);
    
  }
  
  void showComparison(PImage img1, PImage img2, PVector pos1, PVector pos2) {
    pushMatrix();
    translate(pos1.x, pos1.y, pos1.z);
    globe = createShape(SPHERE, radius);
    globe.setTexture(img1);
    translate(pos2.x, pos2.y, pos2.z);
    globe = createShape(SPHERE, radius);
    globe.setTexture(img2);
    popMatrix();
  }
  
} 
