## Castle Game Simulation
This is an educational project for Data Structures and Algorithms, written in C++ using Visual Studio. It is a simple simulation game of a castle fight with its enemies. CMUGraphics and SFML libraries are used. 

**Features**
- Data of the fight (castle and enemies) is loaded from a text file (6 files are provided for different scenarios).
- An output file is produced showing game status and statistics.
- 3 Modes of simulation are available:
  - Interactive mode: time passes with mouse clicks.
  - Step-By-Step mode: one time step passes every second.
  - Silent mode:only an output file is produced (no simulation).
- The castle has 4 regions, each with a tower protecting it.
- Each time step, enemies can move closer to the castle, based on whether the area is paved.
- Enemies types:
  - Fighters: Damage the castle towers.
  - Shielded Fighters: Deals more damage to towers and take less damage from them.
  - Pavers: Pave unpaved areas for other enemies to move on.
  - Balloons: Heal wounded enemies.
  - Freeze Tanks: Freezes a tower for one time step preventing it from attacking.
- Each enemy has unique reload time, fire power, starting health, etc.
- Tower and Enemy damages are calculated based on the distance they are from each other, their firepower, and several constants.
- The towers prioritize enemies that arrived first to their regions, however, some types of enemies are prioritized over others.
- The modes are dynamic, you can change the game mode during the simulation or load another file to start a new simulation.
- Sounds and images are added for better experience.


**It is a team project with 4 contributers:**

- Yosry Mohammad Yosry
- Amr Ahmad Abdelbaqi
- AbdElRahman Muhammad ElGamil
- Shady Fahmy AbdElHafez
