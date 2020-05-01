# Development

---
- **4/18/20** Attempt to set up foundation of project
   - ~~Implement GamePlay external library~~
   - [x] Change external libary to ciAnimatedGif

- **4/21/20** Implement external library
    - [x] Implement header and source files to implement library

- **4/22/20** Write logic to ensure external library functionality
    - [x] Libary can draw animated gifs
    - [x] Library can resize animated gifs
    - [x] Library can draw multiple gifs at once and they can all play simultaneously
  
- **4/23/20** Start implementing Tile and PlayingField logic
    - [x] Text files written to represent scenes one and two
    - [x] Tile Class & PlayingField Class created
    - [x] Getters created for private instances

- **4/25/20** Program will not run
    - After trying to implement logic to read the map text files, program has crashed. 
    Will likely need to make another copy of the final project repository. 
    
- **4/27/20** Will attempt to recreate the project in a new copy of the repository.

- **4/28/20** Program works again, continue progress on loading map
    - [x] Can read file to store as entire rows in a string vector
    - [x] PlayingField class can now parse through files to create maps. 
    Tiles will automatically start out as a blank tile (white background and no 
    interactive dynamic type).
    
- **4/29/30** Work on having the correct gifs for the dynamic images.
    - [x] Implement minion default graphics.
    
- **4/30/30** Further implement user interaction and appropriate responses.
    - [x] Beemo can move around and will turn accordingly based on direction.
    - [x] Beemo movement is contained within the bounds of the playing field.
    - [x] Beemo will not walk into solid objects.
    - [x] Beemo can walk between scenes.
    
- **5/1/30** Create the skeleton of the game interaction logic.
    - ~~Implement minion attack response graphics.~~
    - [x] Replace minion default graphics with attack graphics.
    - [x] Save dynamic states based on the item that is hidden that will be revealed
    upon interaction. 
    - [x] Format and draw description, inventory, and stats slots. 
    - [x] Description, inventory, and stats update according to item interaction.
    - [x] Create a Character class to track animation, stats, inventory and more.
    - [ ] Create an final boss and end state for the game. 
    
Ongoing: 
- [ ] Implement Initializer Lists in Playing Field Constructor.
- [ ] Remove magic numbers.