byte heading = 0;
byte color = 0;
enum State {MIRROR, PLAYER_ATTACHED, PLAYER_ALONE, PLAYER_EMIT, PLAYER_DEAD};
enum Proto {NONE, EMIT};
Color colors[7] = {RED, BLUE, GREEN, YELLOW, ORANGE, CYAN, MAGENTA};
State state = MIRROR;
byte tbl[6 * 6] = {  3,2,1,0,5,4,  4,3,5,1,0,2,  5,4,3,2,1,0,  3,5,4,0,2,1,  1,0,5,4,3,2,  2,4,0,5,1,3};
Timer timer;

void stateMirror() {
  if (buttonSingleClicked()) heading = (heading + 1 + FACE_COUNT) % FACE_COUNT;
  if (buttonDoubleClicked()) heading = (heading - 1 + FACE_COUNT) % FACE_COUNT;
  if (buttonLongPressed()) state = PLAYER_ATTACHED;
//  inFace = 0;
  setColor(OFF);
  setColorOnFace(WHITE, (heading/2 + 0) % 3);
  setColorOnFace(WHITE, (heading/2 + 0) % 3 + heading % 2);
  setColorOnFace(WHITE, (heading/2 + 0) % 3 + 3);
  setColorOnFace(WHITE, ((heading/2 + 0) % 3 + 3 + heading % 2) % FACE_COUNT);
  setValueSentOnAllFaces(NONE);
  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      switch (getLastValueReceivedOnFace(f)) {
        case EMIT:
          setColorOnFace(YELLOW, f);
          byte outFace = tbl[heading * 6 + f];
          setValueSentOnFace(EMIT, outFace);
          setColorOnFace(YELLOW, outFace);
          break;
      }
    }
  }
  
  //temp
//    if (isValueReceivedOnFaceExpired(3)) state = PLAYER_ATTACHED;

//  state = PLAYER_ATTACHED;
//  startState();
//  if (startState() == START_STATE_WE_ARE_ROOT) state = PLAYER_ATTACHED;
}

void displMirror() {
}

void checkDead() {
  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      switch (getLastValueReceivedOnFace(f)) {
        case EMIT:
          state = PLAYER_DEAD;
          break;
      }
    }
  }
}
  
void statePlayerAttached() {
  setValueSentOnAllFaces(NONE);
  if (buttonSingleClicked()) {
    timer.set(2000);
    state = PLAYER_EMIT;
  }
  if (buttonLongPressed()) state = MIRROR;
  checkDead();
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
  if(timer.isExpired()) state = PLAYER_ATTACHED;
  setValueSentOnFace(EMIT, 0);
  checkDead();
}

void displPlayerEmit() {
  setColor(colors[color]); 
  setColorOnFace(OFF, 0);
}

void statePlayerDead() {
  if (buttonSingleClicked()) state = MIRROR;
}

void displPlayerDead() {
  setColor(makeColorRGB(64, 64, 64));
}

void setup() {
  randomize();
  color = random(sizeof(colors)-1);
//  heading = random(5);
  //temp
//  if (random(17) == 0) state = PLAYER_ATTACHED;
}

void loop() {
  switch (state) {
    case MIRROR:
      stateMirror();
      displMirror();
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
    case PLAYER_DEAD:
      statePlayerDead();
      displPlayerDead();
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
