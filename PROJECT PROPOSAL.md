# Beemo's Rescue

Author: Sue Wee

---
##Overview
For my project, I would like to create a 2D adventure game. This game would be based on
Teemo, a League of Legends character featured here:

![ImageOfTeemo](https://www.mobafire.com/images/champion/skins/landscape/teemo-beemo.jpg)

A little background about Teemo is that his abilities include becoming invisible after
standing still for a while, and he is able to shoot little poison darts to defeat his
enemies in the game. In my adaptation of this, I would like to have the user be able to
control Teemo as he wanders around a map and collect items that buff him in some way,
whether by increasing his damage, health, armor or movement speed. There will be little text
boxes that tell the user a description of the item. I would also include his little
invisibility quirk, by making him translucent after a designated time of not moving, if
possible. After he collects his items, I would ideally have enemies that Teemo could
engage in battles with, who would drop special loot that give stronger buffs. However,
the goal of the game will be for Teemo to reach some sort of goal, whether it be a vat of
honey or saving a little friend of his, but there will be a "boss" at the end as the final
obstacle, so the will incentivize the user to collect the items/buffs. This is very similar
to our _**Adventure**_ MP Logic, where the user is able to pick up certain items and
navigate rooms or defeat enemies.

###Motivation & Background
I want to make this project because my CS 125 final was a Pokemon battle simulator, and I've
generally been very interested in game development because it allows me to be creative.
Also, the idea of showing this to my friends who share my interests is a HUGE motivator for me.
It's something that I can see myself really extending and working on even after the submission
of the initial project and that is very fun for me. As for background knowledge, I have a good
idea of how to structure the key elements of the data, such as items and enemies, so I will
mostly just have to adapt this into a visually interactive project. Also, thanks to the
_**Snake**_ MP Logic, I do have a lot to reference for help in terms of overall game
logic with keyboard input and refreshes.


###External Library
I plan on using a CinderBlock library of ciAnimatedGif, which will allow me to play gifs
on the screen.

###Projected Timeline
* Week One:
  * Have Teemo, the main character, operable by using the arrow keys.
  * Get familiar with GamePlay development and creating scenes.
  * Create rough ending for the game that will exit program when it occurs.
  * Implement at least one item that works, but ideally implement all items. Have them
interact with Teemo's stats accordingly. Implement sound effects for items.
* Week Two:
  * Create at least one enemy to have the game logic established.
  * Implement Teemo's invisibility passive ability.
  * Create ending in case Teemo's health reaches 0.
  * Ideally implement all enemies. Implement sound effects for enemies.
* Week Three:
  * Clean up the rest of the code and make sure to implement all missing pieces,
whether it be items or enemies.
  * Implement background music.
  * Implement the game logic for the final boss.
  
If I finish this assignment early (which I doubt I would), I could implement a side
mission sort of thing, where further investment in a sequence of events could lead
to obtaining a special item could result in a special ending once you do complete the game.
