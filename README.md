# WORMS
This Worms game is a original game developed by Pol Maresch, Alex Garcia and Pau Olmos

Source Code: https://github.com/MaralGS/Pintball-Fisica

## Developers:

* Alex Garcia Selma ([Github])(https://github.com/MaralGS))
* Pol Maresch Marxuach ([Github])(https://github.com/rayolop20))
+ Pau Olmos Serrano ([Github])(https://github.com/PauOlmos))
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

## Features:
 -If you hit all Ball Bumpers (static obstacle) you get 1 live extra
 -If you hit Ball Bumpers or Bumpers the ball bounces. When trow one ball, is created a wall by one sensor on the exit ball,
 that makes you unable to return the ball to the starting position inadvertently.
 -Added original sounds
 -Score, Last Score and Highest score
 -Time step

##How we made the game:
 We started making the map and adding walls and ball position, when we had that, then we started to make joins, the sticks and push ball joins, and there we
 had the firts problems, first of all the sticks colide with the walls and get stucked with them, we solve that separating sticks from rotation position.
 With push ball we had another problem, that somtimes stoped and didn't work, for solve that we needed to reduce and move the push walls and position, 
 because we think that the walls of push ball and map walls was colision with them and this stop the joint.

 Then we maked the win and score sensors, that we had no real big problems, after this we maked the bumpers, and we had problems with the velocity, 
 position and angle thats trows the ball, we solve that reducing the power that trows the ball, reducing the mesures of colder and makinh a new variable in
 box that this alowed rotate the bar.

 After this we make the First and End screens and lives and score, we didn't have problems with that. After do that we see that we had bullet frame,
 solve that we using the theory learned in class.

 Then we put it the sprites in the ball and sticks and souns, on the images we only had problems with the the image mesure,
 but with audios, we had problems because sometimes that didn't work or the audio sound was elevated, we solve that searching and converting mp3 audios
 to wav.

 And finaly we maked the frame-time that the only problems that we had, was only how to do that, and searching information and examples we maked.
