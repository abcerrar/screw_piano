const int zumbador = 9;
//                 la   si    do   re  mi    fa   sol
//                 A4    B4   C4   D4   E4   F4   G4
int notas_base[] = {440, 494, 262, 294, 330, 349, 392};
int notas_sost[] = {466, 000, 277, 311, 000, 369, 415}; 

int get_nota(char *n){
  if (n[0] == '0')
    return (0);
  int nota;
  
  if (n[0] <= 'Z')
  	nota = notas_base[n[0] - 'A'];
  else
    nota = notas_sost[n[0] - 'a'];
  int escala = n[1] - '0';
  if (escala > 4)
    while (escala-- != 4)
      nota /= 2;
  if (escala < 4)
    while (escala++ != 4)
      nota *= 2;
    
  return (nota);
}

int get_tempo(float bpm){
  return ((60 / bpm) * 1000);
}

void setup() {
  pinMode(zumbador, OUTPUT);
  Serial.begin(9600);

}

void play_melody(){
  char melody[][3] = {
    "C4", "C4", "D4", "C4", "F4", "E4", "00",
    "C4", "C4", "D4", "C4", "G4", "F4", "00", 
    "C4", "C4", "C3", "A4", "F4", "E4", "D4", "00",
    "a4", "a4", "A4", "F4", "G4", "F4"};
  float note_durations[] = {
    0.5, 0.5, 1, 1, 1, 1,
    1, 0.5, 0.5, 1, 1, 1, 1, 
    1, 0.5, 0.5, 1, 1, 1, 1, 1,
    1, 0.5, 0.5, 1, 1, 1, 1};
  int tempo = 130; //tempo in bpm
  int half = get_tempo(tempo);
  

  int size_melody = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < size_melody; i++){
    tone(zumbador, get_nota(melody[i]), (int)(half * note_durations[i]));
    Serial.println((int)(note_durations[i] * half));
    delay((int)(half * note_durations[i]));

  }
}

void loop() {
  if(digitalRead(2) == HIGH){
  	digitalWrite(zumbador, HIGH);
    play_melody();
    delay(200);
  }else{
  	digitalWrite(zumbador, LOW);
    delay(200);
    noTone(zumbador);
  }

}
		
