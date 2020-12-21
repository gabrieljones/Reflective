# Reflective - a game for Blinks

Two to Seven Teams

## Piece types

### Mirrors
- Single click - clockwise
- Double click - counter clockwise
- Long press - become Emitter

Rotate 1/12th per click

Orientations

    △▽△  ▲▼▲  △▼▲  △▽▲  ▲▽▲  ▲▽△  ▲▼△  △▼△ △▼▲  △▽▲  ▲▽▲  ▲▽△  ▲▼△  △▼△
    ▽△▽  ▼▲▼  ▼▲▽  ▼△▽  ▼△▼  ▽△▼  ▽▲▼  ▽▲▽ ▼▲▽  ▼△▽  ▼△▼  ▽△▼  ▽▲▼  ▽▲▽

### Emmiters

- Alone
  - Single click - change color
- Attached
  - Single click - emit for 2 seconds
- Long press - become Mirror

## Three types of Reflect

- Shallow - reflects to 2nd segment to right or left,  4 segments lit up
```
    △▼▲    ▲▽▲    ▲▼△
    ▼▲▽    ▼△▼    ▽▲▼
```
- Steep - reflect to 1st segment right or left, two opposing segments lit up
```
    ▲▽△    △▼△    △▽▲
    ▽△▼    ▽▲▽    ▼△▽
```
- None - passes straight through eg 3rd segment left or right aka opposite segment

  Never reflects backwards
  
## Setup

- Players each choose a blink and detach it from the cluster.
- Long press the blink so it becomes an emitter.
- Choose prefered color by single clicking their emitter repeatedly.
- Reattach the blink to the cluster.

## Game play

Turn

- Choose mirror
- Double click or Single click to rotate one step
- Click own emitter
- Observe reflected light path
- If light hits an emitter, the emitter dies
- End of turn

Play until one team remains.

## ToDo
- make light color match emitter color
- make emitter immune to own color, ie no friendly fire
- perpendicular mirror should reverse reflect, ie block light since self immune
- should mirror display be flipped 90 degrees. Would that be more intuitive?

## Alternative Play: Simulturn
- first player token rotates to next player
- take turns choosing and lightly placing finger on a mirror blink without clicking
- everyone simultaneously single clicks or double clicks their selected mirror blink
- then immediately clicks their emmiter blink
- repeat until one team remains
