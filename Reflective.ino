byte heading = 0;
byte inFace = 0;
byte color = 0;
enum State {MIRROR, REFLECT, PLAYER_ATTACHED, PLAYER_ALONE, PLAYER_EMIT};
enum Proto {NONE, EMIT};
Color colors[7] = {RED, BLUE, GREEN, YELLOW, ORANGE, CYAN, MAGENTA};
State state = MIRROR;

void stateMirror() {
  if (buttonSingleClicked()) heading = (heading + 1 + FACE_COUNT) % FACE_COUNT;
  if (buttonDoubleClicked()) heading = (heading - 1 + FACE_COUNT) % FACE_COUNT;
  if (buttonLongPressed()) state = PLAYER_ATTACHED;
  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      switch (getLastValueReceivedOnFace(f)) {
        case EMIT:
          inFace = f;
          state = REFLECT;
          break;
      }
    }
  }
  
  //temp
    if (isValueReceivedOnFaceExpired(3)) state = PLAYER_ATTACHED;

//  state = PLAYER_ATTACHED;
//  startState();
//  if (startState() == START_STATE_WE_ARE_ROOT) state = PLAYER_ATTACHED;
}

void displMirror() {
  setColor(OFF);
  setColorOnFace(WHITE, (heading/2 + 0) % 3);
  setColorOnFace(WHITE, (heading/2 + 0) % 3 + heading % 2);
  setColorOnFace(WHITE, (heading/2 + 0) % 3 + 3);
  setColorOnFace(WHITE, ((heading/2 + 0) % 3 + 3 + heading % 2) % FACE_COUNT);
}
  
void stateReflect() {
  stateMirror();
}

void displReflect() {
  displMirror();
  setColorOnFace(YELLOW, inFace);
}
  
void statePlayerAttached() {
  if (buttonSingleClicked()) state = PLAYER_EMIT;
  if (buttonLongPressed()) state = MIRROR;
  if (isAlone()) {
    state = PLAYER_ALONE;
  }
}

void statePlayerAlone() {
  if (buttonSingleClicked()) color = (color + 1 + 7) % 7;
  if (buttonDoubleClicked()) color = (color - 1 + 7) % 7;
  if (buttonLongPressed()) state = MIRROR;
  if (!isAlone()) {
    state = PLAYER_ATTACHED;
  }
}

void displPlayer() {
  setColor(dim(colors[color], 128)); 
  setColorOnFace(colors[color], 0);
}
  
void statePlayerEmit() {
  setValueSentOnFace(EMIT, 0);
}

void displPlayerEmit() {
  setColor(colors[color]); 
  setColorOnFace(OFF, 0);
}

void setup() {
  randomize();
  color = random(sizeof(colors)-1);
  heading = random(5);
  //temp
//  if (random(17) == 0) state = PLAYER_ATTACHED;
}

void loop() {
  switch (state) {
    case MIRROR:
      stateMirror();
      displMirror();
      break;
    case REFLECT:
      stateReflect();
      displReflect();
      break;
    case PLAYER_ATTACHED:
      statePlayerAttached();
      displPlayer();
      break;
    case PLAYER_ALONE:
      statePlayerAlone();
      displPlayer();
      break;
    case PLAYER_EMIT:
      statePlayerEmit();
      displPlayerEmit();
      break;
  }
}

/*
0
  0 3
  1 2
  2 1
  3 0
  4 5
  5 4
1
  0 4
  1 3
  2 5
  3 1
  4 0
  5 2
2
  0 5
  1 4
  2 3
  3 2
  4 1
  5 0
3
  0 3
  1 5
  2 4
  3 0
  4 2
  5 1
4
  0 1
  1 0
  2 5
  3 4
  4 3
  5 2
5
  0 2
  1 4
  2 0
  3 5
  4 1
  5 3
  */
