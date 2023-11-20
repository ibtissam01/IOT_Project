int ledPin = 8;
int pietonLedPin = 5;
int mouvPin = 7;
int buzzerPin = 9;
int voitureMouvPin = 6; // Ajout du capteur de mouvement pour les voitures
unsigned long debutPriorite = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pietonLedPin, OUTPUT);
  pinMode(mouvPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(voitureMouvPin, INPUT); // Configurer le capteur de mouvement pour les voitures
  digitalWrite(ledPin, LOW);
  digitalWrite(pietonLedPin, LOW);
  noTone(buzzerPin);
  Serial.begin(9600); // Initialisation de la communication série
}

void loop() {
  unsigned long tempsActuel = millis();

  // Si le temps écoulé est inférieur à 10 secondes, priorité aux voitures
  if (tempsActuel - debutPriorite < 10000) {
    digitalWrite(ledPin, LOW); // LED éteinte
    digitalWrite(pietonLedPin, HIGH);
    noTone(buzzerPin); // Arrêt de l'alerte sonore

    if (digitalRead(mouvPin) == HIGH) {
      // Détection de mouvement de piéton
      tone(buzzerPin, 1000, 1000); // Émet un bip pour avertir les voitures
    }
  } else { // Après 10 secondes, priorité aux piétons
    digitalWrite(ledPin, HIGH); // LED allumée
    digitalWrite(pietonLedPin, LOW);
    noTone(buzzerPin); // Arrêt de l'alerte sonore
 
    if (digitalRead(mouvPin) == LOW) {
      if (digitalRead(voitureMouvPin) == HIGH) {
        // Détection de mouvement de voiture en l'absence de piéton
        digitalWrite(ledPin, LOW);
        tone(buzzerPin, 500, 1000); // Signal positif pour les voitures
      }
    }
  }
  
  if (tempsActuel - debutPriorite >= 20000) {
    debutPriorite = tempsActuel; // Réinitialisation du temps de priorité
  }

  Serial.println(tempsActuel); // Afficher tempsActuel dans le port série
}
