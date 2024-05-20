#include <Arduino.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

// Firebase project details
#define FIREBASE_HOST "automated-rural-traffic-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "4dTzFcEH0vwurmfGQ8vOKIHpOZX68xNZX7bqbzTC"

// Wi-Fi credentials
#define WIFI_SSID "Daiyan"
#define WIFI_PASSWORD "dairaz1711"

const int redLED = 10;
const int blueLED = 11;
const int greenLED = 12;

FirebaseData firebaseData;
const String firebasePath = "/color/color";

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Connect to Wi-Fi
  connectToWiFi();

  // Initialize Firebase
  initializeFirebase();

  // Set initial status to "OFF"
  String status = getFirebaseStatus();
  if (status == "ERROR") {
    Serial.println("Failed to get initial status from Firebase");
  } else {
    Serial.println("Initial status from Firebase: " + status);
  }
}

void loop() {
  // Read status from Firebase
  String status = getFirebaseStatus();

  if (status == "red") {
    flashRed();
    Serial.println("Red turned on");
  } else if (status == "blue") {
    flashBlue();
    Serial.println("Blue turned on");
  } else if (status == "green") {
    flashGreen();
    Serial.println("Green turned on");
  } else if (status == "OFF") {
    Serial.println("OFF");
  } else {
    Serial.println("Unknown status: " + status);
  }

  delay(1000); // Adjust the delay as needed
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("Local IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void initializeFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH,WIFI_SSID,WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}

String getFirebaseStatus() {
  if (Firebase.getString(firebaseData, firebasePath)) {
    return firebaseData.stringData();
  } else {
    Serial.println("Error getting Firebase status: " + firebaseData.errorReason());
    return "ERROR";
  }
}

void flashRed() {
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
}

void flashBlue() {
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, HIGH);
  digitalWrite(greenLED, LOW);
}

void flashGreen() {
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, HIGH);
}
