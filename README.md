# Space Pirates

## AKA SDL Course project attempt 2 or so

## Todo's
UPDATE: The old version of this list is quite wishful XD I refactored it to make more sense in regards to the actual state of the game. that is fully playable demo devoid of much content.
### KNOWN BUGS
Those of course should be handled in the first place:
- Rock explosion animation doesn't work when collided with the ship.
- Sprites has no alpha channel so can occasionally overlap with black blobs.
- Jet stream particle effect spawns in much less amount that it should.
- Invisible menu higlights are in Leaderboards and Help.
- no game over when ship far over screen

### PLANNED FEATURES
**Should haves** - at least some of those would be really preferable to add soon*ish*:
- damage cooldown!!!
- clear code rubbish.
- implement global debugMode handler - one place to set dev mode options such as various logging (levels) or at least no need to enable collision boxes for each class one by one lol.
- includes optimization - move headers to separate directory, implement global headers, namespaces and check includes order (e.g. standard libs, then third-parties, then internal).
- power-ups like power kits (hp up), jet upgrade kit (max velocity up), shooting upgrade/power-up (either quicker shooting or temp thing like double shot or quick shot burst) - kinda nice to have, but soo easy to implement and makes the game feel much more abundant.
- ~~some at least minimal main menu would be nice.~~
- increasing difficulty.

**Good to haves** - not really that crucial, but would really benefit UX/maintainability:
- help page in main menu
- also leaderboard would nice fit the arcade-like style.
- keyboard handler to not trash main logic with multiple keyboard inputs (alongside with probably a lot of other main.cpp cleanings)
- Chunking for some game objects to improve performance.
- SFXs.
- background
- ~~refactor~~ implement TextureManager/AnimationManager/both - for big number of texture metadata, it might be better to store them in a separate file, e.g. csv file and use some method to en-masse initalize all TextureData objects into their vector.
- actual enemies - that seems like a no-brainer/should have, but depending on strategy those can be either almost-minimal-effort (like for some kind of sentry turrets /w minimal or no animation) or a whole lot of work (any sensible AI, animation, BALANCING); def good to have, but I'd prefer the game to have actual main menu than that... (and both are relatively big things).
- Decouple window and game area, i.e. so that you can't e.g. fly under the UI hehe.

**Won't do** (in a nearest future) - big things, not planning them in a near future:
- actually implementing the idea of "moving camera"/big world map - that one would be quite tricky, but would also enable a whole new bunch of possibilities gameplay-wise.
- Biomes - different background, music, maybe physical characteristics, certainly spawn rates, difficulty and loot.
- Mining
- Equipment that have UI and not only some text placed on the game window.
- Trading/Interacting with GameObjects/rabbit hole type entities with own UI.
- graphics better than paint doodles XD
 
## Sources / Architecture patterns
https://en.wikipedia.org/wiki/Composition_over_inheritance - inspired by Starcraft blogpost I decided to try (meta?)pattern of Composition over inheritance and thus introducing delegates instead of traditional object family tree. Hopefully this helps with avoiding major project redefinition in case of change of requirements during the coding...
https://en.wikipedia.org/wiki/Entity_component_system#Common_patterns_in_ECS_use - actually, it was randomly recommended by Gemini and seemed like a reasonable next step after adding basic components to the game.

**Update:** I currently rolled-back most component-based code from the main branch; this might however eventually be an useful thing, but might also require quite some refactor...

## Licensing

### Font Details
Designer Name: 	Astigmatic One Eye Typographic Institute
Font License: 	Public domain, GPL, OFL
Website: 	http://www.astigmatic.com