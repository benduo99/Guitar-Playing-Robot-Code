typedef struct
{
  // Fretting Stuff
  tMotor pulleyMotor;
  tSensors touchPort;
  char currentNote;
  char previousNote;
  // Strumming Stuff
  tMotor strummingMotor;
  int parity;			// Left relative to motor while looking at it from behind
} Line;
void updateNote (Line & object_A, Line & object_G, char note_A, char note_G)
{
  if (object_A.currentNote != '-')
    object_A.previousNote = object_A.currentNote;
  if (object_G.currentNote != '-')
    object_G.previousNote = object_G.currentNote;
  object_A.currentNote = note_A;
  object_G.currentNote = note_G;
}

void initializeLine (Line & object, tMotor pulleyMotor, tSensors touchPort,
  tMotor strummingMotor)
  {
    object.pulleyMotor = pulleyMotor;
    object.touchPort = touchPort;
    object.currentNote = '-';
    object.previousNote = 'A';	// Talk to Sam about this, where will it start according to his note generator
    object.strummingMotor = strummingMotor;
    object.parity = 1;
  } 

  void switchParity (Line & object)
  {
    object.parity *= -1;
  }
