# Backlog

As I'm not sure for now if I'd have time and motivation in the near future to deal with all minor todo's, good-to-haves etc. for this project, I won't care for now to populate Issues. 

Instead, here are unordered list of todo's that have generally even lower priority (or greater effort) than nice-to-haves from Readme. Here they are:
- Second iteration of main.cpp clean-code and refactor; possibly could also include delegating most of the logic to external component files, esp. 
  - moving, 
  - cinematics (ending sequence), 
  - views process flow (this one separately is a good few afternoons of work, if one would like to do it properly and with scale in mind tbh),
  - (control) events handling
  - particles/objects in general spawning
  - randomness calculations
- global code review in terms of memory safety
- implementation of multi-threading / async's.
- Particle/"jetstream" spawn: implement dynamic parameter for width/height, though that might not be needed for now.
- Player/textures: Implement Texture / Sprite Manager/Component?
- Player: should hp be handled by GEH?
- TextBox/fonts handling: Probably I could came up with an idea to better handle fonting than having the path hardcoded, with only diff between constructors being fontSize setup.
- Rock:
  - /substitute unused default constructor with simple log message; possibly the same for other unused, but required artifacts? Or maybe they are not required?
  - /merge asteroid and random spawn constructors and general spawning refactor
  - /for random spawn "dynamic for width/height, though that might not be needed for now" - not sure what I meant, possibly differing size rocks?
  - /asteroid: Why not store them in GEH or other global setting component? Investigate if it's a good idea to use GEH/GlobalSettings component for easier management of rock spawns.
- Create RandomnessUtility to handle many random vars and distributions I use.
- Review updating positions for renderer logic - should I create component / utility for those calculations and assignments?
- Create an utility to calculate a sensible text box size based on font size, char sum size and char number. Or maybe there are ready-made implementations available?
- Control/player moving: Add velocity vector which is applied at the end of the scan, so that <<possibly>> it will work for multi-key combos; i.e. flying forward and clockwise at the same time;
- Related to the point one above: came up with an idea of modularized sprite rendering, e.g. separate texture states for left-right side-engine, main engine, laser gun, shield activated as a filter/alpha channel adjusted new sprite; in a far future that could even evolve into some kind of upgrading system, which would be cool (at least as long as it would not make another make-ship-from-tiles game-type clone; I'd much prefer Mars-Miner-flyin-in-space-with-upgrades game clone/mutant!!!)
- Came up with the idea to disable speeding animations (& particles) when not actively pushing movement buttons; at least kind of related to the one above.
