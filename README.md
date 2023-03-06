# Beyblade Project

## Project Description
### Introduction
The Beyblade Project, named after an anime about brave warriors battling
with spinning tops, aims to allow the user to observe spinning tops of different
shapes evolving according to their chosen initial values and numerical integrators
among the following choices

### Tops :
- Conical Top (ConeSimple)
- Chinese Top
- General Conical Top (a conical top with more general evolution equa-
tions)
- Energy Conical Top (a conical top with evolution equations based on
energy)
### Integrators :
- Euler-Cromer (for 1st and 2nd degree equations)
- Newmark (only for 2nd degree)
- Runge-Kutta (for 1st and 2nd degree equations)
Note : The General and Energy Conical Tops have some issues with their
evolution equations. The Euler-Cromer integrator does not seem to be suitable
for the Chinese Top as it diverges rapidly.
### Improvements
Several improvements, which are the pride of their creators, have since been
added to the project, such as (non-exhaustive list) :
- Ability to add tops with variable height, radius, and shape.
- Ability to choose whether the tops move in space or remain fixed in one
place.
- Ability to display the trace of their axes of symmetry.
- Ability to save the state of multiple tops and load old saves with certainty
of their authenticity.
- Top colors vary based on their rotation speed.
- Creation of bouncing balls.
- A WTF mode.
And much more...

## Beyblade Installation
1. Open Beyblade/project/beyblade.pro, QtCreator should open, press Ctrl+R
or click the run button at the bottom right.
2. An error "No rule to make target.." may appear (we have not been able to
make it disappear). A folder named build-beyblade-"Selected Kit" should
have been created in the Beyblade folder.
3. Move the files "music.wav" and "toupie.png" from Beyblade/project/Qt_GL
to Beyblade/build-beyblade-.../QT_GL.
4. Go back to QtCreator and run again, the program should start now.


## Using Beyblade
### Configuring initial parameters
Once the project is executed, two windows should appear, one with the
authors’ photo and a description such as "By Arthur and Jojo" and the other
being a configuration panel titled "Toupie Nº1". In the latter, you can select
the type of top, the integrator, the initial values of the angles (in radians) and
their derivatives as well as the initial position of the top. Then press Validate.
The selected top should then appear on the first mentioned window.
### Launching and interacting during execution
To set the top in motion, press the Space key on your keyboard. Press it
again to pause. Several other keys on your keyboard allow you to interact with
the program :

**u** Allows tops to move in space (press again to cancel).

**y** Displays the trace of the top (extension of the vector (contact point -
center of gravity)).

**w** Launches a randomly colored ball.

**t** Launches the WTF option, which puts the arena in full screen mode and
disrupts the current program.

**o** Decreases dt for better precision.

**p** Increases dt.

**F2** Activates full screen mode.

**ESC** Exits the program.

### Camera movement
The camera moves in a spherical coordinate system centered at the origin.
It is not possible to change this system.

**z** Zoom.

**s** Unzoom.

**q** Rotates the camera counterclockwise.

**d** Rotates the camera clockwise.

**h** Resets the camera.

- The arrow keys allow you to move in the spherical coordinate system
centered at the origin.
- The mouse (while holding down the left click) can also be used to move
the camera.
### Advanced parameters
For the smooth execution of these operations, pause the program. In the
program options, several choices are available to you :
1. Add a top
Reopens the configuration panel to add a top to the arena.
1. Delete a top
Deletes the selected top.
1. Saving and loading old backups
Save the system opens a window allowing you to select the file name where
the tops will be saved, as well as its location. (If a file with the same name
already exists, it will be replaced). The backup file thus created contains a
security code generated by a hashing function to verify the authenticity of the
document when it is reopened.
1. Information
A window appears. Select the bey of your choice to get information about
it.
### Running tests
To run a test, simply :
- "Uncomment" the test you are interested in in main_text.cc
- Click on the icon above the green execution arrow
- Select text and compile.
