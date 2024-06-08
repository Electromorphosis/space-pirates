# Space Pirates

## AKA SDL Course project attempt 2 or so

## Addition ideas
Not all of those might actually be needed to be implemented, but I needed some draft to-do list somewhere:
- Chunking for some game objects to improve performance.
- Biomes - different background, music, maybe physical characteristics, certainly spawn rates, difficulty and loot.
- Mining
- Trading

## Sources / Architecture patterns
https://en.wikipedia.org/wiki/Composition_over_inheritance - inspired by Starcraft blogpost I decided to try (meta?)pattern of Composition over inheritance and thus introducing delegates instead of traditional object family tree. Hopefully this helps with avoiding major project redefinition in case of change of requirements during the coding...
https://en.wikipedia.org/wiki/Entity_component_system#Common_patterns_in_ECS_use - actually, it was randomly recommended by Gemini and seemed like a reasonable next step after adding basic components to the game.

## Licensing
Spaceships by PixelWolf https://pixelwolfnet.itch.io/space-shooter-assets (CC0 - Creative Commons Licence)