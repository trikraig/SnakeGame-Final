# SnakeGame-Final
Game Dev with C++ Year 1 - Snake Game  - SFML ICA

My attempt at the below supplied spec using SFML. Started to create this game after learning C++ for 4 months.

Copy of the Spec

Snakes have discovered the best food to be underwater but must periodically come to the
surface for air. The snakes in this game live in a water tank, which unfortunately has a leak,
and the water level is dropping…
1. As with the original Snake game, the player controls a snake that moves around a
game world enclosed by walls (the extents of the water tank).
2. Snakes continually move in the direction they are facing.
3. Snake movement is carried out in steps where by the snake head moves by the size
of its head each update.
4. The player only controls the snake’s direction.
5. A game should have a minimum of one human controlled snake. Each snake should
have a score and ‘remaining breath’ displayed on screen.
6. Collectable food items appear at random times, there can be no more than 5
collectable items on screen at any one time. Each collectable item must occupy its
own location; i.e. they cannot overlap.
7. When collectable items are collected by a player, the snake’s ‘tail' grows by the
amount determined by the collectable item’s properties and the snake gains some
score. Different types of collectable item should increase the player’s tail and score
by different amounts.
8. A snake has a limited amount of breath available (counted in movement steps) and
must periodically come to the surface for air else they start losing their tail segments
(and score). The snake cannot go more than one step above the level of the water.
9. A snake will die if it collides with itself, another snake, the walls of the water tank or
it has no segments left.
10. Periodically the water level in the tank falls. It should take 90 seconds for the water
to drain completely.
11. The game finishes when there is only one snake remaining or all the water has
drained away.
12. The winner is the surviving snake with the highest score. If there is a head-on
collision or both snakes die at the same time, the winner is the snake with the
highest score.
