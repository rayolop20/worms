# WORMS
This Worms game is a original game developed by Pol Maresch, Alex Garcia and Pau Olmos

Source Code: https://github.com/rayolop20/worms/releases/tag/V1.0

## Developers:

* Alex Garcia Selma ([Github])(https://github.com/MaralGS))
* Pol Maresch Marxuach ([Github])(https://github.com/rayolop20))
* Pau Olmos Serrano ([Github])(https://github.com/PauOlmos))
## Controls:
 * A Key: ForceX Left move
 * D key: ForceX Right move
 * S Key: ForceY Down move
 * W Key: ForceY Up move
 * Left Key: Move Left players (1 o 2)
 * Right Key: Move Right players (1 o 2)
 * F1 Key: Restart game
 * F2 Key: Enable/Disable Physics ball
 * F3 Key: Enable/Disable Debug colliders
 * F4 Key: Enable/Disable Bonus (Big Ball)
 * F5 Key: Enable/Disable Gravity
 * F6 Key: Enable/Disable Impulse forces
 * F7 Key: Enable/Disable Buoyancy forces
 * F8 Key: Enable/Disable Drag forces
 * F9 Key: Enable/Disable Move ball on the air (with W,A,S,D)
 * F11 Key: Put the game on 30 o 60 FPS (delta time to 1/16 ms or 1/33 ms)
 * Esc Key: Close game

## Objective:
The objective is make a physics engine from zero;
we maked a set of cannons that will fire, if one hits the o other
wins, there is a power up where the balls gets bigger for one turn.

The engine is made up of:
-Forces that control the grenade, such speed, acceleration, drag, gravity and boyancy.
-The engine is also made up of various formulas such as Newton's 2nd law, integrators and a collision system.
